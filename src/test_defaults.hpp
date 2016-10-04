#pragma once
#include "variant.hpp"
#include <cinttypes>
#include <vector>

struct Basic_Struct {
	int64_t a;
	int32_t b;
	int16_t c;
	int8_t d;
	bool e;
};

struct Padded_Struct {
	bool e;
	int8_t d;
	int16_t c;
	int32_t b;
	int64_t a;
};

struct Overaligned_Struct {
	alignas(64) char a[32];
};

using Test_SVariant =
    typename SirVariant::Stack_Variant<int16_t, float, double, Basic_Struct, Padded_Struct,
                                       Overaligned_Struct, std::vector<int32_t>>;

using Test_HVariant =
    typename SirVariant::Heap_Variant<int16_t, float, double, Basic_Struct, Padded_Struct,
                                      Overaligned_Struct, std::vector<int32_t>>;
