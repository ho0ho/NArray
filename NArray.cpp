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

	NArray::~NArray()
	{
		destroy_way(root);
		delete[] size;
	}

} // narrayPark