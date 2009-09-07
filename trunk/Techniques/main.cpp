
//#define CPP

#ifdef CPP
#include "Object.h"
	Interpreter nInterpret;
#else
#include "Parameters.h"
#endif

int main(int nArgs, char ** hArg)
{
	for (int i = 1; i < nArgs; i++)
	{
#ifdef CPP
		nInterpret.InterpretArgument(hArg[i]);
#else
		InterpretArgument(hArg[i]);
#endif
	}

	return 0;
}



