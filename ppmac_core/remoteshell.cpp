//
// Created by urbschaj on 14.01.19.
//

#include "remoteshell.h"

#include "utility.h"
#include "stopwatch.h"
#include "throw.h"

#include "libs/span.hpp"

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <boost/algorithm/string.hpp>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>

namespace ppmac {

	namespace detail {

		enum class ReadCallbackAction {
			Break,
			Continue
		};

		/*int WaitSocket(int sock, LIBSSH2_SESSION* session) {
			timeval timeout;
			timeout.tv_sec = 0;
			timeout.tv_usec = 500000;

			fd_set fd;
			FD_ZERO(&fd);
			FD_SET(sock, &fd);

			//now make sure we wait in the correct direction
			int dir = libssh2_session_block_directions(session);


			fd_set *writefd = nullptr;
			fd_set *readfd = nullptr;

			if(dir & LIBSSH2_SESSION_BLOCK_INBOUND) {
				readfd = &fd;
			}

			if(dir & LIBSSH2_SESSION_BLOCK_OUTBOUND) {
				writefd = &fd;
			}

			int rc = select(sock + 1, readfd, writefd, NULL, &timeout);

			return rc;
		}*/

		template<typename Channel, typename Session, typename DataCallback>
		RemoteShellErrorCode ReceiveToBuffer(int sock, Channel& channel, Session& session, std::chrono::milliseconds timeout, DataCallback cb) {
			std::array<char, 4096> recvBuffer;
			bool useTimeout = timeout > time::zero;
			StopWatch<> sw(true);
			while(true) {
				ssize_t rc = libssh2_channel_read(channel.get(), recvBuffer.data(), recvBuffer.size());
				(void)sock;
				(void)session;
				/*int so_error;
				socklen_t len = sizeof so_error;
				getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
				if (so_error != 0) {
					printf("conn is closed (read)!\n");
				}*/
				while(rc == LIBSSH2_ERROR_EAGAIN) {
					if(useTimeout && sw.Elapsed() > timeout) {
						//SPDLOG_DEBUG("read command timeout");
						return RemoteShellErrorCode::CommandTimeout;
					}
					//WaitSocket(sock, session.get());
					rc = libssh2_channel_read(channel.get(), recvBuffer.data(), recvBuffer.size());
				}
				if(rc < 0) {
					SPDLOG_DEBUG("ssh read error: {}", rc);
					return RemoteShellErrorCode::ConnectionReset;
				}
				ReadCallbackAction action = cb(stdext::span<char>{recvBuffer.begin(), recvBuffer.begin() + rc});
				if(action == ReadCallbackAction::Break) {
					break;
				}
			}
			return RemoteShellErrorCode::Ok;
		};
	}

	RemoteShell::RemoteShell(CoreNotifyInterface* core)
		: host(),
		port(0),
		sock(0),
		connected(false),
		session(nullptr, [](auto){}),
		channel(nullptr, [](auto){}),
		core(core)
	{}

	RemoteShell::~RemoteShell() {
		Disconnect();
		libssh2_exit();
	}

	/*
	 * Channel read reads a message that is terminated by the 0x06 terminator which is the terminator the pmac uses.
	 */
	stdext::expected<std::string, RemoteShellErrorCode> RemoteShell::ChannelRead(std::chrono::milliseconds timeout) {
		std::lock_guard<std::mutex> guard(readWriteMtx);
		return ReadUntilTerminator(timeout);
	}

	/*
	 * Consume simply reads everything it can get untill the timeout is reached.
	 */
	stdext::expected<std::string, RemoteShellErrorCode> RemoteShell::ChannelConsume(std::chrono::milliseconds timeout) {
		std::lock_guard<std::mutex> guard(readWriteMtx);
		return Consume(timeout);
	}

	/*
	 * Sends a command to the server
	 */
	RemoteShellErrorCode RemoteShell::ChannelWrite(const std::string& str, std::chrono::milliseconds timeout) {
		std::lock_guard<std::mutex> guard(readWriteMtx);
		return Write(str, timeout);
	}

	/*
	 * The ChannelWriteRead method clears the message buffer as we want the answer for the previously written request.
	 * If you want to send multiple requests and then read the ansers back from the message buffer you need to use
	 * ChannelWrite and ChannelRead manually. ChannelWriteRead will delete all remaining messages from the buffer
	 * before receiving.
	 */
	stdext::expected<std::string, RemoteShellErrorCode> RemoteShell::ChannelWriteRead(const std::string& str, std::chrono::milliseconds timeout) {
		std::lock_guard<std::mutex> guard(readWriteMtx);
		auto writeRes = Write(str, timeout);
		if(writeRes == RemoteShellErrorCode::Ok) {
			auto readRes = ReadUntilTerminator(timeout);
			if(readRes) {
				messageBuffer.Clear();
				auto& s = *readRes;
				auto pos = s.find_first_of(str);
				// erase everything until the end of the string we send
				// before, if we cant find it something is off
				if(pos == std::string::npos) {
					return stdext::make_unexpected(RemoteShellErrorCode::InvalidWriteReadResponse);
				};
				s.erase(0, str.size() + pos);
				boost::algorithm::trim(s);
				return readRes;
			}
			return readRes;
		}
		return stdext::make_unexpected(writeRes);
	}

	/*
	 * Get the native socket
	 */
	int RemoteShell::GetSocket() {
		return sock;
	}

	/*
	 * Connect to a remote host and setup the ssh connection
	 */
	RemoteShellErrorCode RemoteShell::Connect(std::string host_, int port_) {
		std::lock_guard<std::mutex> guard(readWriteMtx);
		host = host_;
		port = port_;
		sock = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		unsigned long hostaddr = inet_addr(host.c_str());
		sin.sin_addr.s_addr = hostaddr;

		struct timeval timeout;
		timeout.tv_sec  = 1;
		timeout.tv_usec = 0;
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

		if (connect(sock, reinterpret_cast<sockaddr*>(&sin), sizeof(sockaddr_in)) != 0) {
			SPDLOG_DEBUG("failed to connect to {}:{}", host, port);
			return RemoteShellErrorCode::ConnectionRefused;
		}
		int val[]{1};
		setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, val, sizeof(int));
		SetupShell();
		connected = true;
		SPDLOG_DEBUG("connection to pmac established");
		return RemoteShellErrorCode::Ok;
	}

	/*
	 * Close the ssh connection and the socket
	 */
	void RemoteShell::Disconnect() {
		std::lock_guard<std::mutex> guard(readWriteMtx);
		channel.reset();
		session.reset();
		if(sock) {
			int ret = close(sock);
			if(ret != 0) {
				SPDLOG_DEBUG("unable to close rocket, error: {}", ret);
			}
			sock = 0;
		}
		connected = false;
		SPDLOG_DEBUG("connection to pmac closed");
		core->OnConnectionLost();
	}

	bool RemoteShell::IsConnected() {
		return connected;
	}

	RemoteShellErrorCode RemoteShell::Write(const std::string& str, std::chrono::milliseconds timeout) {
		if(!connected) {
			SPDLOG_DEBUG("unable to write channel if not connected");
			return RemoteShellErrorCode::ConnectionIsClosed;
		}
		ssize_t bytesWritten = 0;
		SetupWriteBuffer(str, '\n', writeBuffer);
		StopWatch<> sw(true);
		while(bytesWritten < static_cast<ssize_t>(writeBuffer.size())) {
			ssize_t rc = libssh2_channel_write(channel.get(), writeBuffer.data() + bytesWritten, writeBuffer.size() - bytesWritten);
			/*int so_error;
			socklen_t len = sizeof so_error;
			getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
			if (so_error != 0) {
				printf("conn is closed (write)!\n");
			}*/
			if(rc == LIBSSH2_ERROR_EAGAIN) {
				auto tmp = sw.Elapsed();
				if(timeout > time::zero && tmp > timeout) {
					SPDLOG_DEBUG("write command timeout");
					return RemoteShellErrorCode::CommandTimeout;
				}
				//SPDLOG_DEBUG("write incomplete, trying again");
				//detail::WaitSocket(sock, session.get());
				continue;
			}
			if(rc < 0) {
				SPDLOG_DEBUG("ssh write error: {}", rc);
				Disconnect();
				return RemoteShellErrorCode::ConnectionReset;
			}
			bytesWritten += rc;
		}
		return RemoteShellErrorCode::Ok;
	}

	stdext::expected<std::string, RemoteShellErrorCode> RemoteShell::ReadUntilTerminator(std::chrono::milliseconds timeout) {
		if(!connected) {
			SPDLOG_DEBUG("unable to read channel if not connected");
			return stdext::make_unexpected(RemoteShellErrorCode::ConnectionIsClosed);
		}
		// check if we had an extra message from the last recv
		auto msg = messageBuffer.ExtractMessage();
		if(msg) {
			SPDLOG_DEBUG("returning message from buffer");
			return *msg;
		}
		std::string message;
		auto result = detail::ReceiveToBuffer(sock, channel, session, timeout, [this, &message](stdext::span<char> data){
			messageBuffer.AddData(data);
			auto msg = messageBuffer.ExtractMessage();
			if(msg) {
				message = *msg;
				return detail::ReadCallbackAction::Break;
			}
			return detail::ReadCallbackAction::Continue;
		});

		if(result == RemoteShellErrorCode::ConnectionReset) {
			Disconnect();
		}
		else if(result == RemoteShellErrorCode::CommandTimeout) {
			AddTimeout();
		}
		else if(result == RemoteShellErrorCode::Ok) {
			return message;
		}
		return stdext::make_unexpected(result);
	}

	stdext::expected<std::string, RemoteShellErrorCode> RemoteShell::Consume(std::chrono::milliseconds timeout) {
		if(!connected) {
			SPDLOG_DEBUG("unable to read channel if not connected");
			return stdext::make_unexpected(RemoteShellErrorCode::ConnectionIsClosed);
		}
		readBuffer.clear();
		auto result = detail::ReceiveToBuffer(sock, channel, session, timeout, [this](stdext::span<char> data){
			readBuffer.insert(readBuffer.end(), data.begin(), data.end());
			return detail::ReadCallbackAction::Continue;
		});

		if(result == RemoteShellErrorCode::ConnectionReset) {
			Disconnect();
		}

		if(IsOneOf(result, RemoteShellErrorCode::Ok, RemoteShellErrorCode::CommandTimeout)) {
			return std::string(readBuffer.begin(), readBuffer.end());
		}
		return stdext::make_unexpected(result);
	}

	void RemoteShell::SetupShell() {
		auto session_ = std::unique_ptr<LIBSSH2_SESSION, void(*)(LIBSSH2_SESSION* sess)>{libssh2_session_init(), [](LIBSSH2_SESSION* sess){
			libssh2_session_disconnect(sess, "Normal Shutdown, Thank you for playing");
			libssh2_session_free(sess);
		}};
		//libssh2_session_set_timeout(session_.get(), 5000);
		if (libssh2_session_handshake(session_.get(), sock)) {
			THROW_RUNTIME_ERROR("Failure establishing SSH session");
		}
		const char* fingerprint = libssh2_hostkey_hash(session_.get(), LIBSSH2_HOSTKEY_HASH_SHA1);
		fmt::memory_buffer mb;
		for(char c : stdext::span<const char>{fingerprint, 20}) { fmt::format_to(mb, "{:X}", c); }
		SPDLOG_DEBUG("Fingerprint: {}.", fmt::to_string(mb));
		if (libssh2_userauth_password(session_.get(), "root", "deltatau")) {
			//fprintf(stderr, "\tAuthentication by password failed!\n");
			THROW_RUNTIME_ERROR("Authentication by password failed!");
		}
		auto channel_ = std::unique_ptr<LIBSSH2_CHANNEL, void(*)(LIBSSH2_CHANNEL* sess)>{libssh2_channel_open_session(session_.get()), [](LIBSSH2_CHANNEL* chan){
			libssh2_channel_free(chan);
		}};
		if (!channel_.get()) {
			THROW_RUNTIME_ERROR("Unable to open a session");
		}
		libssh2_channel_setenv(channel_.get(), "FOO", "bar");
		if (libssh2_channel_request_pty(channel_.get(), "vanilla")) {
			THROW_RUNTIME_ERROR("Failed requesting pty");
		}
		if (libssh2_channel_shell(channel_.get())) {
			THROW_RUNTIME_ERROR("Unable to request shell on allocated pty");
		}
		libssh2_channel_set_blocking(channel_.get(), 0);

		//libssh2_trace(session_.get(), LIBSSH2_TRACE_SOCKET | LIBSSH2_TRACE_TRANS | LIBSSH2_TRACE_CONN | LIBSSH2_TRACE_ERROR );

		session = std::move(session_);
		channel = std::move(channel_);
	}

	void RemoteShell::SetupWriteBuffer(const std::string &data, char terminator, std::vector<char> &buffer) {
		buffer.clear();
		buffer.reserve(data.size() + 1);
		buffer.insert(buffer.begin(), data.begin(),data.end());
		buffer.push_back(terminator);
	}

	void RemoteShell::AddTimeout() {
		consecutiveTimeouts++;
		SPDLOG_DEBUG("timeouts: {}", consecutiveTimeouts);
		if(consecutiveTimeouts >= 5) {
			SPDLOG_DEBUG("more than 5 consecutive timeouts, closing connection (TEST MESSAGE)");
			Disconnect();
		}
	}

	void RemoteShell::ResetTimeouts() {
		consecutiveTimeouts = 0;
		SPDLOG_DEBUG("timeouts: reset");
	}
}
