#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/CircularDoubleLinkedList.h"
#include "../Imagwzit/Queue.h"
#include "../Imagwzit/Stack.h"
#include "../Imagwzit/EmptyListException.h"
//Il faut que ce dernier lien soit aussi dans 
//[right-click sur projet]\éditeur de liens\propriétés\entrées\dépendances additionnelles
//sinon il y aura une erreur de linkage

//Si la classe que vous testez a une autre classe comme attribut, alors il faut aussi linker son .obj

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjetSFMLTest
{
	TEST_CLASS(testsPile)
	{
	public:
		/* Tests méthode getSize() */
		TEST_METHOD(StackGetSize_TestUnElement)
		{
			Stack<int> * stack = new Stack<int>();
			int element = 10;
			stack->push(&element);
			Assert::AreEqual(stack->getSize(), 1);
			delete stack;
		}
		TEST_METHOD(StackGetSize_TestDixElements)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++) 
			{
				int * element = new int(i);
				stack->push(element);
			}
			Assert::AreEqual(stack->getSize(), 10);
			delete stack;
		}
		TEST_METHOD(StackGetSize_TestAucunElement)
		{
			Stack<int> * stack = new Stack<int>();
			Assert::AreEqual(stack->getSize(), 0);
			delete stack;
		}

		TEST_METHOD(StackGetSize_TestUnElementEnleve)
		{
			Stack<int> * stack = new Stack<int>(); 
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			stack->pop();
			Assert::AreEqual(stack->getSize(), 9);
			delete stack;
		}

		TEST_METHOD(StackGetSize_TestPlusieursElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			for (int i = 0; i < 5; i++) 
			{
				stack->pop();
			}
			Assert::AreEqual(stack->getSize(), 5);
			delete stack;
		}

		TEST_METHOD(StackGetSize_TestTousElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			for (int i = 0; i < 10; i++)
			{
				stack->pop();
			}
			Assert::AreEqual(stack->getSize(), 0);
			delete stack;
		}

		/* Tests méthode top() */
		TEST_METHOD(StackTop_TestUnElement)
		{
			Stack<int> * stack = new Stack<int>();
			int element = 10;
			stack->push(&element);
			Assert::AreEqual(*stack->top(), 10);
			delete stack;
		}
		TEST_METHOD(StackTop_TestDixElements)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			Assert::AreEqual(*stack->top(), 9);
			delete stack;
		}
		TEST_METHOD(StackTop_TestAucunElement)
		{
			Stack<int> * stack = new Stack<int>();
			Assert::IsNull(stack->top());
			delete stack;
		}

		TEST_METHOD(StackTop_TestUnElementEnleve)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			stack->pop();
			Assert::AreEqual(*stack->top(), 8);
			delete stack;
		}

		TEST_METHOD(StackTop_TestPlusieursElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			for (int i = 0; i < 5; i++)
			{
				stack->pop();
			}
			Assert::AreEqual(*stack->top(), 4);
			delete stack;
		}

		TEST_METHOD(StackTop_TestTousElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			for (int i = 0; i < 10; i++)
			{
				stack->pop();
			}
			Assert::IsNull(stack->top());
			delete stack;
		}
		/* Tests méthode push() */
		TEST_METHOD(StackPush_TestUnElement)
		{
			Stack<int> * stack = new Stack<int>();
			int element = 10;
			stack->push(&element);
			Assert::AreEqual(*stack->top(), 10);
			delete stack;
		}
		TEST_METHOD(StackPush_TestDixElements)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			Assert::AreEqual(*stack->top(), 9);
			delete stack;
		}
		TEST_METHOD(StackPush_TestAucunElement)
		{
			Stack<int> * stack = new Stack<int>();
			Assert::IsNull(stack->top());
			delete stack;
		}

		TEST_METHOD(StackPush_TestUnElementEnleve)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			stack->pop();
			Assert::AreEqual(*stack->top(), 8);
			delete stack;
		}

		TEST_METHOD(StackPush_TestPlusieursElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			for (int i = 0; i < 5; i++)
			{
				stack->pop();
			}
			Assert::AreEqual(*stack->top(), 4);
			delete stack;
		}

		TEST_METHOD(StackPush_TestTousElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			for (int i = 0; i < 10; i++)
			{
				stack->pop();
			}
			Assert::IsNull(stack->top());
			delete stack;
		}
		/* Tests méthode pop() */
		TEST_METHOD(StackPop_TestUnElementEnleve)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			stack->pop();
			Assert::AreEqual(*stack->top(), 8);
			delete stack;
		}

		TEST_METHOD(StackPop_TestPlusieursElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			for (int i = 0; i < 5; i++)
			{
				stack->pop();
			}
			Assert::AreEqual(*stack->top(), 4);
			delete stack;
		}

		TEST_METHOD(StackPop_TestTousElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			for (int i = 0; i < 10; i++)
			{
				stack->pop();
			}
			Assert::IsNull(stack->top());
			delete stack;
		}

		TEST_METHOD(StackPop_TestTropElementsEnleves)
		{
			Stack<int> * stack = new Stack<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				stack->push(element);
			}
			bool exception = false;
			for (int i = 0; i < 15; i++)
			{
				try {
					stack->pop();
				}
				catch (EmptyListException&)
				{
					exception = true;
				}
			}
			Assert::AreEqual(exception, true);
			delete stack;
		}
	};
}