// project12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdexcept>
#include <cassert>

#include "Interpreter.h"

int main()
{
	/*Stack<int> s;

	cout << s.isEmpty() << endl;
	s.push(5);
	s.push(9);
	s.push(145);
	cout << s.getTop() << endl;
	s.pop();
	cout << s.getTop() << endl;*/

	//List<int> l;
	//cout << l.isEmpty() << endl;
	//l.pushFront(2);
	//l.pushFront(5);
	//l.popAtPos(l.findPos(2));
	//cout << l.at(0) << endl;
	////cout << l.at(1) << endl;

	Interpreter i;
	
	/*i.addVariable("edno", 1);
	i.addVariable("dve", 2);
	i.printVariable();
	cout << i.findVariable("dve") << endl;
	i.changeVariable("dve", 33);
	i.printVariable();*/
	
	i.readFromFile("in.txt");
	//i.printVariable();

	return 0;
}