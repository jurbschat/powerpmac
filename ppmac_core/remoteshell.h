//
// Created by urbschaj on 14.01.19.
//

#ifndef POWERPMAC_CONNECTIONHANDLER_H
#define POWERPMAC_CONNECTIONHANDLER_H

//#include "config.h"
#include "receivebuffer.h"
#include "corenotifyinterface.h"
#include "libs/expected.hpp"

#include <libssh2.h>
#include <wise_enum.h>

#include <mutex>
#include <vector>
#include <chrono>
#include <memory>
#include <string>

namespace ppmac {

	WISE_ENUM_CLASS((RemoteShellErrorCode, int32_t),
			Ok,
			ConnectionReset,
			ConnectionIsClosed,
			WriteAlreadyInProcess,
			ReadAlreadyInProcess,
			CommandTimeout,
			BufferToSmall,
			NoTerminatorFound,
			InvalidWriteReadResponse,
			ConnectionRefused,
			SSHHandshakeFailed,
			SSHAuthFailed,
			SSHSessionFailed,
			SSHPTYFailed,
			SSHShellFailed
	)


	class RemoteShell
	{
	public:
		RemoteShell();

		~RemoteShell();

		/*
		 * Channel read reads a message that is terminated by the 0x06 terminator which is the terminator the pmac uses.
		 */
		stdext::expected<std::string, RemoteShellErrorCode> ChannelRead(std::chrono::milliseconds timeout = std::chrono::milliseconds{1000});

		/*
		 * Consume simply reads everything it can get untill the timeout is reached.
		 */
		stdext::expected<std::string, RemoteShellErrorCode> ChannelConsume(std::chrono::milliseconds timeout = std::chrono::milliseconds{1000});

		/*
		 * Sends a command to the server
		 */
		RemoteShellErrorCode ChannelWrite(const std::string& str, std::chrono::milliseconds timeout = std::chrono::milliseconds{1000});

		/*
		 * The ChannelWriteRead method clears the message buffer as we want the answer for the previously written request.
		 * If you want to send multiple requests and then read the ansers back from the message buffer you need to use
		 * ChannelWrite and ChannelRead manually. ChannelWriteRead will delete all remaining messages from the buffer
		 * before receiving.
		 */
		stdext::expected<std::string, RemoteShellErrorCode> ChannelWriteRead(const std::string& str, std::chrono::milliseconds timeout = std::chrono::milliseconds{1000});

		/*
		 * Same as WriteRead but does not read untill terminator but until timeout
		 */
		stdext::expected<std::string, RemoteShellErrorCode> ChannelWriteConsume(const std::string& str, std::chrono::milliseconds timeout  = std::chrono::milliseconds{1000});

		/*
		 * Get the native socket
		 */
		int GetSocket();

		/*
		 * Connect to a remote host and setup the ssh connection
		 */
		RemoteShellErrorCode Connect(std::string host_, int port_);

		/*
		 * Close the ssh connection and the socket
		 */
		void Disconnect();

		/*
		 * Returns the current connection status. As we are non blocking, it can happen that we think
		 * we are in a good state but messages are not arriving anymore. Send/Recv success has to be
		 * checked on each ChannelRead/ChannelWrite call.
		 */
		bool IsConnected();

	private:
		using mutex_type = std::recursive_mutex;

		RemoteShellErrorCode Write(const std::string& str, std::chrono::milliseconds timeout);
		stdext::expected<std::string, RemoteShellErrorCode> ReadUntilTerminator(std::chrono::milliseconds timeout);
		stdext::expected<std::string, RemoteShellErrorCode> Consume(std::chrono::milliseconds timeout);
		stdext::expected<std::string, RemoteShellErrorCode> Execute(const std::string& str, std::chrono::milliseconds timeout);

		RemoteShellErrorCode SetupShell();
		void CloseSocket();
		void SetupWriteBuffer(const std::string &data, char terminator, std::vector<char> &buffer);
		void AddTimeout();
		void ResetTimeouts();

		std::string host;
		int port;
		int sock;
		bool connected;
		int32_t consecutiveTimeouts;
		std::unique_ptr<LIBSSH2_SESSION, void(*)(LIBSSH2_SESSION*)> session;
		std::unique_ptr<LIBSSH2_CHANNEL, void(*)(LIBSSH2_CHANNEL*)> channel;
		std::vector<char> readBuffer;
		std::vector<char> writeBuffer;
		ReceiveBuffer messageBuffer;
		mutex_type readWriteMtx;
	};
}


#endif //POWERPMAC_CONNECTIONHANDLER_H

/*
 * Welcome
Login: gq95ont
Password: s9Qt8Wj8
 * */