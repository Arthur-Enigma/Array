#include <iostream>
#include <string>
#include <cassert>

template <typename T>
class Array
{
public:
	explicit Array(unsigned int size = 0) :
		  size(size)
		, real_size(size + 1)
		, arr(new T[real_size]) 
	{
	}

	Array(const Array& other) :
		  size(other.size)
		, real_size(other.real_size)
		, arr(new T[other.real_size])
	{
		memcpy(arr, other.arr, sizeof(T)*size);
	}

	Array(Array &&other) :
		  size(other.size)
		, real_size(other.real_size)
		, arr(other.arr)
	{
		other.arr = nullptr;
		other.size = 0;
		other.real_size = 0;
	}

	Array& operator=(const Array& other) 
	{
		if (&other == this)
		{
			return *this;
		}
		delete[] arr;
		size = other.size;
		real_size = other.real_size;
		arr = new T[other.real_size];
		memcpy(arr, other.arr, sizeof(T)*size);
		return *this;
	}

	Array& operator=(Array&& other) 
	{
		delete[] arr;
		size = other.size;
		real_size = other.real_size;
		arr = other.arr;
		other.arr = nullptr;
		other.size = 0;
		other.real_size = 0;
		return *this;
	}

	T& operator[](unsigned int i)
	{
		assert(i < size);
		return arr[i];
	}

	const T& operator[](unsigned int i) const
	{
		assert(i < size);
		return arr[i];
	}

	~Array()
	{
		if(arr != nullptr)
			delete[] arr;
		arr = nullptr;
	}

	unsigned int getsize() const { return size; }

	bool isempty() const { return !size; }

	void push_back(const T& t)
	{
		if (size + 1 < real_size)
		{
			arr[size] = t;
			++size;
			return;
		}
		real_size *= 2;
		T* new_arr = new T[real_size];
		memcpy(new_arr, arr, sizeof(T)*size);
		new_arr[size] = t;
		delete[] arr;
		arr = new_arr;
		new_arr = nullptr;
		++size;	
	}

	void pop_back()
	{
		
		if (this->isempty())
			return;
		erase(size - 1);
	}

	void erase(unsigned int index)
	{
		if (index < size)
		{
			--size;
			if (size < real_size / 2)
			{
				real_size /= 2;
				T* new_arr = new T[real_size];
				memcpy(new_arr, arr, sizeof(T)*index);
				memcpy(&new_arr[index], &arr[index + 1], sizeof(T)*(size - index));
				delete[] arr;
				arr = new_arr;
				new_arr = nullptr;
				return;
			}
			else
			{
				memcpy(&arr[index], &arr[index + 1], sizeof(T)*(size - index));
			}
		}

	}

private:
	T* arr;
	unsigned int size;
	unsigned int real_size;
};


int main()
{
	
	return 0;
}