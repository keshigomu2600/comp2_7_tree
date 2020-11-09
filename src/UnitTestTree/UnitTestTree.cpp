#include "pch.h"

// ���������[�N�̃L���v�`��
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "CppUnitTest.h"
#include "../include/libtree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestTree
{
	TEST_MODULE_CLEANUP(test_module_cleanup) {
		Assert::IsFalse(_CrtDumpMemoryLeaks());// ���������[�N�`�F�b�N
	}

	void check_values(const node* p)
	{
		static int i = 0;
		static const char* table[] = { "hello", "world", "!" };
		Assert::AreEqual(table[i++], p->value);
	}

	TEST_CLASS(UnitTestTree)
	{
	public:

		// add_node���������������m�F����
		TEST_METHOD(TestAddNodeMethod)
		{
			binary_tree tree;
			initialize(&tree);

			add_node(&tree, 1, "hello world!"); //�m�[�h������Ĕԍ�1�ԂŒǉ�

			Assert::AreEqual("hello world!", tree.root->value); //�ǉ��������̂������Ă���

			finalize(&tree);

		}

		// search���������������m�F����
		TEST_METHOD(TestSearchMethod)
		{
			binary_tree tree;
			initialize(&tree);

			add_node(&tree, 1, "hello world!");

			serach(&tree, [](const node* p) { Assert::AreEqual("hello world!", p->value); });

			finalize(&tree);

		}

		// �����̃m�[�h��ǉ�
		TEST_METHOD(TestSearchMethodWithManyNodes)
		{
			binary_tree tree;
			initialize(&tree);

			add_node(&tree, 1, "hello");
			add_node(&tree, 2, "world");
			add_node(&tree, 3, "!");

			serach(&tree, check_values);

			finalize(&tree);

		}

		// ���������ł͂Ȃ����ԂŃm�[�h��ǉ�����
		TEST_METHOD(TestSearchMethodWithoutOrdering)
		{
			binary_tree tree;
			initialize(&tree);

			add_node(&tree, 2, "world");
			add_node(&tree, 3, "!");
			add_node(&tree, 1, "hello");

			void (*callback_func)(const node * p) = [](const node* p) {
				static int i = 0;
				static const char* table[] = { "hello", "world", "!" };
				Assert::AreEqual(table[i++], p->value);
			};
			serach(&tree, callback_func);

			finalize(&tree);

		}
	};
}
