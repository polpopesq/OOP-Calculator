#include <iostream>
#include <string>
#include "Calculator.h"

using namespace std;

int main()
{
	Calculator c1;
	string expression = "";
	cout << "Enter expression:" << endl;
	getline(cin, expression);
	while (expression != "exit")
	{
		string solution = c1.solveExp(expression);
		if (c1.exc == 0)
		{
			cout << "Result is: ";
		}
		cout << solution << endl << "Enter another expression type or exit:" << endl;
		c1.exc = 0;
		getline(cin, expression);
	}
}