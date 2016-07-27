#include <iostream>
using namespace std;
class test1
{
public:
	void operator()(int x)
	{
		cout << x << endl;
	}
};
void test2(int x)
{
	cout << x << endl;
}
template<class OP> void f(OP op) {
	op(10);
}
int main()
{
	f(test1());
 	f(test2);
	return 0;
}