#include "Calculator.h"
#include <cmath>
#include "CharStack.h"
#include "DoubleStack.h"
#include <string>

Calculator::Calculator()
{
	exc = 0;
}

string Calculator::solveExp(string expression)
{
	expression = eraseSpaces(expression);

	dealWithNegativeSign(expression);

	if (!correctExpression(expression))
	{
		return "Expression has no sense!\n";
	}
	string result = calculateSection(expression, 0, expression.length());
	if (exc)
	{
		return "";
	}
	return result;
}

bool Calculator::correctExpression(string expression)
{
	int roundOpen = 0, squareOpen = 0;
	int roundClosed = 0, squareClosed = 0;
	//bucata asta numara cate paranteze sunt inchise/deschise
	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == '(')
		{
			roundOpen++;
		}
		if (expression[i] == ')')
		{
			roundClosed++;
		}
		if (expression[i] == '[')
		{
			squareOpen++;
		}
		if (expression[i] == ']')
		{
			squareClosed++;
		}
	}
	if (roundClosed != roundOpen || squareClosed != squareOpen)
	{
		cout << "Bracket error!" << endl;
		return false;
	}
	
	return true;
}

string Calculator::eraseSpaces(string expression)
{
	string str = "";
	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] != ' ')
		{
			str += expression[i];
		}
	}
	return str;
}

void Calculator::dealWithNegativeSign(string& expression)
{
	if (expression.length() > 0 && expression[0] == '-')
	{
		expression = '0' + expression;
	}
	for (int i = 1; i < expression.length(); i++)
	{
		if (expression[i] == '-' && (expression[i - 1] == '(' || expression[i - 1] == '['))
		{
			expression = expression.substr(0, i) + '0' + expression.substr(i);
		}
	}
}

void Calculator::replaceComma(string& expression)
{
	for (int i = 0; i < expression.length(); i++)
	{
		if (expression[i] == ',')
		{
			expression[i] = '.';
		}
	}
}

//calculates expression [start,end)
string Calculator::calculateSection(string expression, int start, int end)
{
	while (true)
	{
		//aici cand da de paranteza apeleaza recursiv calculateSection de paranteza si modifica expression cu valoare calculata recursiv
		if (expression.find('(') == string::npos)//daca nu mai are rotunde
		{
			if (expression.find('[') != string::npos)//dar are inca patrate
			{
				squareToRound(expression);
			}
			else //nu are nici rotunde nici patrate
			{
				return to_string(solvePara(toRPN(expression)));
			}
		}
		else //are inca ()
		{
			if (expression.find('(') > expression.find('('))
			{
				return "Open bracket before closing it!";
			}
			else
			{
				int bracStart = expression.find('(');
				int bracEnd = expression.find(')');
				string toSolve = expression.substr(bracStart + 1, bracEnd - bracStart - 1);
				double tempResult = solvePara(toRPN(toSolve));
				expression.erase(bracStart, bracEnd - bracStart + 1);
				expression.insert(bracStart, to_string(tempResult));
			}
		}
	}
	return string();
}

void Calculator::squareToRound(string& expression)
{
	while (expression.find('[') != string::npos)
	{
		int i = expression.find('[');
		expression[i] = '(';
	}
	while (expression.find(']') != string::npos)
	{
		int i = expression.find(']');
		expression[i] = ')';
	}
}

double Calculator::numFromString(string num)
{
	double res = 0;
	int intRes = 0;
	int i;
	if (num.find('.') != string::npos)
	{
		i = num.length() - 1;
		while (num[i] != '.')
		{
			res = (res + (num[i] - '0')) / 10;
			i--;
		}

	}
	i = 0;
	while (num[i] != '.' && i < num.length())
	{
		intRes = intRes * 10 + num[i] - '0';
		i++;
	}
	res += intRes;
	return res;
}

int Calculator::precedence(char c)
{
	if (c == '^' || c == '#')
	{
		return 3;
	}
	else if (c == '*' || c == '/')
	{
		return 2;
	}
	else if (c == '+' || c == '-')
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

bool Calculator::isNum(char c)
{
	return ((c <= '9' && c >= '0') || c == '.');
}

string Calculator::toRPN(string expression)
{
	string polish;
	CharStack postfixer;

	for (int i = 0; i < expression.length(); i++)
	{
		if (isNum(expression[i]))
		{
			polish += expression[i];
			if (i < expression.length() && isNum(expression[i + 1]) == false)
			{
				polish += ' ';
			}
		}
		else
		{
			if (postfixer.isEmpty())
			{
				postfixer.push(expression[i]);
			}
			else
			{
				if (precedence(expression[i]) > precedence(postfixer.peek()))
				{
					postfixer.push(expression[i]);
				}
				else
				{
					while (postfixer.isEmpty() == false && precedence(expression[i]) <= precedence(postfixer.peek()))
					{
						polish += postfixer.pop();
						polish += ' ';
					}
					postfixer.push(expression[i]);
				}
			}
		}
	}
	while (postfixer.isEmpty() == false)
	{
		polish += postfixer.pop();
	}

	return polish;
}

double Calculator::calculus(double x, double y, char sign)
{
	if (sign == '+')
	{
		return x + y;
	}
	else if (sign == '-')
	{
		return x - y;
	}
	else if (sign == '*')
	{
		return x * y;
	}
	else if (sign == '/')
	{
		return x / y;
	}
	else if (sign == '^')
	{
		return pow(x, y);
	}
	else if (sign == '#')
	{
		return pow(x, 1.0 / y);
	}
	else return 0;
}

double Calculator::solvePara(string para)
{
	DoubleStack solver;

	if (para.find('(') != string::npos ||
		para.find(')') != string::npos ||
		para.find('[') != string::npos ||
		para.find(']') != string::npos)
	{
		cerr << "Incorrect expression!";
	}

	int i = 0;
	while (i < para.length())
	{
		if (isNum(para[i]))
		{
			int start = i;
			while (i < para.length() && para[i] != ' ' && isNum(para[i]))
			{
				i++;
			}
			string currentNum = para.substr(start, i);
			double temp = atof(currentNum.c_str());
			solver.push(temp);
		}
		else if (para[i] == ' ')
		{
			i++;
		}
		else if (precedence(para[i]) != -1)
		{
			try {
				double val2 = solver.pop();
				double val1 = solver.pop();

				if (para[i] == '/' && val2 == 0) {
					throw std::exception("Cannot divide by 0!");
				}
				else {
					solver.push(calculus(val1, val2, para[i]));
				}
				i++;
			}
			catch (const std::exception& e) {
				cerr << e.what() << endl;
				exc = 1;
				return 0;
			}
		}
		else
		{
			cerr << "Invalid character in equation!";
			return 0;
		}
	}

	return solver.pop();
}