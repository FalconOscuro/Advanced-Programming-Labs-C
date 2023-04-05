#include <iostream>
using namespace std;

int mymax(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void MyFunc(int a, bool c, char d)
{
	return;
}

int main(int, char**) {

	int a = 10;
	int b = 20;

	int max = mymax(a, b);
	MyFunc(2, false, 'c');

	cout << "a=" << a << ", b=" << b << endl;
	cout << "max=" << max << endl;

	return 0;
}

