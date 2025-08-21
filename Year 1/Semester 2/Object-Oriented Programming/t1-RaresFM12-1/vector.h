#pragma once
#include <iostream>

template<typename TElem>
class DynamicVector {
private:
	int size;
	int capacity;
	TElem* elem;

	void resize(int cap);

public:
	DynamicVector();
	DynamicVector(int cap);
	~DynamicVector();

	/// <summary>
	/// Copy Constructor
	/// </summary>
	/// <param name="v">the vector we want to copy</param>
	DynamicVector(const DynamicVector& v);

	/// <summary>
	/// Assignement operator
	/// </summary>
	/// <param name="v"></param>
	/// <returns>the address of the vector</returns>
	DynamicVector<TElem>& operator=(const DynamicVector& v);

	/// <summary>
	/// [] operator to acces elements
	/// </summary>
	/// <param name="ind">the index of the element we want to acces</param>
	/// <returns>the element we want to acces</returns>
	DynamicVector operator[](int ind);

	/// <summary>
	/// Adds an element to the vector
	/// </summary>
	/// <param name="e">the element</param>
	void addElement(const TElem& e);

	/// <summary>
	/// Removes an element from the vector
	/// </summary>
	/// <param name="ind">the index of the element</param>
	void removeElement(int ind);

	/// <summary>
	/// Updates an element from the vector
	/// </summary>
	/// <param name="ind">the index of the element</param>
	/// <param name="e">the new element</param>
	void updateElement(int ind, TElem e);

	int getSize();
	TElem getElement(int ind);
};

template<typename TElem>
DynamicVector<TElem>::DynamicVector() :
	size{ 0 }, capacity{ 0 }, elem{ nullptr }
{}

template<typename TElem>
DynamicVector<TElem>::DynamicVector(int cap) :
	size{ 0 }, capacity{ cap }, elem{ new TElem[capacity] }
{}

template<typename TElem>
DynamicVector<TElem>::~DynamicVector()
{
	delete[] elem;
}

template<typename TElem>
DynamicVector<TElem>::DynamicVector(const DynamicVector& v) :
	size{ v.size }, capacity{ v.capacity }, elem{ new TElem[capacity] }
{
	for (int i = 0; i < v.size; ++i)
		elem[i] = v.elem[i];
}

template<typename TElem>
DynamicVector<TElem>& DynamicVector<TElem>::operator=(const DynamicVector& v)
{
	if (this == &v)
		return *this;

	size = v.size;
	capacity = v.capacity;

	delete[] elem;
	elem = new TElem[capacity];
	for (int i = 0; i < v.size; ++i)
		elem[i] = v.elem[i];

	return *this;
}

template<typename TElem>
DynamicVector<TElem> DynamicVector<TElem>::operator[](int ind)
{
	return elem[ind];
}

template<typename TElem>
void DynamicVector<TElem>::resize(int cap)
{
	if (cap <= capacity)
		return;

	TElem* new_elem = new TElem[cap];
	for (int i = 0; i < size; ++i)
		new_elem[i] = elem[i];

	delete[] elem;
	elem = new_elem;
	capacity = cap;
}

template<typename TElem>
void DynamicVector<TElem>::addElement(const TElem& e)
{
	if (size == capacity)
		if (size == 0)
			resize(2);
		else
			resize(2 * capacity);

	elem[size++] = e;
}

template<typename TElem>
void DynamicVector<TElem>::removeElement(int ind)
{
	for (int i = ind; i < size - 1; ++i)
		elem[i] = elem[i + 1];

	--size;
}

template<typename TElem>
void DynamicVector<TElem>::updateElement(int ind, TElem e)
{
	elem[ind] = e;
}

template<typename TElem>
int DynamicVector<TElem>::getSize()
{
	return size;
}

template<typename TElem>
TElem DynamicVector<TElem>::getElement(int ind)
{
	return elem[ind];
}
