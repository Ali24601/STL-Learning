#include <stdlib.h>
#include <vector>
int main()
{
	std::vector<int>Vec;
	Vec.assign(1, 0);
	//resize��������ָ��Ԫ�ظ�����������_Newsize����oldsize��
	//������ӵ�Ԫ��ֵ��Ԫ�ص�Ĭ�Ϲ��������ʼ��
	//�ɽ��ܵ�����������Ĭ�Ϲ��캯����
	Vec.resize(2, 1);
	//assign��������ָ�������е�Ԫ�ظ����Լ�Ԫ��ֵ
	//����˫����
	Vec.assign(3, 2);
	//reserve����Ԥ�����ڴ棬������ĸı�size������
	//��capacity() < _Count��Ϊ�������·���ռ䡣��ԭ�е�Ԫ�ظ��Ƶ��µ����������ͷ�ԭ�������Ŀռ䡣
	//���򣬲����κδ���
	//reserveֻ������capacity()�����ܼ�С
	Vec.reserve(2);//ûЧ��
	Vec.reserve(4);//�ı�capacity()
	return 0;
}