#pragma once
#include "SmartPtr.h"

template <class T>
class WeakPtr
{
	template <class U>
	friend class SmartPtr;

	template <class U>
	friend class WeakPtr;

public:

	// null
	WeakPtr() : m_refCount(nullptr), m_Ptr(nullptr)
	{ }


	// for creating a WeakPtr from SmartPtr
	WeakPtr(const SmartPtr<T> & i_owner)
	{
		m_Ptr = i_owner.m_Ptr;
		m_refCount = i_owner.m_refCount;

		m_refCount->weakCount++;
	}

	// for creating a WeakPtr from SmartPtr [ Polymorphic one ]
	template<class U>
	WeakPtr(const SmartPtr<U> & i_owner)
	{
		m_Ptr = i_owner.m_Ptr;
		m_refCount = i_owner.m_refCount;

		m_refCount->weakCount++;
	}

	// Copy Constructor for copying between similar types
	WeakPtr(const WeakPtr & i_oth)
	{
		m_Ptr = i_oth.m_Ptr;
		m_refCount = i_oth.m_refCount;
		m_refCount->weakCount++;
	}

	// Copy Constructor for polymorphic one
	template<class U>
	WeakPtr(const WeakPtr<U> & i_oth)
	{
		m_Ptr = i_oth.m_Ptr;
		m_refCount = i_oth.m_refCount;
		m_refCount->weakCount++;
	}

	SmartPtr<T> AquireOwnership()
	{
		if (m_refCount->smartCount > 0)
		{
			return SmartPtr<T>(*this);
		}
		else
		{
			return SmartPtr<T>(); // create a null smartPtr
		}
	}

	~WeakPtr()
	{
		m_refCount->weakCount--;
		if (m_refCount->weakCount == 0 && m_refCount->smartCount == 0)
		{
			delete m_refCount;
			delete m_Ptr;
			m_refCount = nullptr;
			m_Ptr = nullptr;
		}
	}

	// Assignment operator similar types
	WeakPtr & operator=(const WeakPtr & i_oth)
	{
		if (m_Ptr == i_oth.m_Ptr) // if same
		{
			return *this;
		}
		else
		{	// if not null then check for delete case
			if (m_refCount != nullptr)
			{
				m_refCount->weakCount--;
				if (m_refCount->weakCount == 0 && m_refCount->smartCount == 0)
				{
					delete m_refCount;
					delete m_Ptr;
					m_refCount = nullptr;
					m_Ptr = nullptr;
				}
				// new reference
				m_Ptr = i_oth.m_Ptr;
				m_refCount = i_oth.m_refCount;
				m_refCount->weakCount++;
				return *this;
			}
		}
	}

	// Assignment operator Polymorphic types
	template <class U>
	WeakPtr & operator=(const WeakPtr<U> & i_oth)
	{
		if (m_Ptr == i_oth.m_Ptr) // if same
		{
			return *this;
		}
		else
		{	// if not null then check for delete case
			if (m_refCount != nullptr)
			{
				m_refCount->weakCount--;
				if (m_refCount->weakCount == 0 && m_refCount->smartCount == 0)
				{
					delete m_refCount;
					delete m_Ptr;
					m_refCount = nullptr;
					m_Ptr = nullptr;
				}
				// new reference
				m_Ptr = i_oth.m_Ptr;
				m_refCount = i_oth.m_refCount;
				m_refCount->weakCount++;
				return *this;
			}
		}
	}

	template<class U>
	WeakPtr & operator=(const SmartPtr<U> & i_other)
	{

	}

	WeakPtr<T> & operator=(std::nullptr_t i_null)
	{
		DEBUG_PRINT("Warning: Assigning a null ptr");
		assert(false);
	}

	// Equality comparision between similar types
	bool operator==(const WeakPtr<T> & i_oth) const
	{
		return m_Ptr == i_oth.m_Ptr;
	}

	// Equality comparison between polymorphic ones
	template <class U>
	bool operator==(const WeakPtr<U> & i_oth) const
	{
		return m_Ptr == i_oth.m_Ptr;
	}

	// equality comparison with SmartPtr of similar types
	bool operator==(const SmartPtr<T> & i_Othr) const
	{
		return m_Ptr == i_Othr.m_Ptr;
	}

	// equality comparison with SmartPtr of polymorphic types
	template <class U>
	bool operator==(const SmartPtr<U> & i_oth) const
	{
		return m_Ptr == i_oth.m_Ptr;
	}

	// direct comparison to similar types
	bool operator==(const T * i_ptr) const
	{
		return m_Ptr == i_ptr;
	}

	//direct comparison to polymorphic types
	template <class U>
	bool operator==(const U * i_ptr)
	{
		return m_Ptr == i_ptr;
	}

	// null ptr
	bool operator==(std::nullptr_t i_null) const
	{
		return m_Ptr == i_null;
	}

	// InEquality comparision between similar types
	bool operator!=(const WeakPtr<T> & i_oth) const
	{
		return m_Ptr != i_oth.m_Ptr;
	}

	// Equality comparison between polymorphic ones
	template <class U>
	bool operator!=(const WeakPtr<U> & i_oth) const
	{
		return m_Ptr != i_oth.m_Ptr;
	}

	// equality comparison with SmartPtr of similar types
	bool operator!=(const SmartPtr<T> & i_Othr) const
	{
		return m_Ptr != i_Othr.m_Ptr;
	}

	// equality comparison with SmartPtr of polymorphic types
	template <class U>
	bool operator!=(const SmartPtr<U> & i_oth) const
	{
		return m_Ptr != i_oth.m_Ptr;
	}

	// direct comparison to similar types
	bool operator!=(const T * i_ptr) const
	{
		return m_Ptr != i_ptr;
	}

	//direct comparison to polymorphic types
	template <class U>
	bool operator!=(const U * i_ptr)
	{
		return m_Ptr != i_ptr;
	}

	// null ptr
	operator bool() const
	{
		return m_Ptr != nullptr;
	}

	T & operator*() const
	{
		return *m_Ptr;
	}

// NOOOOOOOOOOO WAYYYYY
	//T* operator->() const
	//{
	//	return m_Ptr;
	//}

private:
	
	T* m_Ptr;
	reference_Counter * m_refCount;
};

