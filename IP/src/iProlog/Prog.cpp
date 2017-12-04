#include "Prog.h"

Prog::Prog(std::string fname)
	:Engine(fname)
{

}

Prog::~Prog()
{

}

void Prog::pp(std::string str)
{
	cout << str;
};

void Prog::println(std::string str)
{
	cout << str;
}

template<typename T>
std::string Prog::maybeNull(const T &O) {
	if (O == null) return "$null";

	return showTerm(O);
}

template<typename T>
bool Prog::isListCons(const T &name) {
	return ".".equals(name) || "[|]".equals(name) || "list".equals(name);
}

template<typename T>
static bool isOp(const T &name) {
	return "/".equals(name) || "-".equals(name) || "+".equals(name) || "=".equals(name);
}

template<typename T>
std::string Prog::st0(const T args[])
{
	std::string buf = "";

	const std::string name = args[0]->toString();
	if (args.size() == 3 && isOp(name))
	{
		buf.append("(");
		buf.append(maybeNull(args[0]));
		buf.append(" " + name + " ");
		buf.append(maybeNull(args[1]));
		buf.append(")");
	}
	else if (args.size() == 3 && isListCons(name))
	{
		buf.append('[');
		{
			buf.append(maybeNull(args[1]));
			auto tail = args[2];
			for (;;)
			{

				if ("[]" == tail || "nil" == tail)
				{
					break;
				}
				if (!(dynamic_cast<std::vector<void*>>(tail) != nullptr))
				{
					buf.append('|');
					buf.append(maybeNull(tail));
					break;
				}
				std::vector<void*> list = static_cast<std::vector<void*>>(tail);
				if (!(list.size() == 3 && isListCons(list[0])))
				{
					buf.append('|');
					buf.append(maybeNull(tail));
					break;
				}
				else
				{
					//if (i > 1)
					buf.append(',');
					buf.append(maybeNull(list[1]));
					tail = list[2];
				}
			}
		}
		buf.append(']');
	}
	else if (args.size() == 2 && "$VAR" == name)
	{
		buf.append("_" + args[1]);
	}
	else
	{
		const std::wstring qname = maybeNull(args[0]);
		buf.append(qname);
		buf.append("(");
		for (int i = 1; i < args.size(); i++)
		{
			constexpr auto O = args[i];
			buf.append(maybeNull(O));
			if (i < args.size() - 1)
			{
				buf.append(",");
			}
		}
		buf.append(")");
	}

	return buf;
}

void Prog::ppCode() {
	pp("\nSYMS:");
	pp("\nCLAUSES:\n");

	for (int i = 0; i < clauses.size(); i++) {
		Clause *C = clauses[i];
		pp("[" + std::to_string(i) + "]:" + showClause(C));
	}
	pp("");

}

std::string Prog::showClause(Clause *s)
{
	int l = s->hgs.size();
	std::string buf = "";
	buf.append("---base:[" + std::to_string(s->base) + "] neck: " + std::to_string(s->neck) + "-----\n");
	buf.append(showCells(s->base, s->len)); // TODO
	buf.append("\n");
	buf.append(showCell(s->hgs[0]));

	buf.append(" :- [");
	for (int i = 1; i < l; i++)
	{

		int e = s->hgs[i];
		buf.append(showCell(e));
		if (i < l - 1)
		{
			buf.append(", ");
		}
	}

	buf.append("]\n");

	buf.append(showCell(s->hgs[0]));
	
	if (l > 1)
	{
		buf.append(" :- \n");
		for (int i = 1; i < l; i++)
		{
			int e = s->hgs[i];
			buf.append("  ");
			buf.append(showCell(e));
			buf.append("\n");
		}
	}
	else
	{
		buf.append("\n");
	}
	return buf;
}

void Prog::ppGoals(IntList *bs)
{
	while (bs->isempty(bs) != 0)
	{
		pp(showCell(bs->getHead(bs)));
		bs = bs->getTail(bs);
	}

}

void Prog::ppc(Spine *S)
{
	//stats();
	IntList *bs = S->gs;
	
	pp("\nppc: t=" + std::to_string(S->ttop) + ",k=" + std::to_string(S->k) + "len=" + std::to_string(bs->len(bs)));
	ppGoals(bs);
}

template<typename T>
std::vector<T> *Prog::stream()
{
	return "";
	//return StreamSupport::stream(this, false);
}

int Prog::characteristics()
{
	return 0;
}

long long Prog::estimateSize()
{
	return std::numeric_limits<long long>::max();
}
