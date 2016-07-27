// Example program
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
	vector<int> v;
	v.reserve(10);

	for (int i = 0; i<7; i++)
		v.push_back(i);

	try
	{
		int iVal1 = v[7];  // not bounds checked - will not throw
		//int iVal2 = v.at(7); // bounds checked - will throw if out of range
	}
	catch (const exception& e)
	{
		cout << e.what();
	}
	return 0;
}
