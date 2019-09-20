#pragma once

#include <assert.h>
#include <algorithm>
#include <vector>

namespace Engine {
	template<class ... Params>
	class Delegate
	{
	public:
		Delegate() :
			m_pInstance(nullptr),
			m_pMethodStub(nullptr)
		{}

		bool operator==(const Delegate & i_other)
		{
			return (m_pInstance == i_other.m_pInstance) && (m_pMethodStub == i_other.m_pMethodStub);
		}

		template <class T, void (T::*TMethod)(Params ...)>
		static Delegate Create(T* i_pInstance)
		{
			return Delegate(i_pInstance, &method_stub<T, TMethod>);
		}

		operator bool() const
		{
			return m_pInstance != nullptr;
		}

		void operator()(Params ... i_Parameters) const
		{
			assert(m_pMethodStub);

			return (*m_pMethodStub)(m_pInstance, i_Parameters);
		}

		void ExecuteIfBound(Params ... i_Parameter) const
		{
			if (m_pInstance)
			{
				assert(m_pMethodStub);
				(*m_pMethodStub)(m_pInstance, i_Parameter ...);
			}
		}

	private:
		typedef void(*tMethodStub)(void * i_pInstance, Params ... i_Parameter);

		void *			m_pInstance;
		tMethodStub		m_pMethodStub;

		explicit Delegate(void * i_pInstance, tMethodStub i_pMethodStub) :
			m_pInstance(i_pInstance),
			m_pMethodStub(i_pMethodStub)
		{
			assert(i_pInstance);
			assert(i_pMethodStub);
		}

		template <class T, void (T::*TMethod)(Params ...)>
		static void method_stub(void * m_pInstance, Params ... i_Parameters)
		{
			(static_cast<T*>(m_pInstance)->*TMethod)(i_Parameters ...);
		}
	};

	template<class ... Params>
	class MultiCastDelegate
	{
	public:
		void AddDelegate(Delegate<Params ...> & i_Delegate)
		{
			Receivers.push_back(i_Delegate);
		}
		//r-value reference
		void AddDelegate(Delegate<Params ...> && i_Delegate)
		{
			Receivers.push_back(i_Delegate);
		}

		void RemoveDelegate(Delegate<Params ...> & i_Delegate)
		{
			Receivers.erase(std::remove_if(Receivers.begin(), Receivers.end(), [&i_Delegate](const Delegate<Params ...> & i_Entry) {return i_Entry == i_Delegate; }),
				Receivers.end());
		}

		void ExecuteOnBound(Params ... i_Parameters)
		{
			for (auto Receiver : Receivers)
				Receiver.ExecuteIfBound(i_Parameters ...);
		}
		~MultiCastDelegate()
		{
			Receivers.~vector();
		}
	private:
		std::vector< Delegate<Params ...> > Receivers;
	};


	void Delegates__UnitTest();

} // namespace Engin
