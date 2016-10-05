#include "test_defaults.hpp"
#include "gtest/gtest.h"

TEST(Stack_Single, CopyConstructSelf) {
	std::vector<int> i{1, 2};
	Test_SVariant v1(i);
	Test_SVariant v2(v1);

	auto&& i1 = v1.get<std::vector<int>>();
	auto&& i2 = v2.get<std::vector<int>>();
	ASSERT_EQ(i1.size(), size_t{2});
	ASSERT_EQ(i1[0], 1);
	ASSERT_EQ(i1[1], 2);

	ASSERT_EQ(i2.size(), size_t{2});
	ASSERT_EQ(i2[0], 1);
	ASSERT_EQ(i2[1], 2);

	ASSERT_EQ(v1.tag_val(), v2.tag_val());
}

TEST(Stack_Single, MoveConstructSelf) {
	std::vector<int> i{1, 2};
	Test_SVariant v1(i);
	Test_SVariant v2(std::move(v1));

	auto&& ir = v2.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);

	ASSERT_EQ(v1.tag_val(), decltype(v1)::tag_of<void>());
}

TEST(Stack_Single, CopyAssignSelf) {
	std::vector<int> i{1, 2};
	Test_SVariant v1(i);
	Test_SVariant v2;
	v2 = v1;

	auto&& i1 = v1.get<std::vector<int>>();
	auto&& i2 = v2.get<std::vector<int>>();
	ASSERT_EQ(i1.size(), size_t{2});
	ASSERT_EQ(i1[0], 1);
	ASSERT_EQ(i1[1], 2);

	ASSERT_EQ(i2.size(), size_t{2});
	ASSERT_EQ(i2[0], 1);
	ASSERT_EQ(i2[1], 2);

	ASSERT_EQ(v1.tag_val(), v2.tag_val());
}

TEST(Stack_Single, MoveAssignSelf) {
	std::vector<int> i{1, 2};
	Test_SVariant v1(i);
	Test_SVariant v2;
	v2 = std::move(v1);

	auto&& ir = v2.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);

	ASSERT_EQ(v1.tag_val(), decltype(v1)::tag_of<void>());
}

TEST(Stack_Single, CopyConstructT) {
	std::vector<int> i{1, 2};
	Test_SVariant v(i);
	auto&& ir = v.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);
}

TEST(Stack_Single, MoveConstructT) {
	std::vector<int> i{1, 2};
	Test_SVariant v(std::move(i));
	auto&& ir = v.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);
}

TEST(Stack_Single, CopyAssignT) {
	std::vector<int> i{1, 2};
	Test_SVariant v;
	v = i;
	auto&& ir = v.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);
}

TEST(Stack_Single, MoveAssignT) {
	std::vector<int> i{1, 2};
	Test_SVariant v;
	v = std::move(i);
	auto&& ir = v.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);
}

TEST(Heap_Single, CopyConstructSelf) {
	std::vector<int> i{1, 2};
	Test_HVariant v1(i);
	Test_HVariant v2(v1);

	auto&& i1 = v1.get<std::vector<int>>();
	auto&& i2 = v2.get<std::vector<int>>();
	ASSERT_EQ(i1.size(), size_t{2});
	ASSERT_EQ(i1[0], 1);
	ASSERT_EQ(i1[1], 2);

	ASSERT_EQ(i2.size(), size_t{2});
	ASSERT_EQ(i2[0], 1);
	ASSERT_EQ(i2[1], 2);

	ASSERT_EQ(v1.tag_val(), v2.tag_val());
}

TEST(Heap_Single, MoveConstructSelf) {
	std::vector<int> i{1, 2};
	Test_HVariant v1(i);
	Test_HVariant v2(std::move(v1));

	auto&& ir = v2.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);

	ASSERT_EQ(v1.tag_val(), decltype(v1)::tag_of<void>());
}

TEST(Heap_Single, CopyAssignSelf) {
	std::vector<int> i{1, 2};
	Test_HVariant v1(i);
	Test_HVariant v2;
	v2 = v1;

	auto&& i1 = v1.get<std::vector<int>>();
	auto&& i2 = v2.get<std::vector<int>>();
	ASSERT_EQ(i1.size(), size_t{2});
	ASSERT_EQ(i1[0], 1);
	ASSERT_EQ(i1[1], 2);

	ASSERT_EQ(i2.size(), size_t{2});
	ASSERT_EQ(i2[0], 1);
	ASSERT_EQ(i2[1], 2);

	ASSERT_EQ(v1.tag_val(), v2.tag_val());
}

TEST(Heap_Single, MoveAssignSelf) {
	std::vector<int> i{1, 2};
	Test_HVariant v1(i);
	Test_HVariant v2;
	v2 = std::move(v1);

	auto&& ir = v2.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);

	ASSERT_EQ(v1.tag_val(), decltype(v1)::tag_of<void>());
}

TEST(Heap_Single, CopyConstructT) {
	std::vector<int> i{1, 2};
	Test_HVariant v(i);
	auto&& ir = v.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);
}

TEST(Heap_Single, MoveConstructT) {
	std::vector<int> i{1, 2};
	Test_HVariant v(std::move(i));
	auto&& ir = v.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);
}

TEST(Heap_Single, CopyAssignT) {
	std::vector<int> i{1, 2};
	Test_HVariant v;
	v = i;
	auto&& ir = v.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);
}

TEST(Heap_Single, MoveAssignT) {
	std::vector<int> i{1, 2};
	Test_HVariant v;
	v = std::move(i);
	auto&& ir = v.get<std::vector<int>>();
	ASSERT_EQ(ir.size(), size_t{2});
	ASSERT_EQ(ir[0], 1);
	ASSERT_EQ(ir[1], 2);
}
