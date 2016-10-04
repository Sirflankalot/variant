#pragma once

#include <cstdlib>
#include <functional>
#include <limits>
#include <type_traits>

namespace CAS {
	namespace _meta {
		// A utility struct to deduce function parameters
		// primary template. I tried to write this myself,
		// but I kept failing, so I copy pasted it from
		// stack overflow. Template metaprogramming is difficult
		// sometimes :/ I tried to get this to work for too damn
		// long, something on the order of 2 hours...
		template <class T>
		struct function_traits : function_traits<decltype(&T::operator())> {};

		// partial specialization for function type
		template <class R, class... Args>
		struct function_traits<R(Args...)> {
			using result_type    = R;
			using argument_types = std::tuple<Args...>;
		};

		// partial specialization for function pointer
		template <class R, class... Args>
		struct function_traits<R (*)(Args...)> {
			using result_type    = R;
			using argument_types = std::tuple<Args...>;
		};

		// partial specialization for std::function
		template <class R, class... Args>
		struct function_traits<std::function<R(Args...)>> {
			using result_type    = R;
			using argument_types = std::tuple<Args...>;
		};

		// partial specialization for pointer-to-member-function (i.e., operator()'s)
		template <class T, class R, class... Args>
		struct function_traits<R (T::*)(Args...)> {
			using result_type    = R;
			using argument_types = std::tuple<Args...>;
		};

		template <class T, class R, class... Args>
		struct function_traits<R (T::*)(Args...) const> {
			using result_type    = R;
			using argument_types = std::tuple<Args...>;
		};

		// I did write everything else by hand though
		template <size_t n, class Func>
		struct function_arg {
			using type =
			    typename std::tuple_element<n,
			                                typename function_traits<Func>::argument_types>::type;
		};

		// Type to mark the end of a variatic template list
		struct none_type {};

		//////////////////
		// for_each_all //
		//////////////////

		template <template <class> class S, class T, class... Types>
		struct impl_for_each_all {
			using next = impl_for_each_all<S, Types...>;

			constexpr static bool value = S<T>::value ? next::value : false;
		};

		template <template <class> class S, class... Types>
		struct impl_for_each_all<S, none_type, Types...> {
			constexpr static bool value = true;
		};

		template <template <class> class S, class T, class... Types>
		struct for_each_all {
			using next = impl_for_each_all<S, T, Types..., none_type>;

			constexpr static bool value = next::value;
		};

		//////////////////
		// for_each_any //
		//////////////////

		template <size_t depth, template <class> class S, class T, class... Types>
		struct impl_for_each_any {
			using next = impl_for_each_any<depth + 1, S, Types...>;

			constexpr static bool value   = S<T>::value ? true : next::value;
			constexpr static size_t index = S<T>::value ? depth : next::index;
			constexpr static size_t count = size_t{S<T>::value} + next::count;
		};

		template <size_t depth, template <class> class S, class... Types>
		struct impl_for_each_any<depth, S, none_type, Types...> {
			constexpr static bool value   = false;
			constexpr static size_t index = depth;
			constexpr static size_t count = 0;
		};

		template <template <class> class S, class T, class... Types>
		struct for_each_any {
			using next = impl_for_each_any<0, S, T, Types..., none_type>;

			constexpr static bool value   = next::value;
			constexpr static size_t index = next::index;
			constexpr static size_t count = next::count;
		};

		////////////////
		// type_is_in //
		////////////////

		template <class T1, class... Types>
		struct type_is_in {
			template <class T2>
			using comp = std::is_same<T1, T2>;
			using next = impl_for_each_any<0, comp, Types..., none_type>;

			constexpr static bool value   = next::value;
			constexpr static size_t index = next::index;
		};

		//////////////
		// max_size //
		//////////////
		template <size_t max, class T, class... Types>
		struct impl_max_size {
			constexpr static size_t size = sizeof(T) > max
			                                   ? impl_max_size<sizeof(T), Types...>::size
			                                   : impl_max_size<max, Types...>::size;
		};

		template <size_t max, class... Types>
		struct impl_max_size<max, none_type, Types...> {
			constexpr static size_t size = max;
		};

		template <class T, class... Types>
		struct max_size {
			constexpr static size_t size = impl_max_size<0, T, Types..., none_type>::size;
		};

		///////////////
		// max_align //
		///////////////
		template <size_t max, class T, class... Types>
		struct impl_max_align {
			constexpr static size_t size = alignof(T) > max
			                                   ? impl_max_align<alignof(T), Types...>::size
			                                   : impl_max_align<max, Types...>::size;
		};

		template <size_t max, class... Types>
		struct impl_max_align<max, none_type, Types...> {
			constexpr static size_t size = max;
		};

		template <class T, class... Types>
		struct max_align {
			constexpr static size_t size = impl_max_align<0, T, Types..., none_type>::size;
		};

		////////////////////
		// max_int_needed //
		////////////////////
		template <size_t val, class T, class... Types>
		struct impl_max_int_needed {
			// static_assert(val < std::numeric_limits<T>::max(), "blah");
			using type =
			    typename std::conditional<(val < std::numeric_limits<T>::max()), T,
			                              typename impl_max_int_needed<val, Types...>::type>::type;
		};

		template <size_t val, class... Types>
		struct impl_max_int_needed<val, none_type, Types...> {
			using type = size_t;
		};

		template <size_t val>
		struct max_int_needed {
			using type =
			    typename impl_max_int_needed<val, unsigned char, unsigned short, unsigned int,
			                                 unsigned long, unsigned long long, none_type>::type;
		};
	}
}
