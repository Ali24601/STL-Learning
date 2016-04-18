#include<iostream>
using namespace std;
void stringFilter(const char *pInputStr, long lInputLen, char *pOutputStr)
{
	bool alreadyshowed[26] = { false };
	long j = 0;
	for (long i = 0; i < lInputLen; ++i)
	{
		int index = pInputStr[i] - 'a';
		if (!alreadyshowed[index])
		{
			alreadyshowed[index] = true;
			pOutputStr[j++] = pInputStr[i];
		}
	}
}
void stringZip(const char *pInputStr, long lInputLen, char *pOutputStr)
{
	char *temp = new char[lInputLen];
	memset(temp, 0, lInputLen*sizeof(char));
	long j = -1;
	int mult = 0;
	long i = lInputLen - 1;
	temp[++j] = pInputStr[i--];
	mult++;
	for (; i >= 0;--i)
	{
		if (temp[j] != pInputStr[i])
		{
			if (mult > 1)
				temp[++j] = mult+'0';
			mult = 1;
			temp[++j] = pInputStr[i];
		}
		else
		{
			++mult;
		}
		if (i == 0&&mult>1)
		{
			temp[++j] = mult + '0';
		}
	}
	long k = 0;
	while(j>=0)
		pOutputStr[k++] = temp[j--];
	delete[]temp;
}

void arithmetic(const char *pInputStr, long lInputLen, char *pOutputStr)
{
	bool add;
	long i = 0;
	long j = 0;
	int num1 = 0;
	int num2=0;
	int result = 0;
	while (pInputStr[i] != '\x20')
	{
		num1 *= 10;
		num1 += pInputStr[i++] - '0';
	}
	++i;
	if (pInputStr[i] == '+')
	{
		add = true;
		++i;
	}
	else if (pInputStr[i] == '-')
	{
		add = false;
		++i;
	}
	else 
	{
		pOutputStr[j++] = '0';
		return;
	}
	++i;
	while (i<lInputLen-1)
	{
		num2 *= 10;
		num2 += pInputStr[i++] - '0';
	}
	if (add)
	{
		result = num1 + num2;
	}
	else
	{
		result = num1 - num2;
	}
	if (result < 0)
	{
		result = -result;
		pOutputStr[j++] = '-';
	}
	int k = 0;
	char *temp = new char[lInputLen];
	memset(temp, 0, lInputLen*sizeof(char));
	while (result)
	{
		temp[k++] = result % 10 + '0';
		result /= 10;
	}
	k--;
	while(k!=-1)
		pOutputStr[j++] = temp[k--];	
	delete[]temp;
}
int main()
{
	const char *input = "4 + 7";	
	long num = 6;
	char *output = new char[num];
	memset(output, 0, num*sizeof(char));
	//stringFilter(input, num, output);
	//stringZip(input, num, output);
	arithmetic(input, num, output);
	return 0;
}