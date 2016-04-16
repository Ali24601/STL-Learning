#include <stdlib.h>
#include <vector>
int main()
{
	std::vector<int>Vec;
	Vec.assign(1, 0);
	//resize函数重新指定元素个数，并且若_Newsize大于oldsize，
	//则新添加的元素值用元素的默认构造参数初始化
	//可接受单参数（调用默认构造函数）
	Vec.resize(2, 1);
	//assign函数重新指定容器中的元素个数以及元素值
	//必须双参数
	Vec.assign(3, 2);
	//reserve函数预分配内存，不是真的改变size个数。
	//若capacity() < _Count，为容器重新分配空间。把原有的元素复制到新的容器，再释放原有容器的空间。
	//否则，不做任何处理
	//reserve只能扩大capacity()，不能减小
	Vec.reserve(2);//没效果
	Vec.reserve(4);//改变capacity()
	return 0;
}