#include "pch.h"
#include "Interpreter.h"

Variable::Variable(const string& name, const int& value)
{
	this->name = name;
	this->value = value;
}

bool Variable::operator==(const Variable& other)
{
	return !this->name.compare(other.name);
}

void Interpreter::addVariable(string name, int value)
{
	l.pushFront(Variable(name, value));
}

int Interpreter::findVariable(string name)
{
	return l.at(l.findPos(Variable(name, -1))).value;
}

const Variable& Interpreter::getVariable(string name)
{
	return l.at(l.findPos(Variable(name, -1)));
}

void Interpreter::changeVariable(string name, int newValue)
{
	Variable v(name, newValue);
	l.popAtPos(l.findPos(v));
	l.pushFront(v);
}

void Interpreter::printVariable() const
{
	l.print();
}

void Interpreter::pushVariable(string name)
{
	s.push(getVariable(name));
}

void Interpreter::readFromFile(string fileName)
{
	input.open(fileName);

	if (!input.is_open())
	{
		throw std::runtime_error("Can not read from file");
	}

	string sequence;
	while (input >> sequence)
	{
		callFunction(sequence);	
	}
	input.close();
}

void Interpreter::callFunction(string function)
{
	if (function == "LET") 
	{
		let();
	}
	else if (function == "READ") 
	{
		read();
	}
	else if (function == "PRINT")
	{
		print();
	}
	else if (function == "PUSH")
	{
		push();
	}
	else if (function == "POP")
	{
		pop();
	}
	else if (function == "GOTO")
	{
		goTo();
	}
	else if (function == "LABEL")
	{
		label();
	}
	else if (function == "IF")
	{
		iF();
	}
	else if (function == "WHILE")
	{
		wHile();
	}
	else if (findVariable(function))
	{
		operationWithVariable(function);
	}
}

void Interpreter::let()
{
	string variableName;
	input >> variableName;
	addVariable(variableName, -1);
}

void Interpreter::read()
{
	string variableName;
	input >> variableName;
	int value;
	cin >> value;
	changeVariable(variableName, value);
}

void Interpreter::print()
{
	string variableName;
	input >> variableName;

	if (l.findPos(Variable(variableName, -1)) == -1)
	{
		cout << variableName << endl;
	}
	else
	{
		cout << findVariable(variableName) << endl;
	}
}

void Interpreter::push()
{
	string variableName;
	input >> variableName;
	pushVariable(variableName);
}

void Interpreter::pop()
{
	s.pop();
}

void Interpreter::goTo()
{
	string isTheSame;
	input >> isTheSame;
	string sequence;
	while (input >> sequence)
	{	
		if (sequence == "LABEL")
		{
			input >> sequence;
			if (isTheSame == sequence)
				break;
		}
	}
}

void Interpreter::label()
{
	string sequence;
	input >> sequence;
}

void Interpreter::iF()
{
	string sequence;
	if (operationVariable())
	{
		while (input >> sequence)
		{
			if (sequence == "ELSE")
			{
				while (input >> sequence)
				{
					if (sequence == "ENDIF")
						return;
				}
			}
			else if (sequence == "ENDIF")
			{
				return;
			}
			callFunction(sequence);
			if (sequence == "GOTO")
				return;
		}
	}
	else
	{
		while (input >> sequence)
		{
			if (sequence == "ELSE")
				break;
		}
		while (input >> sequence)
		{
			if (sequence == "ENDIF")
				return;

			callFunction(sequence);
			if (sequence == "GOTO")
				return;
		}
	}
}

void Interpreter::wHile()
{
	string sequence;
	streampos pos = input.tellg();
	while (operationVariable())
	{
		while (input >> sequence)
		{
			if (sequence == "DONE")
			{
				input.seekg(pos);
				break;
			}
			callFunction(sequence);
		}
	}
	while (input >> sequence)
	{
		if (sequence == "DONE")
		{
			return;
		}
	}
}

void Interpreter::operationWithVariable(string name)
{
	string line;
	getline(input, line);
	stringstream str(line);
	string operation;
	str >> operation;

	if (operation == "=")
	{
		int result = 0;
		string first;
		str >> first;
		
		int firstInt = stringToInt(first);
	
		string operation;
		str >> operation;
		if (operation == "")
		{
			result = firstInt;	
		}
		else
		{
			string second;
			str >> second;
			int secondInt = stringToInt(second);
			
			switch (operation[0])
			{
			case '+': result = firstInt + secondInt;
				break;
			case '-': result = firstInt - secondInt;
				break;
			case '*': result = firstInt * secondInt;
				break;
			case '/': result = firstInt / secondInt;
				break;
			case '%': result = firstInt % secondInt;
			}
		}
		changeVariable(name, result);
	}
}

int Interpreter::stringToInt(string str)
{
	int result = 0;
	if (l.findPos(Variable(str, -1)) == -1)
	{
		stringstream toNumber(str);
		toNumber >> result;
	}
	else
	{
		result = findVariable(str);
	}
	return result;
}

bool Interpreter::operationVariable()
{
	string line;
	getline(input, line);
	stringstream str(line);
	string fVariable;
	str >> fVariable;
	int firstVariable = stringToInt(fVariable);
	string operation;
	str >> operation;
	string sVariable;
	str >> sVariable;
	int secondVariable = stringToInt(sVariable);

	if (operation == "==")
	{
		return firstVariable == secondVariable;
	}
	else if (operation == "!=")
	{
		return firstVariable != secondVariable;
	}
	else if (operation == "<")
	{
		return firstVariable < secondVariable;
	}
	else if (operation == "<=")
	{
		return firstVariable <= secondVariable;
	}
	else if (operation == ">")
	{
		return firstVariable > secondVariable;
	}
	else if (operation == ">=")
	{
		return firstVariable >= secondVariable;
	}
	return false;
}