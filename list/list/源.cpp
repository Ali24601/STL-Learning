#include<iostream>  
#include<string>  
#include<list>  
using namespace std;
typedef list<int> LISTINT;

int main()
{
	LISTINT test;
	test.push_back(1);
	test.push_back(5);
	test.push_back(3);
	test.push_back(10);

	LISTINT test2;
	test2.push_back(2);
	test2.push_back(8);
	test2.push_back(6);
	test2.push_back(9);

	//test.sort();
	//test2.sort();

	test.merge(test2);

	for (LISTINT::iterator it = test.begin(); it != test.end(); it++)
	{
		cout << *it << "\t";
	}
	cout << endl;
	cout << test.size() << "\t" << test2.size() << endl;
	return 0;
}