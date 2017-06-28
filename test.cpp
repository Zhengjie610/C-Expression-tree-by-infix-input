#include "ExprTree.h"
#include <sstream>
using namespace std;
#include <iostream>
#include <string>
#include <vector>

bool IsOperator(char C);
string removeSpaces(string input);
vector<string> ExprTree(string expression)
{
	string a;
	string s;
	string s2;
	vector<string> v;
	int b = 0;
	int e = 0;
	a = removeSpaces(expression);
	cout << a.size() << endl;
	cout << a[0] << endl;

	/*(1111 + 2) �����������
	������ʱ����0��λ �жϽ�ȥ
	if (s.size() != 0) ���������ˡ�
	s2 = a[i];��
	v.push_back(s2); ���������
	b=1���������������ţ��ߵ������λ��+
	�жϳɹ����ǰ��Ķ�����a.substr(1, 5 - 1)
	1111push��ȥ����������a[i] ���ǽ�+��������
	�õ���1111+ Ȼ��ʼ������)7��λ e=7 b=6
	���ǽ�bָ����+���� Ȼ��a.substr(6, 7 - 6)
	������2�Ž�ȥs2 = a[i]; a[i]���ǣ�	
	*/
	for (int i = 0; i < a.size(); ++i)
	{
		if (IsOperator(a[i]))
		{
			e = i;
			s = a.substr(b, e - b);
			if (s.size() != 0) {
				v.push_back(s);
				cout << "�жϲ������е�S " <<  s  << endl;
				cout << "b= " << b << "e= " << e << endl;
				
			}
			s2 = a[i];
			v.push_back(s2);
			b = e + 1;
			cout << "�жϲ��������e " << s2 << endl;
			cout << "b= " << b << "e= " << e << endl;
			
		}

	}
	
	s = a.substr(b, a.size() - b);
	if (s.size() != 0) {

		v.push_back(s);
		cout << "�����s " << s << endl;
	}
}
bool IsOperator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$' || C == '(' || C == ')')
		return true;

	return false;
}

string removeSpaces(string input)
{
	int length = input.length();
	for (int i = 0; i < length; i++) {
		if (input[i] == ' ')
			input.erase(i, 1);
	}
	return input;
}



//int main()
//{
//	string line, word;
//	while (getline(cin, line))
//	{
//		stringstream stream(line);
//		cout << stream.str() << endl;
//		while (stream >> word) { cout << word << endl; }
//	}
//	return 0;
//}
et* constructTree(char postfix[])
{
	stack<et *> st;
	et *t, *t1, *t2;

	// Traverse through every character of
	// input expression
	for (int i = 0; i < strlen(postfix); i++)
	{
		// If operand, simply push into stack
		if (!isOperator(postfix[i]))
		{
			t = newNode(postfix[i]);
			st.push(t);
		}
		else // operator
		{
			t = newNode(postfix[i]);

			// Pop two top nodes
			t1 = st.top(); // Store top
			st.pop();      // Remove top
			t2 = st.top();
			st.pop();

			//  make them children
			t->right = t1;
			t->left = t2;

			// Add this subexpression to stack
			st.push(t);
		}
	}

	//  only element will be root of expression
	// tree
	t = st.top();
	st.pop();

	return t;
}