#ifndef __IM_VECTOR_HEADER__
#define __IM_VECTOR_HEADER__
	  
#include <cstdio>
#include <memory.h>
#include <cassert>
#include "common_util.h"
using namespace std;
template<typename T>
class im_vector_t
{
	uint32_t _cap;
	uint32_t tail;
	uint32_t _max_cap;
	T *array;
public:
	im_vector_t<T>(uint32_t max_cap):_cap(0),tail(0),_max_cap(max_cap),array(NULL)
	{
		if (_max_cap <= 2)
		{
			_max_cap = 3;
		}
	};
	
	~im_vector_t<T>()
	{
		if (array != NULL)
		{
			delete [] array;
		}
	}
	int create(uint32_t cap)
	{
		if (cap == 0)
		{
			cap = 1;
		}

		if(cap>_max_cap)
		{
			cap = _max_cap;
		}
			
		_cap=0;
		tail=0;
		array=new (std::nothrow) T[cap];
		if(array==NULL)
		{
			return -1;
		}
		_cap=cap;
		return 0;
	};
	int push_back(const T& item)
	{
		if(_cap==tail&&_cap==_max_cap)
		{
			return -1;
		}
		if(_cap>tail)
		{
			array[tail++]=item;
			return 0;
		}
		int new_cap=_max_cap<2*_cap?_max_cap:2*_cap;
		T* new_array=new (std::nothrow) T[new_cap];
		if(new_array==NULL)
		{
			return -1;
		}
		PDEBUG("vector malloc %u", new_cap);
		
		memcpy(new_array,array,sizeof(T)*tail);
		delete [] array;
		array=new_array;
		_cap=new_cap;
		array[tail++]=item;
		return 0;
	};
	inline void clear(){tail=0;};
	inline const T& operator[](int pos){return array[pos];};
	inline uint32_t size(){return tail;};
	inline T * begin(){return &array[0];};
	inline T * end(){return &(array[0])+tail;};
};

#endif
