#include "NArray.h"


namespace narrayPark {
	NArray::NArray(int _dim, int *_size) : dim(_dim)
	{
		size = new int[dim];
		for (int i = 0; i < dim; i++)
			size[i] = _size[i];
		root = new Way;
		root->level = 0;
		initialize_way(root);
	}

	NArray::NArray(const NArray& other) : dim(other.dim)
	{
		size = new int[dim];
		for (int i = 0; i < dim; i++)
			size[i] = other.size[i];
		root = new Way;
		// ?? 
	}
	
	void NArray::initialize_way(Way *current)
	{
		if (!current) return;
		if (current->level == dim - 1) 
			current->next = new int[size[current->level]];
		else {	
			current->next = new Way[size[current->level]];
			for (int i = 0; i < size[current->level]; i++) {
				(static_cast<Way *>(current->next) + i)->level = current->level + 1;
				initialize_way(static_cast<Way *>(current->next));
			}
		}
	}

	void NArray::destroy_way(Way *current) 
	{
		if (!current) return;
		if (current->level == dim - 1) 
			delete[] current->next;
		else {
			for (int i = 0; i < size[current->level]; i++) {
				destroy_way(static_cast<Way *>(current->next) + i);
			}
		}
	}

	Int NArray::operator [] (const int index) 
	{
		return Int(index, 1, static_cast<void *>(root), this);
	}

	NArray::~NArray()
	{
		destroy_way(root);
		delete[] size;
	}

	Int::Int(int index, int _level, void *_data, NArray *_arr) 
		: level(_level), arr(_arr)
	{
		if (index < 0 || level < 1 || index >= arr->size[level - 1]) {
			data = NULL;
			return;
		}

		if (level == arr->dim) 
			data = static_cast<void *>(static_cast<int *>(static_cast<NArray::Way *>(data)->next) + index);
		else
			data = static_cast<void *>(static_cast<NArray::Way *>(static_cast<NArray::Way *>(data)->next) + index);
	}

} // narrayPark