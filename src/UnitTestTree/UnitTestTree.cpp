#include "pch.h"

// メモリリークのキャプチャ
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "CppUnitTest.h"
#include "../include/libtree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestTree
{
	TEST_MODULE_CLEANUP(test_module_cleanup) {
		Assert::IsFalse(_CrtDumpMemoryLeaks());// メモリリークチェック
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

		// add_nodeが正しく動くか確認する
		TEST_METHOD(TestAddNodeMethod)
		{
			binary_tree tree;
			initialize(&tree);

			add_node(&tree, 1, "hello world!"); //ノードを作って番号1番で追加

			Assert::AreEqual("hello world!", tree.root->value); //追加したものが入っている

			finalize(&tree);

		}

		// searchが正しく動くか確認する
		TEST_METHOD(TestSearchMethod)
		{
			binary_tree tree;
			initialize(&tree);

			add_node(&tree, 1, "hello world!");

			serach(&tree, [](const node* p) { Assert::AreEqual("hello world!", p->value); });

			finalize(&tree);

		}

		// 複数のノードを追加
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

		// 小さい順ではない順番でノードを追加する
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
