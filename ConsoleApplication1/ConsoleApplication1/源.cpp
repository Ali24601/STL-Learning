/*************************************************************************
> File Name: test4.cpp
> Author: SongLee
************************************************************************/
#include<iostream> 
#include<algorithm> 
#include<string> 
using namespace std;

// �Զ�����������Ԫν�ʣ� 
bool myfunction(char i, char j)
{
	return i > j;
}

bool Compare(string s1, string s2)
{
	// ���÷����㷨��s1,s2����sort()���õ��ǿ��������㷨 
	sort(s1.begin(), s1.end(), myfunction);
	sort(s2.begin(), s2.end(), myfunction);
	if (!s1.compare(s2)) // ��ȷ���0 
		return true;
	else
		return false;
}

int main()
{
	string s1 = "abandon";
	string s2 = "banadon";
	if (Compare(s1, s2))
		cout << "They are brother words!" << endl;
	else
		cout << "They aren't brother words!" << endl;
	return 0;
}