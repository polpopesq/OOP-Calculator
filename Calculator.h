#pragma once
#include <iostream>
#include <string>

using namespace std;

class Calculator {
public:
	Calculator();
	string solveExp(string expression);
	int exc;

private:
	bool correctExpression(string expression);
	string eraseSpaces(string expression);
	void dealWithNegativeSign(string& expression);
	void replaceComma(string& expression);
	string calculateSection(string expression, int start, int end);
	void squareToRound(string& expression);
	double numFromString(string num);
	bool isNum(char c);
	int precedence(char c);
	string toRPN(string expression);
	double calculus(double x, double y, char sign);
	double solvePara(string para);
};