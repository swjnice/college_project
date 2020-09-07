#ifndef HW2_CALCULATOR_H
#define HW2_CALCULATOR_H

#include <string>

using namespace std;

class Calculator
{
private:
	string exp_infix;
	int w_add;
	int w_sub;
	int w_mult;
	int w_div;
	int w_pow;

public:
	Calculator(string str);
	void setInfixExp(string str);
	void setWeight(char op, int w);
	int getWeight(char op) const;
	string getPostfixExp() const;
	int calcTwoOperands(int operand1, int operand2, char op) const;
	int calculate();
	
};

#endif