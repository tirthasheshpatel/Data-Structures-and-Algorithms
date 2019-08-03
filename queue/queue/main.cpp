#include <iostream>
#include "Queue.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
	Queue<int> q;
	for (int i = 0; i < 10; i++) q.enqueue(i);
	for (int i = 0; i < q.size(); i++) cout << q[i] << " "; cout << endl;
}