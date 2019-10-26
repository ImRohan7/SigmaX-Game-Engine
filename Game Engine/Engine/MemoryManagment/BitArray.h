#pragma once
#include "assert.h"
#include "iostream"
#include "stdint.h"
#include <cstring>
#include <intrin.h>

#pragma intrinsic(_BitScanForward)

class BitArray
{
public:

	BitArray() { m_pBits = NULL; }

	static BitArray* Create(void* i_ptr, bool i_bInitToZero) 
	{
		BitArray* temp = static_cast<BitArray*>(i_ptr);
		temp->Initialize(i_ptr, i_bInitToZero);
		return temp;
	}

	// Constructor
	void Initialize(void * i_ptr, bool i_bInitToZero)
	{
		memset(&m_pBits, 0, 1);
	}

	// Getter
	inline uint8_t get() { return m_pBits; }

	// Find if Nth bit is set
	inline bool IsSet(unsigned int i_N)
	{
		uint8_t Tester = 1UL << i_N;
		uint8_t temp = Tester;
		Tester &= m_pBits;
		if (Tester == temp) { return true; }
		else{	return false;	}
	}

	// Negate
	inline void Negate() { 
		m_pBits = ~(m_pBits); 
	}

	// Set Nth Bit
	inline void SetBit(unsigned int i_N)
	{
		m_pBits |= (1U << i_N);
	}

	// Set All
	inline void SetALL()
	{
		int i = 8;
		while (i >= 0)
		{
			SetBit(i--);
		}
	}

	// Clear Nth Bit
	inline void ClearBit(unsigned int i_N)
	{
		m_pBits &= ~(1U << i_N);
	}

	// Find first set
	unsigned char findFirstSet(unsigned long &i_index) 
	{
		unsigned char IsNonZero;
		unsigned long mask = ~(m_pBits);

#if _32_IT_IS
		IsNonZero = _BitScanForward(&i_index, mask);
#elif _64_IT_IS
		IsNonZero = _BitScanForward64(&i_index, mask);
#endif
		
		return IsNonZero;
	}

	// Clear ALL
	inline void ClearALL()
	{
		int i = 8;
		while (i >= 0)
		{
			ClearBit(i--);
		}
	}

	// Find Nth Bit
	inline unsigned int FindBit(const unsigned int i_N ) const
	{
		unsigned int Nth;
		Nth = (m_pBits >> i_N) & 1U;
		return Nth;
	}

	// Print all Bits
	inline void PrintBits() 
	{
		int i = 7;
		std::cout<<std::endl;
		while (i >= 0)
		{
			std::cout << FindBit(i) << " ";
			i--;
		}
	}

private:
	uint8_t m_pBits;
};