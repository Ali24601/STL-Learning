/*************************************************************************
> File Name: test4.cpp
> Author: SongLee
************************************************************************/
#include<iostream> 
#include<algorithm> 
#include<string> 
using namespace std;

// 自定义序函数（二元谓词） 
bool myfunction(char i, char j)
{
	return i > j;
}

bool Compare(string s1, string s2)
{
	// 采用泛型算法对s1,s2排序，sort()采用的是快速排序算法 
	sort(s1.begin(), s1.end(), myfunction);
	sort(s2.begin(), s2.end(), myfunction);
	if (!s1.compare(s2)) // 相等返回0 
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