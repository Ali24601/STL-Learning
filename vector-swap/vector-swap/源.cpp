// Example program
//����ͨ��std::vector<int>(v).swap(v)��vector<int>().swap(v)
//�ﵽ�ͷ��ڴ��Ч��
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
