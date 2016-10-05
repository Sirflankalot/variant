#include "test_defaults.hpp"
#include "gtest/gtest.h"

TEST(Stack_Multi, GetExceptionEmpty) {
	Test_SVariant v;

	size_t throw_count = 0;

	try {
		v.get<int16_t>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<float>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<double>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Basic_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Padded_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Overaligned_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<std::vector<int32_t>>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	ASSERT_EQ(throw_count, size_t{7});
}

TEST(Stack_Multi, GetExceptionFull) {
	Test_SVariant v(std::vector<int32_t>{});

	size_t throw_count = 0;

	try {
		v.get<int16_t>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<float>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<double>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Basic_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Padded_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Overaligned_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	ASSERT_EQ(throw_count, size_t{6});
}

TEST(Heap_Multi, GetExceptionEmpty) {
	Test_HVariant v;

	size_t throw_count = 0;

	try {
		v.get<int16_t>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<float>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<double>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Basic_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Padded_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Overaligned_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<std::vector<int32_t>>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	ASSERT_EQ(throw_count, size_t{7});
}

TEST(Heap_Multi, GetExceptionFull) {
	Test_HVariant v(std::vector<int32_t>{});

	size_t throw_count = 0;

	try {
		v.get<int16_t>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<float>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<double>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Basic_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Padded_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	try {
		v.get<Overaligned_Struct>();
	}
	catch (SirVariant::bad_variant_get& e) {
		throw_count += 1;
	}

	ASSERT_EQ(throw_count, size_t{6});
}
