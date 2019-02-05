//
// Created by urbschaj on 01.02.19.
//

#include "exception.h"
#include "throw.h"
#include <spdlog/spdlog.h>
#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>
#include <sstream>
#include <boost/algorithm/string.hpp>

namespace ppmac {

	namespace exception
	{
		std::string BackTrace(int skip) {
			// this is the really easy version to simple get mangled names
			//
			/*void *array[256];
			size_t size;
			// get void*'s for all entries on the stack
			size = backtrace(array, 256);
			// print out all the frames to stderr
			fprintf(stderr, "Error: signal %d:\n", 0);
			backtrace_symbols_fd(array, size, STDERR_FILENO);*/

			void *callstack[128];
			const int nMaxFrames = sizeof(callstack) / sizeof(callstack[0]);
			char buf[1024];
			int nFrames = backtrace(callstack, nMaxFrames);
			char **symbols = backtrace_symbols(callstack, nFrames);

			std::ostringstream trace_buf;
			for (int i = skip; i < nFrames; i++) {
				//printf("%s\n", symbols[i]);

				Dl_info info;
				if (dladdr(callstack[i], &info) && info.dli_sname) {
					char *demangled = NULL;
					int status = -1;
					if (info.dli_sname[0] == '_')
						demangled = abi::__cxa_demangle(info.dli_sname, NULL, 0, &status);
					snprintf(buf, sizeof(buf), "%-3d %*p %s + %zd",
							i, int(2 + sizeof(void*) * 2), callstack[i],
							status == 0 ? demangled :
							info.dli_sname == 0 ? symbols[i] : info.dli_sname,
							static_cast<char*>(callstack[i]) - static_cast<char*>(info.dli_saddr));
					free(demangled);
				} else {
					snprintf(buf, sizeof(buf), "%-3d %*p %s",
							i, int(2 + sizeof(void*) * 2), callstack[i], symbols[i]);
				}
				int p = 0;
				while(symbols[i][p] != '(' && symbols[i][p] != ' ' && symbols[i][p] != 0) {
					++p;
				}
				char syscom[256];
				sprintf(syscom,"addr2line %p -e %.*s", callstack[i], p, symbols[i]);
				//last parameter is the file name of the symbol
				//system(syscom);
				auto res = ExecuteWithReturn(syscom);
				boost::algorithm::trim(res);
				trace_buf << buf << " (src: " << res << ")\n";
			}
			free(symbols);
			if (nFrames == nMaxFrames)
				trace_buf << "[truncated]\n";
			return trace_buf.str();
		}

		void TerminateHandler() {
			auto eptr = std::current_exception();
			if(eptr) {
				SPDLOG_CRITICAL("unhandled exception (exiting):\n{}", StringifyException(std::current_exception(), 4, '>'));
			} else {
				SPDLOG_CRITICAL("terminate without exception");
			}
			fmt::print(BackTrace(0), "\n");
			abort();
		}
	}
}

//		void bt_sighandler(int sig, struct sigcontext ctx) {
//
//			void *trace[16];
//			char **messages = (char **)NULL;
//			int i, trace_size = 0;
//
//			if (sig == SIGSEGV)
//				printf("Got signal %d, faulty address is %p, "
//				       "from %p\n", sig, ctx.cr2, ctx.rip);
//			else
//				printf("Got signal %d\n", sig);
//
//			trace_size = backtrace(trace, 16);
//			/* overwrite sigaction with caller's address */
//			trace[1] = (void *)ctx.rip;
//			messages = backtrace_symbols(trace, trace_size);
//			/* skip first stack frame (points here) */
//			printf("[bt] Execution path:\n");
//			for (i=1; i<trace_size; ++i)
//			{
//				printf("[bt] #%d %s\n", i, messages[i]);
//
//				/* find first occurence of '(' or ' ' in message[i] and assume
//				 * everything before that is the file name. (Don't go beyond 0 though
//				 * (string terminator)*/
//				size_t p = 0;
//				while(messages[i][p] != '(' && messages[i][p] != ' '
//				      && messages[i][p] != 0)
//					++p;
//
//				char syscom[256];
//				sprintf(syscom,"addr2line %p -e %.*s", trace[i], p, messages[i]);
//				//last parameter is the file name of the symbol
//				system(syscom);
//			}
//
//			exit(0);
//		}