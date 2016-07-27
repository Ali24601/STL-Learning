#include <iostream>
#include <vector>
using namespace std;
typedef class tagCVector2
{
public:
	tagCVector2()
	{
		u = v = 0.0f;
	}
	tagCVector2(const tagCVector2& p1)
	{
		u = p1.u;
		v = p1.v;
	}
	float u, v;
}CVector2;

//三维向量
//用来描述坐标、法线
class CVector3
{
public:
	float x, y, z;
public:
	CVector3()
	{
		x = y = z = 0.0f;
	}
	CVector3 (const CVector3 & p1)
	{
		x = p1.x;
		y = p1.y;
		z = p1.z;
	}
	CVector3(const CVector2 & p1)
	{
		x = p1.u;
		y = 0.0f;
		z = p1.v;
	}
	CVector3  & operator=(const CVector3 & p1)//jiang 10.1 改
	{
		x = p1.x;
		y = p1.y;
		z = p1.z;
		return *this;
	}

	CVector3  & operator=(const CVector2 & p1)//sll 2016.5.9
	{
		x = p1.u;
		y = 0.0f;
		z = p1.v;
		return *this;
	}
};
int main(void)
{
	std::vector<CVector2> V2LIST;
	for (int i = 0; i < 10; ++i)
	{
		CVector2 v2;
		v2.u = v2.v = (float)i;
		V2LIST.push_back(v2);
	}
	std::vector<CVector3> V3LIST=V2LIST;
	//for (size_t i = 0; i < V2LIST.size(); ++i)
	//{
	//	CVector2 v2;
	//	CVector3 v3=v2,v4;
	//	v4 = v2;
	//	V3LIST.push_back(v2);
	//}
	return 0;
}