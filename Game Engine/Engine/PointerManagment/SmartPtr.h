#pragma once
#include "../Console/ConsolePrint.h"
#include "stdint.h"
#include <assert.h>

	struct reference_Counter {

		typedef uint64_t	ref_counter;

		reference_Counter() : smartCount(0), weakCount(0)
		{ }

		reference_Counter(ref_counter i_smart, ref_counter i_weak) :
			smartCount(i_smart), weakCount(i_weak)
		{ }

		reference_Counter(const reference_Counter & i_oth)
		{
			smartCount = i_oth.smartCount;
			weakCount = i_oth.weakCount;
		}

		reference_Counter& operator=( const reference_Counter & i_oth)
		{
			smartCount = i_oth.smartCount;
			weakCount = i_oth.weakCount;

			return *this;
		}

		reference_Counter& operator=(const reference_Counter * i_oth)
		{
			smartCount = i_oth->smartCount;
			weakCount = i_oth->weakCount;

			return *this;
		}

		ref_counter smartCount;
		ref_counter weakCount;

	};

	template <class U>
	class WeakPtr;

	template <class T>
	class SmartPtr
	{
		template <class U>
		friend class WeakPtr;

		template <class U>
		friend class SmartPtr;

	public:
		SmartPtr() : m_Ptr(nullptr), m_refCount(nullptr)
		{ }

		// Constructor
		SmartPtr(T* i_ptr ) : m_Ptr(i_ptr),
			m_refCount(new reference_Counter(1, 0))
		{}
		 
		// Copy constructor [Normal One]
		SmartPtr(const SmartPtr & i_other) :
			m_Ptr(i_other.m_Ptr), m_refCount(i_other.m_refCount)
		{
			m_refCount->smartCount++;
		}

		// Copy Constructor [for pollymorphism/inherited One]
		// Eg: SmartPtr<B> X;
		//     SmartPtr<A> Y(X);
		template <class U>
		SmartPtr(const SmartPtr<U> & i_other) :
			m_Ptr(i_other), m_refCount(i_other.m_refCount)
		{	
			m_refCount->smartCount++;
		}

		// Destructor
		~SmartPtr() 
		{
			// delete if only Smart Count is zero
			m_refCount->smartCount--;
			if (m_refCount->smartCount == 0)
			{
				delete m_Ptr;
				m_Ptr = nullptr;
				if (m_refCount->weakCount == 0)
				{
					// bcz I still need this(to be accessed by WeakPtrs if they are not destroyed)
					delete m_refCount;
					m_refCount = nullptr;
				}
			}
		}

		// copy constructor
		// to create a "SmartPtr" from a "WeakPtr"
		// eg: SmartPtr<A>(WeakPtr<A>)
		SmartPtr(const WeakPtr<T> & i_oth)
		{
			if (i_oth.m_refCount->smartCount != 0)
			{
				m_refCount = i_oth.m_refCount;
				m_Ptr = i_oth.m_Ptr;
				
				m_refCount->smartCount++;
			}
			else
			{
			//	return nullptr; /// no need cz alreaady checking in calling function
				// AquireOwnership
			}
		}

		// Assignmnet Operator for Copying 
		// eg: SmartPtr<A> Ptr1 = smartPtr<A> Ptr2
		SmartPtr & operator=(const SmartPtr<T> & i_oth)
		{
			// if they are same
			if( m_Ptr = i_oth.m_Ptr)
			{ // return a reference
				return *this;
			}
			else
			{
				// release a reference 
				m_refCount->smartCount--;
				// delete if this was the last "SmartPtr"
				if (m_refCount->smartCount == 0)
				{
					delete m_Ptr;
					m_Ptr = nullptr;
					if (m_refCount->weakCount == 0)
					{
						delete m_refCount;
						m_refCount = nullptr;
					}
				}
				m_Ptr = i_oth.m_Ptr;
				m_refCount = i_oth.m_refCount;
				m_refCount->smartCount++;
				return *this;
			}
		}

		// Assignment operator for 
		// polymorphic copying
		template <class U>
		SmartPtr & operator=(const SmartPtr<U> & i_oth)
		{
			// if they are same
			if (m_Ptr = i_oth.m_Ptr)
			{ // return a reference
				return *this;
			}
			else
			{
				// release a reference 
				m_refCount->smartCount--;
				// delete if this was the last "SmartPtr"
				if (m_refCount->smartCount == 0)
				{
					delete m_Ptr;
					m_Ptr = nullptr;
					if (m_refCount->weakCount == 0)
					{
						delete m_refCount;
						m_refCount = nullptr;
					}
				}
				m_Ptr = i_oth.m_Ptr;
				m_refCount = i_oth.m_refCount;
				m_refCount->smartCount++;
				return *this;
			}
		}

		// Assignment for copying a smartPtr from a WeakPtr similar types
		SmartPtr & operator=(const WeakPtr<T> & i_oth)
		{
			
		}

		// Assignment for copying a smartPtr from a WeakPtr polymorphic types
		template <class U>
		SmartPtr & operator=(const WeakPtr<U> & i_oth)
		{

		}

		// Assignment Operator - Assigning directly from an existing pointer
		// OwningPointer<Base> BasePtr( new Base() );
		// BasePtr = new Base();
		SmartPtr & operator=(const T * i_ptr)
		{
			// delete if this was the last "SmartPtr"
			m_refCount->smartCount--;
			if (m_refCount->smartCount == 0)
			{
				delete m_Ptr;
				m_Ptr = nullptr;
				if (m_refCount->weakCount == 0)
				{
					delete m_refCount;
					m_refCount = nullptr;
				}
			}

			// new Data
			m_Ptr = i_ptr;
			// new reference
			m_refCount = new reference_Counter(1, 0);
			m_refCount->smartCount++;
			return *this;
		}

		// THIS SHOULD NOT HAPPEN IDEALLY
		// NUll Assignment Operator
		// eg: SmartPtr<A> A( new A() );
		// A = nullptr;
		// Don't really need to implement this. If it's not here it'll go through OwningPointer & operator=( OwningPointer & i_other);
		SmartPtr & operator=(std::nullptr_t i_null)
		{
			DEBUG_PRINT("Wrong Operation: Assigning a Null Ptr to SmartPtr");
			bool x = false;
			assert(x);
		}

		// Access operator
		T* operator->() const
		{
			return m_Ptr;
		}

		// get
		T* getObj() const
		{
			return m_Ptr;
		}

		// Equality comparison with Own Types
		bool operator==(const SmartPtr<T> & i_oth) const
		{
			return m_Ptr == i_oth.m_Ptr;
		}

		// Euality comparision with Polymorphic types
		template <class U>
		bool operator==(const SmartPtr<U> & i_oth) const
		{
			return m_Ptr == i_oth.m_Ptr;
		}

		// Equality comparison to compare with a WeakPtr of similar types
		bool operator==(const WeakPtr<T> & i_oth) const
		{
			return m_Ptr == i_oth.m_Ptr;
		}

		// Equality comp for WeakPtr of polymorphic types
		template <class U>
		bool operator==(const WeakPtr<U> & i_oth) const
		{
			return m_Ptr == i_oth.m_Ptr;
		}

		// Equality comp for direct pointer
		// eg: A a;
		//     SmartPtr<A> X == a;
		bool operator==(T* i_ptr)
		{
			return m_Ptr == i_ptr;
		}

		// Equality comp for null ptr
		bool operator==(std::nullptr_t null) const
		{ 
			return m_Ptr == null; 
		}

		// InEquality comparison with Own Types
		bool operator!=(const SmartPtr<T> & i_oth) const
		{
			return m_Ptr != i_oth.m_Ptr;
		}

		// InEuality comparision with Polymorphic types
		template <class U>
		bool operator!=(const SmartPtr<U> & i_oth) const
		{
			return m_Ptr != i_oth.m_Ptr;
		}

		// InEquality comparison to compare with a WeakPtr of similar types
		bool operator!=(const WeakPtr<T> & i_oth) const
		{
			return m_Ptr != i_oth.m_Ptr;
		}

		// InEquality comp for WeakPtr of polymorphic types
		template <class U>
		bool operator!=(const WeakPtr<U> & i_oth) const
		{
			return m_Ptr != i_oth.m_Ptr;
		}

		// InEquality comp for direct pointer
		bool operator!=(T* i_ptr) const
		{
			return m_Ptr != i_ptr;
		}

		// InEquality comp for null ptr
		bool operator!=(std::nullptr_t null) const
		{
			return m_Ptr != null;
		}

		// bool operator
		// if(m_Ptr)
		operator bool() const
		{
			return m_Ptr =! nullptr;
		}

		// ??
		T & operator*() const
		{
			return *m_Ptr;
		}

	private:
		T* m_Ptr;
		reference_Counter * m_refCount;
	};
