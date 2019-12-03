#include <iostream>
#include "Stack.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	Stack<int> s;
	for (size_t i = 0; i < 1000000000; i++) s.push_back(i);
	// for (size_t i = 0; i < s.size(); i++) cout << s[i] << " "; cout << endl;
	int poped = s.pop_back();
	cout << poped << endl;
	// cout << s.empty() << endl;
	// for (int i = 0; i < s.size(); i++) cout << s[i] << " "; cout << endl;
	// for (Stack<int>::const_iterator i = s.begin(); i < s.end(); i++) cout << *i << " ";
}