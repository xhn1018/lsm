#include<iostream>
#include<thread>
using namespace std;
void f1(int n) {
	cout << n << endl;
}
int main()
{
	int n = 1;
	thread t1(f1, n);
	t1.detach();
	system("pause");
}