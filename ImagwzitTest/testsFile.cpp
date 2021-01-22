#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/CircularDoubleLinkedList.h"
#include "../Imagwzit/Queue.h"
#include "../Imagwzit/Queue.h"
#include "../Imagwzit/EmptyListException.h"
//Il faut que ce dernier lien soit aussi dans 
//[right-click sur projet]\éditeur de liens\propriétés\entrées\dépendances additionnelles
//sinon il y aura une erreur de linkage

//Si la classe que vous testez a une autre classe comme attribut, alors il faut aussi linker son .obj

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjetSFMLTest
{
	TEST_CLASS(testsFile)
	{
	public:
		/* Tests méthode getSize() */
		TEST_METHOD(QueueGetSize_TestUnElement)
		{
			Queue<int> * queue = new Queue<int>();
			int element = 10;
			queue->push(&element);
			Assert::AreEqual(queue->getSize(), 1);
			delete queue;
		}
		TEST_METHOD(QueueGetSize_TestDixElements)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			Assert::AreEqual(queue->getSize(), 10);
			delete queue;
		}
		TEST_METHOD(QueueGetSize_TestAucunElement)
		{
			Queue<int> * queue = new Queue<int>();
			Assert::AreEqual(queue->getSize(), 0);
			delete queue;
		}

		TEST_METHOD(QueueGetSize_TestUnElementEnleve)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			queue->pop();
			Assert::AreEqual(queue->getSize(), 9);
			delete queue;
		}

		TEST_METHOD(QueueGetSize_TestPlusieursElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 5; i++)
			{
				queue->pop();
			}
			Assert::AreEqual(queue->getSize(), 5);
			delete queue;
		}

		TEST_METHOD(QueueGetSize_TestTousElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 10; i++)
			{
				queue->pop();
			}
			Assert::AreEqual(queue->getSize(), 0);
			delete queue;
		}

		/* Tests méthode top() */
		TEST_METHOD(QueueTop_TestUnElement)
		{
			Queue<int> * queue = new Queue<int>();
			int element = 10;
			queue->push(&element);
			Assert::AreEqual(*queue->top(), 10);
			delete queue;
		}
		TEST_METHOD(QueueTop_TestDixElements)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			Assert::AreEqual(*queue->top(), 0);
			delete queue;
		}
		TEST_METHOD(QueueTop_TestAucunElement)
		{
			Queue<int> * queue = new Queue<int>();
			Assert::IsNull(queue->top());
			delete queue;
		}

		TEST_METHOD(QueueTop_TestUnElementEnleve)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			queue->pop();
			Assert::AreEqual(*queue->top(), 1);
			delete queue;
		}

		TEST_METHOD(QueueTop_TestPlusieursElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 5; i++)
			{
				queue->pop();
			}
			Assert::AreEqual(*queue->top(), 5);
			delete queue;
		}

		TEST_METHOD(QueueTop_TestTousElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 10; i++)
			{
				queue->pop();
			}
			Assert::IsNull(queue->top());
			delete queue;
		}
		/* Tests méthode push() */
		TEST_METHOD(QueuePush_TestUnElement)
		{
			Queue<int> * queue = new Queue<int>();
			int element = 10;
			queue->push(&element);
			Assert::AreEqual(*queue->top(), 10);
			delete queue;
		}
		TEST_METHOD(QueuePush_TestDixElements)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			Assert::AreEqual(*queue->top(), 0);
			delete queue;
		}
		TEST_METHOD(QueuePush_TestAucunElement)
		{
			Queue<int> * queue = new Queue<int>();
			Assert::IsNull(queue->top());
			delete queue;
		}

		TEST_METHOD(QueuePush_TestUnElementEnleve)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			queue->pop();
			Assert::AreEqual(*queue->top(), 1);
			delete queue;
		}

		TEST_METHOD(QueuePush_TestPlusieursElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 5; i++)
			{
				queue->pop();
			}
			Assert::AreEqual(*queue->top(), 5);
			delete queue;
		}

		TEST_METHOD(QueuePush_TestTousElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 10; i++)
			{
				queue->pop();
			}
			Assert::IsNull(queue->top());
			delete queue;
		}
		/* Tests méthode pop() */
		TEST_METHOD(QueuePop_TestUnElementEnleve)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			queue->pop();
			Assert::AreEqual(*queue->top(), 1);
			delete queue;
		}

		TEST_METHOD(QueuePop_TestPlusieursElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 5; i++)
			{
				queue->pop();
			}
			Assert::AreEqual(*queue->top(), 5);
			delete queue;
		}

		TEST_METHOD(QueuePop_TestTousElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 10; i++)
			{
				queue->pop();
			}
			Assert::IsNull(queue->top());
			delete queue;
		}

		TEST_METHOD(QueuePop_TestTropElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			bool exception = false;
			for (int i = 0; i < 15; i++)
			{
				try {
					queue->pop();
				}
				catch (EmptyListException&)
				{
					exception = true;
				}
			}
			Assert::AreEqual(exception, true);
			delete queue;
		}
		/*Tests opérateur []*/
		TEST_METHOD(QueueIteration_TestUnElement)
		{
			Queue<int> * queue = new Queue<int>();
			int element = 10;
			queue->push(&element);
			Assert::AreEqual(*(*queue)[0], 10);
			delete queue;
		}
		TEST_METHOD(QueueIteration_TestDixElements)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			Assert::AreEqual(*(*queue)[6], 6);
			delete queue;
		}
		TEST_METHOD(QueueIteration_TestAucunElement)
		{
			Queue<int> * queue = new Queue<int>();
			bool exception = false;
			try {
				*(*queue)[0];
			}
			catch (std::out_of_range&)
			{
				exception = true;
			}
			Assert::IsTrue(exception);
			delete queue;
		}

		TEST_METHOD(QueueIteration_TestUnElementEnleve)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			queue->pop();
			Assert::AreEqual(*(*queue)[4], 5);
			delete queue;
		}

		TEST_METHOD(QueueIteration_TestPlusieursElementsEnleves)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			for (int i = 0; i < 5; i++)
			{
				queue->pop();
			}
			Assert::AreEqual(*(*queue)[3], 8);
			delete queue;
		}

		TEST_METHOD(QueueIteration_TestLimiteSuperieure)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			Assert::AreEqual(*(*queue)[9], 9);
			delete queue;
		}

		TEST_METHOD(QueueIteration_TestLimiteInferieure)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			Assert::AreEqual(*(*queue)[0], 0);
			delete queue;
		}

		TEST_METHOD(QueueIteration_TestPlusQueLimiteSuperieure)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			bool exception = false;
			try {
				*(*queue)[10];
			}
			catch (std::out_of_range&)
			{
				exception = true;
			}
			Assert::IsTrue(exception);
			delete queue;
		}

		TEST_METHOD(QueueIteration_TestMoinsQueLimiteInferieure)
		{
			Queue<int> * queue = new Queue<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				queue->push(element);
			}
			bool exception = false;
			try {
				*(*queue)[-2];
			}
			catch (std::out_of_range&)
			{
				exception = true;
			}
			Assert::IsTrue(exception);
			delete queue;
		}
	};
}