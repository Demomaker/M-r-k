#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Imagwzit/CircularDoubleLinkedList.h"
#include "../Imagwzit/EmptyListException.h"
//Il faut que ce dernier lien soit aussi dans 
//[right-click sur projet]\éditeur de liens\propriétés\entrées\dépendances additionnelles
//sinon il y aura une erreur de linkage

//Si la classe que vous testez a une autre classe comme attribut, alors il faut aussi linker son .obj

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjetSFMLTest
{
	TEST_CLASS(testsListeChainee)
	{
	public:
		/* Tests méthode getSize() */
		TEST_METHOD(CircularDoubleLinkedListGetSize_TestUnElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			int element = 10;
			list->add_start(&element);
			Assert::AreEqual(list->getSize(), 1);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListGetSize_TestDixElements)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			Assert::AreEqual(list->getSize(), 10);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListGetSize_TestAucunElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			Assert::AreEqual(list->getSize(), 0);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetSize_TestUnElementEnleve)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			list->remove_end();
			Assert::AreEqual(list->getSize(), 9);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetSize_TestPlusieursElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			for (int i = 0; i < 5; i++)
			{
				list->remove_start();
			}
			Assert::AreEqual(list->getSize(), 5);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetSize_TestTousElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 10; i++)
			{
				list->remove_start();
			}
			Assert::AreEqual(list->getSize(), 0);
			delete list;
		}

		/* Tests méthode getEnd() */
		TEST_METHOD(CircularDoubleLinkedListGetEnd_TestUnElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			int element = 10;
			list->add_end(&element);
			Assert::AreEqual(*list->getEnd(), 10);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListGetEnd_TestDixElements)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			Assert::AreEqual(*list->getEnd(), 0);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListGetEnd_TestAucunElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			Assert::IsNull(list->getEnd());
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetEnd_TestUnElementEnleve)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			list->remove_end();
			Assert::AreEqual(*list->getEnd(), 8);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetEnd_TestPlusieursElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			for (int i = 0; i < 5; i++)
			{
				list->remove_end();
			}
			Assert::AreEqual(*list->getEnd(), 4);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetEnd_TestTousElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 10; i++)
			{
				list->remove_start();
			}
			Assert::IsNull(list->getEnd());
			delete list;
		}

		/* Tests méthode getStart() */
		TEST_METHOD(CircularDoubleLinkedListGetStart_TestUnElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			int element = 10;
			list->add_end(&element);
			Assert::AreEqual(*list->getStart(), 10);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListGetStart_TestDixElements)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			Assert::AreEqual(*list->getStart(), 9);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListGetStart_TestAucunElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			Assert::IsNull(list->getStart());
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetStart_TestUnElementEnleve)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			list->remove_end();
			Assert::AreEqual(*list->getStart(), 0);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetStart_TestPlusieursElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			for (int i = 0; i < 5; i++)
			{
				list->remove_end();
			}
			Assert::AreEqual(*list->getStart(), 0);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListGetStart_TestTousElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 10; i++)
			{
				list->remove_start();
			}
			Assert::IsNull(list->getStart());
			delete list;
		}
		/* Tests méthode add_end() */
		TEST_METHOD(CircularDoubleLinkedListAddEnd_TestUnElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			int element = 10;
			list->add_end(&element);
			Assert::AreEqual(*list->getEnd(), 10);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListAddEnd_TestDixElements)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			Assert::AreEqual(*list->getStart(), 0);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListAddEnd_TestAucunElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			Assert::IsNull(list->getEnd());
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListAddEnd_TestUnElementEnleve)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			list->remove_end();
			Assert::AreEqual(*list->getEnd(), 8);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListAddEnd_TestPlusieursElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			for (int i = 0; i < 5; i++)
			{
				list->remove_end();
			}
			Assert::AreEqual(*list->getEnd(), 4);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListAddEnd_TestTousElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			for (int i = 0; i < 10; i++)
			{
				list->remove_end();
			}
			Assert::IsNull(list->getEnd());
			delete list;
		}
		/* Tests méthode add_start() */
		TEST_METHOD(CircularDoubleLinkedListAddStart_TestUnElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			int element = 10;
			list->add_start(&element);
			Assert::AreEqual(*list->getEnd(), 10);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListAddStart_TestDixElements)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			Assert::AreEqual(*list->getStart(), 9);
			delete list;
		}
		TEST_METHOD(CircularDoubleLinkedListAddStart_TestAucunElement)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			Assert::IsNull(list->getStart());
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListAddStart_TestUnElementEnleve)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			list->remove_end();
			Assert::AreEqual(*list->getStart(), 9);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListAddStart_TestPlusieursElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 5; i++)
			{
				list->remove_end();
			}
			Assert::AreEqual(*list->getStart(), 9);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListAddStart_TestTousElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 10; i++)
			{
				list->remove_start();
			}
			Assert::IsNull(list->getStart());
			delete list;
		}
		/* Tests méthode remove_end() */
		TEST_METHOD(CircularDoubleLinkedListRemoveEnd_TestUnElementEnleve)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			list->remove_end();
			Assert::AreEqual(*list->getEnd(), 8);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListRemoveEnd_TestPlusieursElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 5; i++)
			{
				list->remove_end();
			}
			Assert::AreEqual(*list->getEnd(), 5);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListRemoveEnd_TestTousElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 10; i++)
			{
				list->remove_end();
			}
			Assert::IsNull(list->getStart());
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListRemoveEnd_TestTropElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			bool exception = false;
			for (int i = 0; i < 15; i++)
			{
				try {
					list->remove_end();
				}
				catch (EmptyListException&)
				{
					exception = true;
				}
			}
			Assert::AreEqual(exception, true);
			delete list;
		}

		/* Tests méthode remove_start() */
		TEST_METHOD(CircularDoubleLinkedListRemoveStart_TestUnElementEnleve)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			list->remove_start();
			Assert::AreEqual(*list->getStart(), 1);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListRemoveStart_TestPlusieursElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 5; i++)
			{
				list->remove_start();
			}
			Assert::AreEqual(*list->getEnd(), 0);
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListRemoveStart_TestTousElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_start(element);
			}
			for (int i = 0; i < 10; i++)
			{
				list->remove_start();
			}
			Assert::IsNull(list->getStart());
			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListRemoveStart_TestTropElementsEnleves)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			for (int i = 0; i < 10; i++)
			{
				int * element = new int(i);
				list->add_end(element);
			}
			bool exception = false;
			for (int i = 0; i < 15; i++)
			{
				try {
					list->remove_start();
				}
				catch (EmptyListException&)
				{
					exception = true;
				}
			}
			Assert::AreEqual(exception, true);
			delete list;
		}
		/*Tests itération*/
		TEST_METHOD(CircularDoubleLinkedListIteration_TestIterateurpp)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			int * element = new int(10);
			list->add_end(element);
			element = new int(5);
			list->add_end(element);
			element = new int(9);
			list->add_end(element);

			int i = 0;
			auto current = std::begin(*list);
			for (int i = 0; i < 2; i++)
			{
				current++;
			}
			Assert::AreEqual(*current,9);

			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListIteration_TestppIterateur)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			int * element = new int(10);
			list->add_end(element);
			element = new int(5);
			list->add_end(element);
			element = new int(9);
			list->add_end(element);

			int i = 0;
			auto current = std::begin(*list);
			for (int i = 0; i < 2; i++)
			{
				++current;
			}
			Assert::AreEqual(*current, 9);

			delete list;
		}

		TEST_METHOD(CircularDoubleLinkedListIteration_TestIterateurComparaisonNonEgal)
		{
			CircularDoubleLinkedList<int> * list = new CircularDoubleLinkedList<int>();
			int * element = new int(10);
			list->add_end(element);
			element = new int(5);
			list->add_end(element);
			element = new int(9);
			list->add_end(element);

			int i = 0;
			auto iterator = std::begin(*list);
			for (int i = 0; i < 2; i++)
			{
				++iterator;
			}
			Assert::AreNotEqual(*iterator, 5);

			delete list;
		}
	};
}