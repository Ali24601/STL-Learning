#pragma once
#ifndef _JJALLOC_H
#define _JJALLOC_H
#include<new> 		//for placement new 
#include<cstddef>	//for ptrdiff_t,size_t
#include<cstdlib>	//for exit()
#include<climits>	//for UINT_MAXʮ���Ƶ����ֵ 
#include<iostream>	//for cerr

namespace JJ
{
	/*****************ptrdiff_t��size_t����*****size_type��difference_type����********************
	****ptrdiff_t:signed���ͣ�ͨ��������ָ����������Ľ�����������Ǹ���������Ϊָ����������и���
	****size_t:unsigned���ͣ�����ָ�����鳤�ȣ����ǷǸ�������
	****size_type:unsigned���ͣ�������Ԫ�س��Ȼ��±�vector<int>::size_type i=0;
	****difference_type:signed���ͣ���ʾ��������࣬vector<int>::difference_type=iter1-iter2
	****ǰ����λ�ڱ�׼���std�ڣ�������Ϊstl��������
	*********************************************************************************************/
	template<class T>
	inline T* _allocate(ptrdiff_t size, T*)
	{
		std::cout << "I'm _allocate in simple_jjalloc!" << std::endl;
		/**************************new_handler��set_new_handler***********************************
		****new_handler:�ڴ����ʧ�ܺ󣬵��õĴ�������
		****set_new_handler:�����Ǳ�ָ����new_handler����ָ�룬���ز���Ҳ��new_handler�Ǳ��滻����new_handler
		*****************************************************************************************/
		std::set_new_handler(0);
		/****************::***********************************************************************
		****"::":ȫ�����á�����::luo����Ǹ�ȫ�ֱ�������luo���Ǹ��ֲ�����
		****"::":�����á�����Node::function()
		****"::":���ֿռ䡣����std::size_t
		*****************************************************************************************/
		T *tmp = (T*)(::operator new((size_t)(size*sizeof(T))));
		if (tmp == 0)//û��ǰ���std::set_new_handler(0);���ڴ����ʧ�ܺ���쳣���ú������滻������ִ�в������ 
		{
			std::cout << "failed!" << std::endl;
			std::cerr << "out of memory" << std::endl;
			exit(1);
		}
		return tmp;
	}

	template<class T>
	inline void _deallocate(T* buffer)
	{
		::operator delete(buffer);
	}
	/************************************new��������̬*******************************************
	****new operator:����ƽ���õ�new��ͨ���������£�1.��operator new�����ڴ������2.���ù��캯����ʼ���ǿ��ڴ棬3.����ַת������ָ��
	����������ڶ��Ͻ���������ôӦ��ʹ��new operator�������ṩ��ȫ�ķ���
	****operator new:��Ĭ����������Ȼ���÷����ڴ�Ĵ��룬���ԴӶ��ϵõ�һ�οռ䣬�ɹ��ͷ��أ�ʧ�ܾ͵���new_hander���ظ�ǰ����̣�ֱ���׳��쳣
	��������Ƿ����ڴ棬��ôӦ�õ���operator new������ʼ����������ְ��֮�ڡ�����Ĭ�ϵ��ڴ������̲����⣬�Ǿ�������
	****placement new:����ʵ�ֶ�λ���죬����ͨ������ѡ����ʵĹ��캯����
	�������һ���ѻ�õ��ڴ��ｨ��һ�������Ǿ͸���placement new
	********************************************************************************************/
	template<class T1, class T2>
	inline void _construct(T1* p, const T2& val)
	{
		new(p) T1(val);//pΪ�ǿ��ڴ��ַ��T1()Ϊָ�����캯�����˾�Ϊp->T1::T1(val); 
		std::cout << "I'm _construct!" << std::endl;
	}

	template<class T>
	inline void _destroy(T* ptr)
	{
		std::cout << "I'm _destroy!" << std::endl;
		ptr->~T();
	}

	template<class T>
	class allocator
	{
	public:
		typedef T value_type;//ΪʲôҪ���¶��壬ԭ��������
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;


		template<class U>
		struct rebind//�����ã����� 
		{
			typedef allocator<U> mother;
		};

		pointer allocate(size_type n, const void* hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}

		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		void construct(pointer p, const_reference val)
		{
			_construct(p, val);
		}

		void destroy(pointer p)
		{
			_destroy(p);
		}

		pointer address(reference x)
		{
			return (pointer)&x;
		}

		const pointer const_address(const_reference x)
		{
			return (const pointer)&x;
		}

		size_type max_size()const
		{
			return size_type(UINT_MAX / sizeof(value_type));
		}
	};
}
#endif