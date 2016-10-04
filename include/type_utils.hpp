#pragma once

#include <cstdlib>

namespace CAS {
	namespace _meta {
		// Applies a template struct to each value (applies S<T>::value)
		// Members:
		// constexpr static bool value (true if all true)
		template <template <class> class S, class T, class... Types>
		struct for_each_all;

		// Applies a template struct to each value (applies S<T>::value)
		// Members:
		// constexpr static bool   value (true if any one true)
		// constexpr static size_t index (index of first match; sizeof...(Types) if value false)
		// constexpr static size_t count (count of types that return true)
		template <template <class> class S, class T, class... Types>
		struct for_each_any;

		// Tells if type T is in list of Types
		// Members:
		// constexpr static   bool value (true if in list, false if not)
		// constexpr static size_t index (index of match; sizeof...(Types) if value false)
		template <class T, class... Types>
		struct type_is_in;

		// Finds max size of provided types
		// Members:
		// constexpr static size_t size
		template <class T, class... Types>
		struct max_size;

		// Finds max size of provided types
		// Members:
		// constexpr static size_t size
		template <class T, class... Types>
		struct max_align;

		// Returns largest integer type needed to store value
		template <size_t val>
		struct max_int_needed;
	}
}

#include "type_utils.tpp"
