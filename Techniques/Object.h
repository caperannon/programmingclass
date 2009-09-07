
#ifndef OBJECT_H_
#define OBJECT_H_


class Interpreter
{
public:
	Interpreter();
	~Interpreter();

	void InterpretArgument(char * pArg);
	
private:
	int m_nCounter;

	void PrintFunction(char * pFunction);
};

#endif

