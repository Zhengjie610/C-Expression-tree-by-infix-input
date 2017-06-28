#include "ExprTree.h"
#include <sstream>
using namespace std;
#include <iostream>
#include <string>

string prefix,infix, postfix = "";
  

bool IsOperandForPost(const string & s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

// Function to verify whether a character is operator symbol or not. 
bool IsOperatorForEXP(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$' || C == '(' || C == ')')
		return true;

	return false;
}

//bool IsOperator(string C);
/*
 * Helper function that tests whether a string is a non-negative integer.
 */

 // Function to convert Infix expression to postfix 
vector<string> InfixToPostfix(vector<string> expression);

// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(string operator1, string operator2);
// Function to verify whether a character is operator symbol or not. 
bool IsOperator(string C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not. 
bool IsOperand(char C);

//Just remove the white space in the string
string removeSpaces(string input);
//Just remove the fist char of the string
string removeFirst(string input);
//the interface for three types of search
string prefixOrderO(TreeNode * root);
string infixOrder0(TreeNode* root);
string postfixOrder0(TreeNode* root);

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

bool is_number(const std::string & s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

/*
 * Helper function that converts a string to an int.
 */
int to_number(const std::string & s) {
	return atoi(s.c_str());
}

/*
 * Helper function that converts a number to a string.
 */
string to_string(const int & n) {
	std::stringstream stream;
	stream << n;
	return stream.str();
}

/*
 * Helper function that creates a TreeNode with the appropriate operator
 * when given a string that's "+", "-", "*" or "/". If the string is wrong
 * it gives a NoOp value.
 */
TreeNode * createOperatorNode(const string & op) {

	if (op == "+") return new TreeNode(Plus);
	if (op == "-") return new TreeNode(Minus);
	if (op == "*") return new TreeNode(Times);
	if (op == "/") return new TreeNode(Divide);
	return new TreeNode(NoOp);

}

/*
 * Basic constructor that sets up an empty Expr Tree.
 */
ExprTree::ExprTree() {

	//TreeNode * r;
	//r= new TreeNode(0);
	root = NULL;
	_size = 0;


}

/*
 * Constructor that takes a TreeNode and sets up an ExprTree with that node at the root.
 */
ExprTree::ExprTree(TreeNode * r) {
	root = r;
	_size = 1;

	if (root->getLeftChild() != NULL)
	{
		_size++;
	}
	if (root->getRightChild() != NULL)
	{
		_size++;
	}
}

/*
 * Destructor to clean up the tree.
 */
ExprTree::~ExprTree() {


}

/*
 * This function takes a string representing an arithmetic expression and breaks
 * it up into components (number, operators, parentheses).
 * It returns the broken up expression as a vector of strings.
 */
vector<string> ExprTree::tokenise(string expression) {

	string a;
	string s;
	string s2;
	vector<string> v;
	int b = 0;
	int e = 0;
	a = removeSpaces(expression);
	for (int i = 0; i < a.size(); i++)
	{
		if (IsOperatorForEXP(a[i]))
		{
			e = i;
			s = a.substr(b, e - b);
			if (s.size() != 0) {
				v.push_back(s);
			}
			s2 = a[i];
			v.push_back(s2);
			b = e + 1;

		}

	}
	s = a.substr(b, a.size() - b);
	if (s.size() != 0) {

		v.push_back(s);
	}
	return  v;

}

/*
 * This function takes a vector of strings representing an expression (as produced
 * by tokenise(string), and builds an ExprTree representing the same expression.
 */
ExprTree ExprTree::buildTree(vector<string> tokens) {
	
	ExprTree tree;
	TreeNode* r = tree.getRoot();
	vector<string> toPost;
	toPost = InfixToPostfix(tokens);
	stack<TreeNode *> st;
	TreeNode * t, *t1, *t2;

	for (int i = 0; i < toPost.size(); i++)
	{
		// If operand, simply push into stack
		if (!IsOperator(toPost[i]))
		{
			t = new TreeNode(to_number(toPost[i]));
			st.push(t);
		}
		else // operator
		{
			t = createOperatorNode(toPost[i]);

			// Pop two top nodes
			t1 = st.top(); // Store top
			st.pop();      // Remove top
			t2 = st.top();
			st.pop();

			//  make them children
			t->setLeftChild(t2);
			t->setRightChild(t1);

			// Add this subexpression to stack
			st.push(t);
		}


	}



	t = st.top();
	st.pop();
	r = t;
	return r;

}

/*
 * This function takes a TreeNode and does the maths to calculate
 * the value of the expression it represents.
 */
int ExprTree::evaluate(TreeNode * n) {


	if (n->getLeftChild() == NULL && n->getRightChild() == NULL)
		return n->getValue();
	else
	{
		int result = 0;
		int left = evaluate(n->getLeftChild());
		int right = evaluate(n->getRightChild());
		Operator op = n->getOperator();

		//while (op)
		switch (op)
		{
		case 1:
			result = left + right;
			break;
		case 2:
			result = left - right;
			break;
		case 3:
			result = left * right;
			break;
		case 4:
			result = left / right;
			break;
		default:
			result = left + right;
			break;
		}
		return result;
	}
}

/*
 * When called on an ExprTree, this function calculates the value of the
 * expression represented by the whole tree.
 */
int ExprTree::evaluateWholeTree() {

	TreeNode* wholetree = getRoot();//Get the whole tree from getRoot()

	return evaluate(wholetree);
}

/*
 * Given an ExprTree t, this function returns a string
 * that represents that same expression as the tree in
 * prefix notation.
 */
string ExprTree::prefixOrder(const ExprTree & t) {

	return removeFirst(prefixOrderO(t.root));
	
}

string prefixOrderO(TreeNode * root)
{

	if (root == NULL)
		return "";
	prefix+=" "+root->toString();
	//prefix += " " + root->toString();
	prefixOrderO(root->getLeftChild());
	prefixOrderO(root->getRightChild());
	return prefix;

}


/*
 * Given an ExprTree t, this function returns a string
 * that represents that same expression as the tree in
 * infix notation.
 */
string ExprTree::infixOrder(const ExprTree & t) {

	return removeFirst(infixOrder0(t.root));
}

string infixOrder0(TreeNode* root)

{
	if (root == NULL)
		return "";
	infixOrder0(root->getLeftChild());
	infix += " " + root->toString();
	infixOrder0(root->getRightChild());

	return infix;
}




/*
 * Given an ExprTree t, this function returns a string
 * that represents that same expression as the tree in
 * postfix notation.
 */
string ExprTree::postfixOrder(const ExprTree & t) {


	return removeFirst(postfixOrder0(t.root));

}


string postfixOrder0(TreeNode* root)
{
	if (root == NULL)
		return "";
	postfixOrder0(root->getLeftChild());
	postfixOrder0(root->getRightChild());
	postfix += " " + root->toString();
	
	return postfix;
}

/*
 * Returns the size of the tree. (i.e. the number of nodes in it)
 */
int ExprTree::size() { return _size; }

/*
 * Returns true if the tree contains no nodes. False otherwise.
 */
bool ExprTree::isEmpty() { return _size == 0; }

TreeNode * ExprTree::getRoot() { return root; }




///////////////////////////POST///////////////////////////////////////
// 


// Function to evaluate Postfix expression and return output
// It returns a string of vector of postfix 
vector<string> InfixToPostfix(vector<string> expression)
{	

	vector<string> post; // Declaring a empty vector for string tokenise
	string temp;

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
		/*if (op == "$")
			weight = 3;
		break;
*/
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






///////////////////////////////////////////////


string removeSpaces(string input)
{
	int length = input.length();
	for (int i = 0; i < length; i++) {
		if (input[i] == ' ')
			input.erase(i, 1);
	}
	return input;
}
string removeFirst(string input)
{
	string output = input.substr(1, input.length());

	return output;
}