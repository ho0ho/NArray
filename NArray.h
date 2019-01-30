#pragma once
// narray.h

#include <iostream>
#include <string>
using namespace std;

#ifndef _NARRAY_H_
#define _NARRAY_H_

namespace narrayPark {
	class NArray;
	class Int;

	class NArray
	{
		friend Int;
	private:
		int dim;
		int *size;
		struct Way {
			int level;
			void *next;
		};
		Way *root;

	public:
		class Iterator
		{
		private:
			int *loc;
			NArray *arr;

		public:
			Iterator(NArray *_arr, int *_loc = NULL) : arr(_arr)
			{
				loc = new int[arr->dim];
				for (int i = 0; i < arr->dim; i++)
					loc[i] = (_loc != NULL ? _loc[i] : 0);
			}

			Iterator(const Iterator& other) : arr(other.arr) {
				loc = new int[arr->dim];
				for (int i = 0; i < arr->dim; i++)
					loc[i] = other.loc[i];
			}

			string print_loc() const {
				string str = "(";
				for (int i = 0; i < arr->dim; i++) {
					str += to_string(loc[i]) + " ";
				}
				str += ")";
				return str;
			}

			// Int가 정의된 후에 구현할수 있으므로 선언만 한다.
			Int operator * ();

			// prefix
			Iterator& operator ++ () {
				if (loc[0] >= arr->size[0]) return (*this);

				bool carry = false;
				int i = arr->dim - 1;
				do {
					loc[i]++;
					if (loc[i] >= arr->size[i] && i >= 1) {
						carry = true;
						loc[i--] = 0;
					}
					else carry = false;
				} while (carry && i >= 0);
				return *this;
			}

			const Iterator operator ++ (int) {
				Iterator itr = *this;
				++(*this);
				return itr;
			}

			Iterator& operator = (const Iterator& right) {
				if (this == &right) return (*this);
				if (arr != right.arr) {
					delete[] loc;
					arr = right.arr;
					loc = new int[arr->dim];
				}
				for (int i = 0; i < arr->dim; i++)
					loc[i] = right.loc[i];
				return (*this);
			}

			bool operator == (const Iterator& right) {
				if (arr == right.arr) {
					int i;
					for (i = 0; i < arr->dim && loc[i] == right.loc[i]; i++);
					if (i >= arr->dim) return true;
					else return false;
				}
				else return false;
			}

			bool operator != (const Iterator& right) {
				return !(*this == right);
			}

			virtual ~Iterator() {
				delete[] loc;
			}
		};

		NArray(int _dim, int *_size);
		NArray(const NArray& other);

		void initialize_way(Way *current);
		void destroy_way(Way *current);

		Int operator [] (const int index);
		Iterator begin();
		Iterator end();

		virtual ~NArray();
	};	// class NArray

	class Int
	{
	private:
		int level;
		void *data;
		NArray *arr;

	public:
		Int(int index, int _level = 0, void *_data = NULL, NArray *_arr = NULL);
		Int(const Int& other);

		Int operator [] (const int index);
		operator int();
		Int& operator = (const int& right);

		virtual ~Int();
	}; // class Int

} // narrayPark

#endif  // _NARRAY_H_
