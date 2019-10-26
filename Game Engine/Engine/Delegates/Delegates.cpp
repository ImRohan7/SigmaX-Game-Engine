#include "Delegates.h"
#include "../Console/ConsolePrint.h"
#include <assert.h>

namespace Engine {

	void Delegates__UnitTest()
	{
#ifdef _DEBUG
		using namespace Engine;

		typedef int					param_t;
		typedef Delegate<param_t>	TestDelegate_t;
		class TestClass
		{
		public:
			void TestMethod(param_t i)
			{
				DEBUG_PRINT("Delegate test OP: %d", i);
			}
		};

		TestClass TestInstance;

		TestDelegate_t TestDelegate1 = TestDelegate_t::Create<TestClass, &TestClass::TestMethod>(&TestInstance);
		TestDelegate_t TestDelegate2 = TestDelegate_t::Create<TestClass, &TestClass::TestMethod>(&TestInstance);

		assert(TestDelegate1 == TestDelegate2);

		TestDelegate1.ExecuteIfBound(4);

#endif // _DEBUG
	}
} // namespace Engine
