#pragma once

namespace CAS {
	namespace _util {
		// A variant is basically a fancy tagged union.
		// It takes the list of types it accepts as template parameters.
		// The amount of data stores is equal to the size of the largest type
		//
		// Heap Variant stores the data on the heap (size 9-16)
		// Stack Variant stores the data on the stack (size 9-16 + sizeof(largest))
		//
		// It has the following methods:
		//
		// Variant()     // default constructs a variant with nothing in it
		// Variant(const Variant&) // Copy construct variant
		// Variant(Variant&&)      // Move construct variant
		//
		// template<class T>
		// explicit Variant(const T&) // Copy construct a subtype
		// template<class T>
		// explicit Variant(T&&)      // Move Construct a subtype
		//
		// template<class T>
		// Variant& operator=(const T&) // copy-assign subtype
		// template<class T>
		// Variant& operator=(T&&)      // move-assign subtype
		//
		// template<class T>
		// T& get()           // Get value if value is type T, otherwise throw bad_variant_get
		//
		// size_t tag_val() // Get current value of internal tag
		//
		// structure to get correct tag value for each type
		// template<class T>
		// struct tag_of {
		//     constexpr static size_t value;
		// };

		template <class T1, class... T>
		class Heap_Variant;

		template <class T1, class... T>
		class Stack_Variant;

		template <class T1, class... T>
		using Variant = Stack_Variant<T1, T...>;

		struct bad_variant_get;
	}
}

void variant_test_function();

#include "variant.tpp"
