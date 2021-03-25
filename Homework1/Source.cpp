#include <iostream>
#include <string>


template <typename T>
class Array
{
public:
	Array(unsigned int size = 0) :
		  size(size)
		, arr(new T[size])
	{
	}

	Array(const Array& other) :
		  size(other.size)
		, arr(new T[other.size])
	{
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
	}

	Array(Array &&other) :
		  size(other.size)
		, arr(other.arr)
	{
		other.arr = nullptr;
		other.size = 0;
	}

	Array& operator=(const Array& other) 
	{
		delete[] arr;
		size = other.size;
		arr = new T[other.size];
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = other.arr[i];
		}
		return *this;
	}

	Array& operator=(Array&& other) 
	{
		delete[] arr;
		size = other.size;
		arr = other.arr;
		other.arr = nullptr;
		other.size = 0;
		return *this;
	}

	T& operator[](unsigned int i)
	{
		if (i < size)
			return arr[i];
	}

	~Array()
	{
		if(arr != nullptr)
			delete[] arr;
		arr = nullptr;
	}

	unsigned int getsize() const
	{
		return size;
	}

	void push_back(const T& t)
	{
		T* new_arr = new T[size + 1];
		for (size_t i = 0; i < size; i++)
		{
			new_arr[i] = arr[i];
		}
		new_arr[size] = t;
		delete[] arr;
		arr = new_arr;
		new_arr = nullptr;
		++size;
		
	}

	void pop_back()
	{
		--size;
		T* new_arr = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			new_arr[i] = arr[i];
		}
		T t = arr[size];		
		delete[] arr;
		arr = new_arr;
		new_arr = nullptr;
		
	}

	void erase(unsigned int index)
	{
		if (index < size)
		{
			T* new_arr = new T[size - 1];
			T t = arr[index];
			for (size_t i = 0; i < index; i++)
			{
				new_arr[i] = arr[i];
			}
			for (size_t i = index + 1; i < size; i++)
			{
				new_arr[i - 1] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			new_arr = nullptr;
			--size;
		}
	}

private:
	T* arr;
	unsigned int size;
};


int main()
{

	Array<int> a;
	a.push_back(5);
	a.push_back(6);
	a.erase(0);
	a.pop_back();


	return 0;
}