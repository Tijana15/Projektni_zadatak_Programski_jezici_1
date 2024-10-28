#pragma once
#include <iostream>
#include <fstream>
#include <concepts>
#include <vector>
#include <memory>
#include <type_traits>
#include "Concepts.h"
#include "MyExceptions.h"

template <typename T, size_t ...N>
	requires OverloadedOperators<T>
class Tensor
{
private:
	std::vector<T> tensor;
	std::vector<size_t> dim;
	size_t sizeOfTensor;
public:
	Tensor() : tensor{}, dim{ N... }, sizeOfTensor(0) {}
	//Tensor(std::vector<T> tensor,size_t s, std::vector<size_t> dim) : dim(dim),sizeOfTensor(s), tensor(tensor) {};
	Tensor(std::initializer_list<T> list) : dim{ N... }, sizeOfTensor(1)
	{
		size_t valid = 0;
		for (size_t i = 0; i < dim.size(); i++)
		{
			sizeOfTensor *= dim[i];
		}
		for (auto& elem : list)
		{
			valid++;
			if (valid <= sizeOfTensor)
			{
				tensor.push_back(elem);
			}
			else throw DimensionsDismatchException("Too many elements. Dimensions mismatch.");
		}
		if (valid < sizeOfTensor)
			throw DimensionsDismatchException("Not enough elements. Dimensions mismatch.");
	}
	Tensor(const Tensor<T, N...>& other)
	{
		this->tensor = other.tensor;
		this->dim = other.dim;
		this->sizeOfTensor = other.sizeOfTensor;
	}
	Tensor<T, N...> operator+(const Tensor<T, N...>& other) const
	{
		Tensor<T, N...> sum(*this);
		for (size_t i = 0; i < sum.size(); i++)
		{
			sum[i] += other[i];
		}
		return sum;
	}
	Tensor<T, N...> operator-(const Tensor<T, N...>& other)const
	{
		Tensor<T, N...> sub(*this);
		for (size_t i = 0; i < sub.size(); i++)
		{
			sub[i] -= other[i];
		}
		return sub;
	}
	Tensor<T, N...> operator*(const Tensor<T, N...>& other)const
	{
		Tensor<T, N...> mul(*this);
		for (size_t i = 0; i < mul.size(); i++)
		{
			mul[i] *= other[i];
		}
		return mul;
	}
	Tensor <T, N...> operator-()const
	{
		Tensor<T, N...> negative(*this);
		for (size_t i = 0; i < negative.size(); i++)
		{
			negative[i] = -(*this)[i];
		}
		return negative;
	}
	Tensor <T, N...> operator+(const size_t scalar)
	{
		Tensor<T, N...> sums(*this);
		for (size_t i = 0; i < sums.size(); i++)
		{
			sums[i] += scalar;
		}
		return sums;
	}
	Tensor <T, N...> operator*(const size_t scalar)
	{
		Tensor<T, N...> muls(*this);
		for (size_t i = 0; i < muls.size(); i++)
		{
			muls[i] *= scalar;
		}
		return muls;
	}
	size_t size() const
	{
		return tensor.size();
	}
	std::vector<size_t> getTensorVal()
	{
		return this->tensor;
	}
	T& operator[](size_t i)
	{
		return tensor[i];
	}
	const T& operator[](size_t i)const
	{
		return tensor[i];
	}
	std::vector<size_t> getDim() const
	{
		return this->dim;
	}
	template <typename T, size_t ...N >
	friend std::ostream& operator<<(std::ostream& os, const Tensor<T, N...>& t)
	{
		os << "{ ";
		((os << N << ", "), ...);
		os << "\b\b} ";  // Brisanje posljednjeg zareza

		os << "{";
		for (size_t i = 0; i < t.tensor.size(); i++)
		{
			os << t.tensor[i];
			if (i != t.tensor.size() - 1)
				os << ", ";
		}
		os << "}" << std::endl;

		return os;
	}
	std::ofstream& serialize(std::ofstream& outFile)
	{
		outFile << sizeof...(N) << ' ';
		((outFile << N << ' '), ...);

		for (const auto& value : tensor)
		{
			outFile << value << ' ';
		}
		return outFile;
	}
	void deserialize(std::ifstream& inFile)
	{
		std::vector<size_t> dim;
		size_t numDims;
		inFile >> numDims;
		dim.resize(numDims);

		for (size_t i = 0; i < numDims; ++i)
		{
			inFile >> dim[i];
		}
		tensor = Tensor<T, N...>(dim);

		for (size_t i = 0; i < tensor.size(); ++i)
		{
			inFile >> tensor[i];
		}
	}
	void setSize(size_t tensSize)
	{
		this->sizeOfTensor = tensSize;
	}
	void setDims(std::vector<size_t> dims)
	{
		this->dim = dims;
	}
	void setTen(std::vector<T> tens)
	{
		this->tensor = tens;
	}
};


template<typename T>
	requires OverloadedOperators<T>
class Tensor<T>
{
private:
	std::vector<T> tensor;
	std::vector<size_t> dim;
	size_t sizeOfTensor;
public:
	Tensor() : tensor{}, dim{}, sizeOfTensor(0) {};
	Tensor(std::initializer_list<T> list, std::vector<size_t> dim) :dim(dim)
	{
		size_t valid = 0;	
		for (size_t i = 0; i < dim.size(); i++)
		{
			sizeOfTensor *= dim[i];
		}
		for (auto& elem : list)
		{
			valid++;
			if (valid <= sizeOfTensor)
			{
				tensor.push_back(elem);
			}
			else throw std::exception("Dimenzije se ne poklapaju.");
		}
		if (valid < sizeOfTensor)
			throw std::exception("Dimenzije se ne poklapaju.");
	}
	//Tensor(std::vector<size_t> dim) : tensor(NULL), dim(dim), sizeOfTensor(dim.size()) {};
	Tensor(const Tensor<T>& other)
	{
		this->tensor = other.tensor;
		this->dim = other.dim;
		this->sizeOfTensor = other.sizeOfTensor;
	}
	Tensor<T> operator+(const Tensor<T>& other) const
	{
		Tensor<T> sum(*this);
		for (size_t i = 0; i < sum.size(); i++)
		{
			sum[i] += other[i];
		}
		return sum;
	}
	Tensor<T> operator-(const Tensor<T>& other)const
	{
		Tensor<T> sub(*this);
		for (size_t i = 0; i < sub.size(); i++)
		{
			sub[i] -= other[i];
		}
		return sub;
	}
	Tensor<T> operator*(const Tensor<T>& other)const
	{
		Tensor<T> mul(*this);
		for (size_t i = 0; i < mul.size(); i++)
		{
			mul[i] *= other[i];
		}
		return mul;

	}
	Tensor <T> operator-()const
	{
		Tensor<T> negative(*this);
		for (size_t i = 0; i < negative.size(); i++)
		{
			negative[i] = -(*this)[i];
		}
		return negative;
	}
	Tensor <T> operator+(const size_t scalar)
	{
		Tensor<T> sums(*this);
		for (size_t i = 0; i < sums.size(); i++)
		{
			sums[i] += scalar;
		}
		return sums;
	}
	Tensor <T> operator*(const size_t scalar)
	{
		Tensor<T> muls(*this);
		for (size_t i = 0; i < muls.size(); i++)
		{
			muls[i] *= scalar;
		}
		return muls;
	}
	void setSize(size_t tensSize)
	{
		this->sizeOfTensor = tensSize;
	}
	void setDims(std::vector<size_t> dims)
	{
		this->dim = dims;
	}
	void setTen(std::vector<T> tens)
	{
		this->tensor = tens;
	}
	size_t size() const
	{
		return tensor.size();
	}
	std::vector<size_t> getTensorVal()const
	{
		return this->tensor;
	}
	T& operator[](size_t i)
	{
		return tensor[i];
	}
	const T& operator[](size_t i)const
	{
		return tensor[i];
	}
	std::vector<size_t> getDim() const
	{
		return this->dim;
	}
	friend std::ostream& operator<<(std::ostream& os, const Tensor<T>& t)
	{
		os << "{";
		for (size_t i = 0; i < t.dim.size(); i++)
		{
			os << t.dim[i];
			if (i != t.dim.size() - 1)
				os << ", ";
		}
		os << " }";
		os << "{";
		for (size_t i = 0; i < t.tensor.size(); i++)
		{
			os << t.tensor[i];
			if (i != t.tensor.size() - 1)
				os << ", ";
		}
		os << "}" << std::endl;

		return os;
	}
	void serialize(std::ofstream& outputFile) const
	{
		outputFile << dim.size() << " ";    // Broj dimenzija
		for (size_t dimSize : dim)
		{
			outputFile << dimSize << " ";  // Dimenzije
		}
		for (const auto& value : tensor)
		{
			outputFile << value << " ";     // Vrijednosti
		}
	}
	void deserialize(std::ifstream& inputFile)
	{
		size_t numDimensions;
		inputFile >> numDimensions;
		dim.resize(numDimensions);

		for (size_t i = 0; i < numDimensions; i++)
		{
			inputFile >> dim[i];
		}

		sizeOfTensor = 1;
		for (size_t dimSize : dim)
		{
			sizeOfTensor *= dimSize;
		}
		tensor.resize(sizeOfTensor);

		for (size_t i = 0; i < sizeOfTensor; i++)
		{
			inputFile >> tensor[i];
		}
	}
};