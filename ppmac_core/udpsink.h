//
// Created by urbschaj on 18.02.19.
//

#include <spdlog/sinks/base_sink.h>
#include <boost/asio.hpp>

#include <mutex>
#include <atomic>
#include <sstream>

#ifndef POWERPMAC_UDPSINK_H
#define POWERPMAC_UDPSINK_H

namespace ppmac {

	// the udp sink directly writes to the udp socket without buffering. if the network is
	// slow this could take some time... but we exepect this to be quite fast so change only to a
	// buffered queue if necessary
	class UdpSink : public spdlog::sinks::base_sink <std::mutex>
	{
	public:
		UdpSink(const std::string& host, int port);
		~UdpSink();
		std::string GetHost();
	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override;
		void flush_() override;
	private:
		void SendMessage(const std::string& msg);
		std::string host;
		int32_t port;
		boost::asio::io_service io_service;
		boost::asio::ip::udp::socket socket;
		boost::asio::ip::udp::endpoint remote_endpoint;
		std::atomic<bool> isLogging;
		std::atomic<bool> disabled;
		std::string runId;
	};

	using udp_sink_mt = UdpSink;
}

#endif //POWERPMAC_UDPSINK_H
