#include "2jjalloc.h"
#include<vector>
#include<iostream>
using namespace std;
int main()
{
	{
		int ia[5] = { 0,1,2,3,4 };
		unsigned int i;

		vector<int, JJ::allocator<int> > iv(ia, ia + 5);//ʹ����JJ::mallocator��alloc�������ڴ� 
		for (i = 0; i<iv.size(); i++)
		{
			cout << iv[i] << "\t";
		}
		cout << endl;
		//Ϊʲôû����JJ::mallocator��destroy�������ڴ棬���Զ�����vector���������������� ������������ָ���˿ռ���������JJ::mallocator�˰�
	}

	return 0;
}