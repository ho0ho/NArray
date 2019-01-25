#pragma once
// narray.h

#include <iostream>

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
		NArray(int _dim, int *_size);
		NArray(const NArray& other);

		void initialize_way(Way *current);
		void destroy_way(Way *current);

		Int operator [] (const int index);

		virtual ~NArray();
	};	// class NArray

	class Int 
	{
	private:
		int level;
		void *data;
		NArray *arr;

	public:
		Int(int index, int _level, void *_data = NULL, NArray *_arr = NULL);
		Int(const Int& other);

		Int operator [] (const int index);
		operator int();
		Int& operator = (const int& right);
	
		virtual ~Int();
	};

} // narrayPark
