#include<iostream>
#include<string>
#include <queue>
#include <stack>
#include <cstdlib>
#include<vector>
using namespace std;

bool isdigit(const char & c) {

	switch (c) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': return true;
	}

	return false;

}

bool IsOperandForPost(const string & s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}


// Function to convert Infix expression to postfix 
vector<string> InfixToPostfix(vector<string> expression);

// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(string operator1, string operator2);

// Function to verify whether a character is operator symbol or not. 
bool IsOperator(string C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not. 

vector<string> post;
string temp;

// Function to evaluate Postfix expression and return output
vector<string> InfixToPostfix(vector<string> expression)
{
	// Declaring a Stack from Standard template library in C++. 
	stack<string> S;
	string postfix = ""; // Initialize postfix as empty string.

	for (int i = 0; i < expression.size(); i++) {

		// Scanning each character from left. 
		// If character is a delimitter, move on. 
		if (expression[i] == " " || expression[i] == ",") continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back. 
		else if (IsOperator(expression[i]))
		{
			while (!S.empty() && S.top() != "(" && HasHigherPrecedence(S.top(), expression[i]))
			{
				temp = S.top();
				post.push_back(temp);
				postfix += S.top();
				S.pop();

			}
			S.push(expression[i]);
		}
		// Else if character is an operand
		else if (IsOperandForPost(expression[i]))
		{
			temp = expression[i];
			post.push_back(temp);
			postfix += expression[i];

		}

		else if (expression[i] == "(")
		{
			S.push(expression[i]);
		}

		else if (expression[i] == ")")
		{
			while (!S.empty() && S.top() != "(") {
				temp = S.top();
				post.push_back(temp);
				postfix += S.top();
				S.pop();

			}
			S.pop();
		}
	}

	while (!S.empty()) {
		temp = S.top();
		post.push_back(temp);
		postfix += S.top();
		S.pop();

	}

	return post;
}




// Function to verify whether a character is english letter or numeric digit. 
// We are assuming in this solution that operand will be a single character


// Function to verify whether a character is operator symbol or not. 
bool IsOperator(string C)
{
	if (C == "+" || C == "-" || C == "*" || C == "/" || C == "$")
		return true;

	return false;
}

// Function to verify whether an operator is right associative or not. 
int IsRightAssociative(string op)
{
	if (op == "$") return true;
	return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence. 
int GetOperatorWeight(string op)
{

	int weight = -1;

	while (IsOperator(op))
	{
		if (op == "+")
			weight = -1;
			break;
		if (op == "-")
			weight = 1;
		break;
		if (op == "*")
			weight = -1;
			break;
		if (op == "/")
			weight = 2;
		break;
		if (op == "$")
			weight = 3;
		break;

	}

	return weight;
}

// Function to perform an operation and return output. 
int HasHigherPrecedence(string op1, string op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	// If operators have equal precedence, return true if they are left associative. 
	// return false, if right associative. 
	// if operator is left-associative, left one should be given priority. 
	if (op1Weight == op2Weight)
	{
		if (IsRightAssociative(op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ? true : false;
}


int main()
{

	vector<string> v;
	vector<string> a;
	
	
	v.push_back("4");
	v.push_back("+");
	v.push_back("3");
	v.push_back("+");
	v.push_back("2");
	v.push_back("+");
	v.push_back("1");

	a = InfixToPostfix(v);
	
	//cout << a.size() << endl;
	for (int i = 0; i < a.size(); i++)
	{

		cout << a[i] << endl;
	}

}