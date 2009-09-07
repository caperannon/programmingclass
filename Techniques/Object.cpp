
#include <iostream>

#include "Object.h"

Interpreter::Interpreter()
{
	m_nCounter = 0;
}

Interpreter::~Interpreter()
{
}

void Interpreter::InterpretArgument(char * pArg)
{
	if (pArg[0] != '-')
	{
		std::cout << pArg << " has an improper format!" << "\n";
	}
	else
	{
		switch (pArg[1])
		{
			case 'P':
			case 'p':
			PrintFunction((char *)"P");
			break;
			
			case 'Q':
			case 'q':
			PrintFunction((char *)"Q");
			break;
			
			default:
			PrintFunction((char *)"Default");
			break;
		}
	}
}

void Interpreter::PrintFunction(char * pFunction)
{
	std::cout << "The " << pFunction << " Function." << "\n";
}

