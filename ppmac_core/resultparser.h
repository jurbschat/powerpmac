//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_COMMANDPARSER_H
#define POWERPMAC_COMMANDPARSER_H

#include <boost/container/small_vector.hpp>
#include <boost/algorithm/string.hpp>
#include <string>

namespace ppmac::cmd {

	template<typename T>
	struct parser_traits;

	template<>
	struct parser_traits<float> {
		static float convert(const std::string& s) {
			return std::stof(s);
		}
	};

	template<typename T>
	T ParseValueResult(const std::string &str) {
		return parser_traits<T>::convert(str);
	};

	template<typename T, size_t VALUE_COUNT = 32>
	boost::container::small_vector<T, VALUE_COUNT> ParseLineResult(const std::string &str) {
		boost::container::small_vector<std::string, VALUE_COUNT> splitVector;
		boost::container::small_vector<T, VALUE_COUNT> resultVector;
		boost::algorithm::split(splitVector, str, boost::is_space(), boost::token_compress_on);
		if(splitVector.empty()) {
			THROW_RUNTIME_ERROR("unable to parse result. str: {}", str);
		}
		for(auto& s : splitVector) {
			resultVector.push_back(ParseValueResult<T>(s));
		}
		return resultVector;
	}

	template<typename T, size_t LINE_COUNT = 4, size_t VALUE_COUNT = 32>
	boost::container::small_vector<boost::container::small_vector<T, LINE_COUNT>, VALUE_COUNT> ParseMultilineResult(const std::string &str)
	{
		boost::container::small_vector<boost::container::small_vector<T, LINE_COUNT>, VALUE_COUNT> resultVector;
		boost::container::small_vector<std::string, VALUE_COUNT> splitVector;
		boost::algorithm::split(splitVector, str, boost::is_any_of("\r\n"), boost::token_compress_on);
		if(splitVector.empty()) {
			THROW_RUNTIME_ERROR("unable to parse result. str: {}", str);
		}
		for(auto& l : splitVector) {
			resultVector.emplace_back(ParseLineResult<T, VALUE_COUNT>(l));
		}
		return resultVector;
	}




}

#endif //POWERPMAC_COMMANDPARSER_H
