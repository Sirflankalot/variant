#include "test_defaults.hpp"
#include "gtest/gtest.h"

TEST(Stack_Empty, ConstructEmpty) {
	Test_SVariant v;
	ASSERT_EQ(sizeof(decltype(v)), 128ULL);
	ASSERT_EQ(alignof(decltype(v)), 64ULL);
}

TEST(Stack_Empty, CopyConstruct) {
	Test_SVariant v;
	auto x = v;
	static_assert(std::is_same<decltype(x), decltype(v)>::value,
	              "Auto copy construction causes incorrect type");
}

TEST(Stack_Empty, MoveConstruct) {
	Test_SVariant v;
	auto x = std::move(v);
	static_assert(std::is_same<decltype(x), decltype(v)>::value,
	              "Auto move construction causes incorrect type");
}

TEST(Stack_Empty, CopyAssign) {
	Test_SVariant v;
	Test_SVariant x;
	x = v;
}

TEST(Stack_Empty, MoveAssign) {
	Test_SVariant v;
	Test_SVariant x;
	x = std::move(v);
}

TEST(Heap_Empty, ConstructEmpty) {
	Test_HVariant v;
	ASSERT_EQ(sizeof(decltype(v)), 24ULL);
	ASSERT_EQ(alignof(decltype(v)), 8ULL);
}

TEST(Heap_Empty, CopyConstruct) {
	Test_HVariant v;
	auto x = v;
	static_assert(std::is_same<decltype(x), decltype(v)>::value,
	              "Auto copy construction causes incorrect type");
}

TEST(Heap_Empty, MoveConstruct) {
	Test_HVariant v;
	auto x = std::move(v);
	static_assert(std::is_same<decltype(x), decltype(v)>::value,
	              "Auto move construction causes incorrect type");
}

TEST(Heap_Empty, CopyAssign) {
	Test_HVariant v;
	Test_HVariant x;
	x = v;
}

TEST(Heap_Empty, MoveAssign) {
	Test_HVariant v;
	Test_HVariant x;
	x = std::move(v);
}
