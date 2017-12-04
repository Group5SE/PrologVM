#ifndef PROG
#define PROG

#include "Engine.h"

using namespace std;
using namespace iProlog;

namespace iProlog {

	class Prog :public Engine
	{
	public:
		Prog(std::string fname);
		~Prog();

		static void pp(std::string str);

		static void println(std::string str);
		
		template<typename T>
		static std::string maybeNull(const T &O);

		template<typename T>
		static bool isListCons(const T &name);

		template<typename T>
		static bool isOp(const T &name);

		template<typename T>
		static std::string st0(const T args[]);

		void ppCode();

		std::string Prog::showClause(Clause *s);

		void ppGoals(IntList *bs);

		void ppc(Spine *S);
		/////////////// end of show

		// possibly finite Stream support
		template<typename T>
		std::vector<T> *stream();

		int characteristics();

		long long estimateSize();
	};


}
#endif


