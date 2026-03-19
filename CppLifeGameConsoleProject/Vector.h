#pragma once

template <typename T>
struct Vector
{
	T* items{};
	int size{};
};

template <typename T>
void PushBack(Vector<T>& vector, T value)
{
	T* array = new T[vector.size + 1];
	for (int i{}; i < vector.size; i++)
		array[i] = vector.items[i];
	array[vector.size] = value;

	delete[] vector.items;
	vector.items = array;
	vector.size++;
}


template <typename T>
void Insert(Vector<T>& vector, int index, T value)
{
	T* array = new T[vector.size + 1];
	for (int i{}; i < index; i++)
		array[i] = vector.items[i];
	array[index] = value;
	for (int i{ index + 1 }; i < vector.size; i++)
		array[i] = vector.items[i - 1];

	delete[] vector.items;
	vector.items = array;
	vector.size++;
}

template <typename T>
T PopBack(Vector<T>& vector)
{
	T value = vector.items[vector.size - 1];

	T* array = new T[vector.size - 1];
	for (int i{}; i < vector.size - 1; i++)
		array[i] = vector.items[i];

	delete[] vector.items;
	vector.items = array;
	vector.size--;

	return value;
}

template <typename T>
T Remove(Vector<T>& vector, int index)
{
	T value = vector.items[index];

	T* array = new T[vector.size - 1];
	for (int i{}; i < index; i++)
		array[i] = vector.items[i];
	for (int i{ index + 1 }; i < vector.size; i++)
		array[i - 1] = vector.items[i];

	delete[] vector.items;
	vector.items = array;
	vector.size--;

	return value;
}

template <typename T>
void SetItem(Vector<T> vector, int index, T value)
{
	vector.items[index] = value;
}

template <typename T>
T GetItem(Vector<T> vector, int index)
{
	return vector.items[index];
}