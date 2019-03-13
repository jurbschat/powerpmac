//
// Created by urbschaj on 18.02.19.
//

#include "udpsink.h"
#include "throw.h"
#include "uuid.h"
#include <spdlog/spdlog.h>

namespace ppmac {


	UdpSink::UdpSink(const std::string& host, int port)
			: host(host),
			  port(port),
			  socket(io_service),
			  isLogging(false),
			  disabled(false)
	{
		boost::asio::ip::udp::resolver resolver(io_service);
		boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, fmt::format("{}", port));
		remote_endpoint = *resolver.resolve(query);
		socket.open(boost::asio::ip::udp::v4());
		runId = uuid::GetUUID();
	}

	std::string UdpSink::GetHost() {
		try {
			boost::asio::ip::udp::resolver resolver(io_service);
			boost::asio::ip::udp::resolver::query query(boost::asio::ip::host_name(), fmt::format("{}", port));
			boost::asio::ip::udp::resolver::query hostQuery(boost::asio::ip::host_name(), "");
			boost::asio::ip::udp::resolver::iterator end;
			std::stringstream ss;
			bool first = true;
			for(auto it = resolver.resolve(hostQuery); it != end; it++) {
				std::string ip = it->endpoint().address().to_string();
				std::string hostName = it->host_name();
				ss << (first ? "" : ", ") << hostName << " (" << ip << ")";
				first = false;
			}
			return ss.str();
		}
		catch(const std::exception& e) {
			fmt::print(stderr, "unable to get hostname: {}\n", e.what());
		}
		return "unknown";
	}

	UdpSink::~UdpSink() {}

	void UdpSink::sink_it_(const spdlog::details::log_msg& msg)
	{
		if(isLogging || disabled) {
			return;
		}
		isLogging = true;
		fmt::memory_buffer formatted;
		spdlog::sinks::sink::formatter_->format(msg, formatted);
		auto str = fmt::to_string(formatted);
		SendMessage(str);
		isLogging = false;
	}

	void UdpSink::flush_() {}

	void UdpSink::SendMessage(const std::string& msg) {
		if(!socket.is_open()) {
			return;
		}
		try {
			size_t sent = socket.send_to(boost::asio::buffer(msg), remote_endpoint, 0);
			if(sent != msg.size()) {
				fmt::print(stderr, "unable to send whole msg to {}:{}, missing {} bytes", host, port, msg.size() - sent);
			}
		} catch(...) {
			fmt::print(stderr, StringifyException(std::current_exception()));
		}
	}

}

