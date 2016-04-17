// Example program
//可以通过std::vector<int>(v).swap(v)和vector<int>().swap(v)
//达到释放内存的效果
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

	std::vector<int> vNew(v);
	cout << vNew.capacity();
	std::vector<int>(v).swap(v);
	v.clear();
	vector<int>().swap(v);
	v.push_back(1);
	return 0;
}
