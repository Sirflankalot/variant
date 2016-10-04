#pragma once

#include "type_utils.hpp"
#include <cstddef>
#include <cstring>
#include <memory>
#include <stdexcept>

namespace SirVariant {
	struct bad_variant_get : public std::exception {
	  public:
		virtual const char* what() const noexcept override {
			return "A variant was accessed with the wrong type\n";
		}
	};

	template <class T1, class... Types>
	class Heap_Variant {
	  public:
		using tag_type = typename SirVariant::max_int_needed<sizeof...(Types) + 1>::type;
		using type_tuple = typename std::tuple<T1, Types...>;
		template <class T>
		using check_type = typename SirVariant::type_is_in<T, T1, Types...>;

		constexpr static size_t type_count = sizeof...(Types) + 1;
		constexpr static size_t max_size = SirVariant::max_size<T1, Types...>::size;
		constexpr static size_t max_align = SirVariant::max_align<T1, Types...>::size;

		Heap_Variant() {
			allocate();
		}
		Heap_Variant(const Heap_Variant& in) {
			allocate();
			std::memcpy(this->data_ptr, in.data_ptr, max_size);
			this->tag = in.tag;
		}
		Heap_Variant(Heap_Variant&& in) noexcept {
			this->unaligned_ptr = in.unaligned_ptr;
			this->data_ptr = in.data_ptr;
			this->tag = in.tag;
			in.unaligned_ptr = nullptr;
			in.data_ptr = nullptr;
			in.tag = type_count;
		}

		Heap_Variant& operator=(const Heap_Variant& in) {
			destruct();
			std::memcpy(this->data_ptr, in.data_ptr, max_size);
			this->tag = in.tag;

			return *this;
		}
		Heap_Variant& operator=(Heap_Variant&& in) noexcept {
			dealocate();
			this->unaligned_ptr = in.unaligned_ptr;
			this->data_ptr = in.data_ptr;
			this->tag = in.tag;
			in.unaligned_ptr = nullptr;
			in.data_ptr = nullptr;
			in.tag = type_count;

			return *this;
		}

		~Heap_Variant() {
			dealocate();
		}

		template <class T,
		          typename std::enable_if_t<!std::is_same<T, Heap_Variant>::value>* = nullptr>
		explicit Heap_Variant(const T& val) {
			static_assert(check_type<T>::value,
			              "Variant can only be constructed from one of its subtypes.");
			allocate();
			data_ptr = reinterpret_cast<char*>(new (data_ptr) T(val));

			this->tag = SirVariant::type_is_in<T, T1, Types...>::index;
		}

		template <class T, typename std::enable_if_t<!std::is_same<T, Heap_Variant>::value &&
		                                             std::is_rvalue_reference<T>::value>* = nullptr>
		explicit Heap_Variant(T&& val) {
			static_assert(check_type<T>::value,
			              "Variant can only be constructed from one of its subtypes.");
			allocate();
			data_ptr = reinterpret_cast<char*>(new (data_ptr) T(std::move(val)));

			this->tag = SirVariant::type_is_in<T, T1, Types...>::index;
		}

		template <class T,
		          typename std::enable_if_t<!std::is_same<T, Heap_Variant>::value>* = nullptr>
		Heap_Variant& operator=(const T& val) {
			static_assert(check_type<T>::value,
			              "Variant can only be assigned from one of its subtypes.");
			destruct();
			data_ptr = reinterpret_cast<char*>(new (data_ptr) T(val));

			this->tag = SirVariant::type_is_in<T, T1, Types...>::index;

			return *this;
		}

		template <class T, typename std::enable_if_t<!std::is_same<T, Heap_Variant>::value &&
		                                             std::is_rvalue_reference<T>::value>* = nullptr>
		Heap_Variant& operator=(T&& val) {
			static_assert(check_type<T>::value,
			              "Variant can only be assigned from one of its subtypes.");
			destruct();
			data_ptr = reinterpret_cast<char*>(new (data_ptr) T(std::move(val)));

			this->tag = SirVariant::type_is_in<T, T1, Types...>::index;

			return *this;
		}

		template <class T>
		T& get() {
			static_assert(check_type<T>::value, "Get type must be in list of subtypes");

			if (check_type<T>::index == tag) {
				return *reinterpret_cast<T*>(data_ptr);
			}
			else {
				throw bad_variant_get();
			}
		}

		tag_type tag_val() {
			return tag;
		}

		template <class T>
		struct tag_of {
			constexpr static tag_type value = SirVariant::type_is_in<T, T1, Types...>::index;
		};

	  protected:
		char* unaligned_ptr = nullptr;
		char* data_ptr = nullptr;
		tag_type tag = type_count;

		Heap_Variant(char* const val) {
			this->data_ptr = val;
		}

		Heap_Variant(const Heap_Variant& in, char* const val) {
			this->data_ptr = val;
			std::memcpy(this->data_ptr, in.data_ptr, max_size);
			this->tag = in.tag;
		}

		void op_eq_assist(const Heap_Variant& in) {
			std::memcpy(this->data_ptr, in.data_ptr, max_size);
			this->tag = in.tag;
		}

		void allocate() {
			// Align the pointer if needed
			if (max_align > alignof(std::max_align_t)) {
				size_t space = max_size + max_align;
				unaligned_ptr = new char[space];
				char* unaligned = unaligned_ptr;
				void*&& unaligned_ref = static_cast<void*>(unaligned);
				void* aligned =
				    std::align(max_align, max_size, static_cast<void*&>(unaligned_ref), space);
				if (aligned == nullptr) {
					delete[] unaligned;
					throw std::bad_alloc();
				}
				data_ptr = static_cast<char*>(aligned);
			}
			else {
				data_ptr = new char[max_size];
			}
		}

		// SFINAE overloads to prevent infinite recursion
		template <size_t count, typename std::enable_if_t<(count >= type_count)>* = nullptr>
		void destruct_assist() {}

		template <size_t count, typename std::enable_if_t<(count < type_count)>* = nullptr>
		void destruct_assist() {
			destruct<count>();
		}

		template <size_t count = 0>
		void destruct() {
			if (count == tag) {
				using cur_type = typename std::tuple_element<count, type_tuple>::type;
				reinterpret_cast<cur_type*>(data_ptr)->~cur_type();
			}
			else {
				destruct_assist<count + 1>();
			}
		}

		void dealocate() {
			destruct();
			delete[] unaligned_ptr;
		}
	};

	template <class T1, class... Types>
	class Stack_Variant : public Heap_Variant<T1, Types...> {
	  public:
		using Parent = Heap_Variant<T1, Types...>;

		Stack_Variant() : Parent(data) {}
		Stack_Variant(const Stack_Variant& val) : Parent(val, data) {}
		Stack_Variant(Stack_Variant&& val) : Parent(const_cast<const Stack_Variant&>(val), data) {}

		template <class T, typename std::enable_if_t<
		                       !std::is_convertible<T, Stack_Variant>::value>* = nullptr>
		explicit Stack_Variant(const T& val) : Parent(val) {}
		template <class T,
		          typename std::enable_if_t<!std::is_convertible<T, Stack_Variant>::value &&
		                                    std::is_rvalue_reference<T>::value>* = nullptr>
		explicit Stack_Variant(T&& val) : Parent(val) {}

		Stack_Variant& operator=(const Stack_Variant& val) {
			Parent::op_eq_assist(val);
			return *this;
		}

		Stack_Variant& operator=(Stack_Variant&& val) {
			Parent::op_eq_assist(val);
			return *this;
		}

		template <class T, typename std::enable_if_t<
		                       !std::is_convertible<T, Stack_Variant>::value>* = nullptr>
		Stack_Variant& operator=(const T& val) {
			Parent::operator=(val);
			return *this;
		}

		template <class T,
		          typename std::enable_if_t<!std::is_convertible<T, Stack_Variant>::value &&
		                                    std::is_rvalue_reference<T>::value>* = nullptr>
		Stack_Variant& operator=(T&& val) {
			Parent::operator=(val);
			return *this;
		}

		~Stack_Variant() {
			Parent::destruct();
			Parent::unaligned_ptr = nullptr;
			Parent::data_ptr = nullptr;
			Parent::tag = Parent::type_count;
		}

	  private:
		alignas(Parent::max_align) char data[Parent::max_size];

		void allocate() {
			Parent::data_ptr = &data;
		}

		void dealocate() {
			Parent::destruct();
		}
	};
}
