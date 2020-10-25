#pragma once
#include "Stack.h"
#include "List.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using std::ifstream;
using std::string;
using std::ostream;
using std::stringstream;
using std::getline;
using std::streampos;

struct Variable
{
	Variable() {};
	Variable(const string& name, const int& value);
	int value;
	string name;
	bool operator==(const Variable& other);
};

inline
ostream& operator<<(ostream& os, Variable v)
{
	os << v.name << " " << v.value << endl;
	return os;
}

class Interpreter
{
private:
	List<Variable> l;
	Stack<Variable> s;

	ifstream input;

	int stringToInt(string str);
public:
	Interpreter() {};

	void addVariable(string name, int value);
	int findVariable(string name);
	const Variable& getVariable(string name);
	void changeVariable(string name, int newValue);
	void printVariable() const;
	void pushVariable(string name);

	void readFromFile(string fileName);

	void callFunction(string function);
	
	void let();
	void read();
	void print();
	void push();
	void pop();
	void goTo();
	void label();
	void iF();
	void wHile();
	
	void operationWithVariable(string name);
	bool operationVariable();
};