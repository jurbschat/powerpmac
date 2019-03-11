#pragma once

namespace ppmac::es {

	struct RecursiveCheck
	{
		RecursiveCheck()
			: depth(0)
		{}

		void Push() {
 			depth++;
		}

		void Pop() {
			depth--;
		}

		operator bool(){
			return depth > 0;
		}
	private:
		int depth;
	};
}