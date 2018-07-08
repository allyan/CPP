#ifndef __BITSET_H__
#define __BITSET_H__

#include <iostream>
#include <stddef.h>
#include <climits>
#include <cstring>

template<size_t SIZE, typename T = unsigned int>
class Bitset
{
public:
	explicit Bitset(const char* data);
	
	bool operator[](size_t index) const;
	typename Bitset<SIZE, T>::BitProxy operator[](size_t index);

	bool getBit(size_t index);
	void setBit(size_t index, bool val); 

	Bitset& operator|=(const Bitset& other);
	Bitset& operator&=(const Bitset& other);
	Bitset& operator^=(const Bitset& other);

	bool operator==(const Bitset& other);
	bool operator!=(const Bitset& other);


	bool isAny() const;
	bool isAll() const;
	bool isNone() const;

private:
	T arr[(SIZE / sizeof(T) / CHAR_BIT) + 1];

/*--------------- class BitProxy --------------------*/
 	class BitProxy 
 	{
    public:
	    BitProxy(Bitset<SIZE,T>& that, size_t index)
	    : bits(that)
	    , bitIndex(index)
	    {}
	   
	    BitProxy& operator=(bool val)
	    {
	        bits.setBit(bitIndex, val);
	    }
	   
	    operator bool(){
	        return bits.getBit(bitIndex);
	    }
       
    private:
        size_t bitIndex;
        Bitset<SIZE,T>& bits;

    }; // class BitProxy
}; // class Bitset


template<size_t SIZE, typename T>
Bitset<SIZE, T>::Bitset(const char* data)
{
	unsigned int mask = 1 , lastIndex = strlen(data) - 1, n = 0;
	memset(arr, 0, sizeof(arr));

	for (int i = 0; i < SIZE; ++i)
	{
		arr[i / (CHAR_BIT*sizeof(T))] |= (((data[lastIndex--] - '0') & 1) << i);
	}
}


template<size_t SIZE, typename T>
bool Bitset<SIZE, T>::getBit(size_t index)
{
	return (arr[((SIZE / sizeof(T) / CHAR_BIT) + 1) - (index / (CHAR_BIT*sizeof(T)))] 
		& (1 << (index % (CHAR_BIT*sizeof(T)))));
}

template<size_t SIZE, typename T>
void Bitset<SIZE, T>::setBit(size_t index, bool val)
{
	(val) 
	? (arr[index / (CHAR_BIT*sizeof(T))] |= (1 << (index % (CHAR_BIT*sizeof(T)))))
	: (arr[index / (CHAR_BIT*sizeof(T))] &= ~(1 << (index % (CHAR_BIT*sizeof(T)))));
}

template<size_t SIZE, typename T>
Bitset<SIZE, T>& Bitset<SIZE, T>::operator|=(const Bitset<SIZE, T>& other)
{
	for (unsigned int i = 0; i < (SIZE / sizeof(T) / CHAR_BIT) + 1; ++i)
		arr[i] |= other.arr[i];
}

template<size_t SIZE, typename T>
Bitset<SIZE, T> operator|(const Bitset<SIZE, T>& lhs, const Bitset<SIZE, T>& rhs)
{
	Bitset<SIZE, T> tmp(lhs);

	tmp |= rhs;
	
	return tmp;
}

template<size_t SIZE, typename T>
Bitset<SIZE, T>& Bitset<SIZE, T>::operator&=(const Bitset<SIZE, T>& other)
{
	for (unsigned int i = 0; i < (SIZE / sizeof(T) / CHAR_BIT) + 1; ++i)
		arr[i] &= other.arr[i];
}

template<size_t SIZE, typename T>
Bitset<SIZE, T> operator&(const Bitset<SIZE, T>& lhs, const Bitset<SIZE, T>& rhs)
{
	Bitset<SIZE, T> tmp(lhs);

	tmp &= rhs;
	
	return tmp;
}

template<size_t SIZE, typename T>
Bitset<SIZE, T>& Bitset<SIZE, T>::operator^=(const Bitset<SIZE, T>& other)
{
	for (unsigned int i = 0; i < (SIZE / sizeof(T) / CHAR_BIT) + 1; ++i)
		arr[i] ^= other.arr[i];
}

template<size_t SIZE, typename T>
Bitset<SIZE, T> operator^(const Bitset<SIZE, T>& lhs, const Bitset<SIZE, T>& rhs)
{
	Bitset<SIZE, T> tmp(lhs);

	tmp ^= rhs;
	
	return tmp;
}

template<size_t SIZE, typename T>
bool Bitset<SIZE, T>::operator==(const Bitset& other)
{
	for (unsigned int i = 0; i < (SIZE / sizeof(T) / CHAR_BIT) + 1; ++i)
     if(arr[i] != other.arr[i])
     	return false;

     return true;
}

template<size_t SIZE, typename T>
bool Bitset<SIZE, T>::operator!=(const Bitset& other)
{
	return !(*this == other);
}

template<size_t SIZE, typename T>
bool Bitset<SIZE, T>::isNone() const
{
	for (unsigned x : arr)
     if(x)
     	return false;

     return true;
}

template<size_t SIZE, typename T>
bool Bitset<SIZE, T>::isAll() const
{
	for (unsigned x : arr)
     if(!x)
     	return false;

     return true;
}

template<size_t SIZE, typename T>
bool Bitset<SIZE, T>::isAny() const
{
	for (unsigned x : arr)
     if(x)
     	return true;

     return false;
}

template<size_t SIZE, typename T>
typename Bitset<SIZE, T>::BitProxy Bitset<SIZE, T>::operator[](size_t index)
{
	return BitProxy(*this, index);
}

template<size_t SIZE, typename T>
bool Bitset<SIZE, T>::operator[](size_t index) const
{
	return (arr[index / (CHAR_BIT*sizeof(T))] & (1 << (index % (CHAR_BIT*sizeof(T)))));
}


template<size_t SIZE, typename T>
std::ostream& operator<< (std::ostream& os, const Bitset<SIZE, T>& set)
{
	for(int i = 0; i < SIZE; ++i)
    	os << set[i];
  
    return os;
}

#endif /* __BITSET_H__ */
