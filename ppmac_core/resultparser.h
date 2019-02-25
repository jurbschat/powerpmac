//
// Created by urbschaj on 24.01.19.
//

#ifndef POWERPMAC_COMMANDPARSER_H
#define POWERPMAC_COMMANDPARSER_H

#include "throw.h"

#include <boost/container/small_vector.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <experimental/optional>

namespace ppmac::parser {

	namespace detail {
		bool CheckForError(const std::string& str);
		void ThrowIfError(const std::string& str);
		std::experimental::optional<std::pair<int32_t, std::string>> GetError(const std::string& str);
	}

	namespace EC {
		const int OUT_OF_RANGE_NUMBER = 23;
	}

	// target = result type e.g. float, int etc. could also be int to inverse and parse bytes to string
	// Tag is used to distinguish if the result type needs to be parsed in different manners depending
	// on what was queried. e.g. a gate returns with $f0000001
	template<typename Target, typename Tag = void>
	struct parser_traits;

	template<>
	struct parser_traits<std::string> {
		using result_type = std::string;
		static const result_type& convert(const std::string& s) {
			return s;
		}
	};

	template<>
	struct parser_traits<float> {
		using result_type = float;
		static result_type convert(const std::string& s) {
			try {
				return std::stof(s);
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse float '{}'", s);
			}
		}
	};

	template<>
	struct parser_traits<double> {
		using result_type = double;
		static result_type convert(const std::string& s) {
			try {
				return std::stod(s);
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse double '{}'", s);
			}
		}
	};

	template<>
	struct parser_traits<int32_t> {
		using result_type = int32_t;
		static result_type convert(const std::string& s) {
			try {
				long result = std::stoll(s);
				if (result > std::numeric_limits<int32_t>::max()) {
					THROW_RUNTIME_ERROR("out of range '{}' for int32_t", s);
				}
				return result;
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse int32 from '{}'", s);
			}
		}
	};

	template<>
	struct parser_traits<uint32_t> {
		using result_type = uint32_t;
		static result_type convert(const std::string& s) {
			try {
				long result = std::stoull(s);
				if (result > std::numeric_limits<uint32_t>::max()) {
					THROW_RUNTIME_ERROR("out of range '{}' for uint32_t", s);
				}
				return result;
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse uint32 from '{}'", s);
			}
		}
	};

	template<>
	struct parser_traits<int64_t> {
		using result_type = int64_t;
		static result_type convert(const std::string& s) {
			try {
				int64_t result = std::stoll(s);
				return result;
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse int64 from '{}'", s);
			}
		}
	};

	template<>
	struct parser_traits<uint64_t> {
		using result_type = uint64_t;
		static result_type convert(const std::string& s) {
			try {
				long result = std::stoull(s);
				return result;
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse uint64 from '{}'", s);
			}
		}
	};

	struct parser_gate_tag;

	template<>
	struct parser_traits<uint32_t, parser_gate_tag> {
		using result_type = uint32_t;
		static result_type convert(const std::string& s) {
			try {
				long result = std::stoull(s.substr(1), nullptr, 16);
				if (result > std::numeric_limits<uint32_t>::max()) {
					THROW_RUNTIME_ERROR("out of range '{}' for uint32_t", s);
				}
				return result;
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse 32bit hex from '{}'", s);
			}
		}
	};

	template<>
	struct parser_traits<uint64_t, parser_gate_tag> {
		using result_type = uint64_t;
		static result_type convert(const std::string& s) {
			try {
				return std::stoull(s.substr(1), nullptr, 16);
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse 64bit hex from '{}'", s);
			}
		}
	};

	struct coord_tag;

	template<>
	struct parser_traits<double, coord_tag> {
		using result_type = double;
		static result_type convert(const std::string& s) {
			try {
				return std::stod(s.substr(1));
			} catch(std::exception) {
				RETHROW_RUNTIME_ERROR("unable to parse double '{}'", s);
			}
		}
	};

	using NoneParser = parser_traits<std::string>;
	using FloatParser = parser_traits<float>;
	using DoubleParser = parser_traits<double>;
	using IntParser = parser_traits<int32_t>;
	using UIntParser = parser_traits<uint32_t>;
	using Int64Parser = parser_traits<int64_t>;
	using UInt64Parser = parser_traits<uint64_t>;
	using Hex32Parser = parser_traits<uint32_t, parser_gate_tag>;
	using Hex64Parser = parser_traits<uint64_t, parser_gate_tag>;
	using CoordDoubleParser = parser_traits<double, coord_tag>;

	template<typename SepPred, size_t VALUE_COUNT = 32>
	boost::container::small_vector<std::string, VALUE_COUNT>
	Split1D(const std::string &str, SepPred pred)
	{
		boost::container::small_vector<std::string, VALUE_COUNT> splitVector;
		boost::algorithm::split(splitVector, str, pred, boost::token_compress_on);
		if(splitVector.empty()) {
			THROW_RUNTIME_ERROR("unable to parse '{}' as line", str);
		}
		return splitVector;
	}

	template<typename SepPred1, typename SepPred2 = boost::algorithm::detail::is_any_ofF<char>, size_t LINE_COUNT = 4, size_t VALUE_COUNT = 32>
	boost::container::small_vector<boost::container::small_vector<std::string, LINE_COUNT>, VALUE_COUNT>
	Split2D(const std::string &str, SepPred1 pred1, SepPred2 pred2)
	{
		boost::container::small_vector<boost::container::small_vector<std::string, LINE_COUNT>, VALUE_COUNT> resultVector;
		boost::container::small_vector<std::string, LINE_COUNT> lineSplitVector;
		boost::algorithm::split(lineSplitVector, str, pred1, boost::token_compress_on);
		if(lineSplitVector.empty()) {
			THROW_RUNTIME_ERROR("unable to parse '{}' as multiline", str);
		}
		for(auto& l : lineSplitVector) {
			resultVector.emplace_back(Split1D<SepPred2, VALUE_COUNT>(l, pred2));
		}
		return resultVector;
	}

}

#endif //POWERPMAC_COMMANDPARSER_H
