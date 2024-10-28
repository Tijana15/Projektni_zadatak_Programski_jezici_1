#pragma once
#include <iostream>
#include "Tensor.h"

template <typename T, size_t ... N>
class Node
{
public:
	virtual Tensor<T, N...> evaluate(const std::vector<Tensor<T, N...>>& operands = {}) const = 0;
	virtual int getOperation() const = 0;
	virtual std::ofstream& serialize(std::ofstream& os) const = 0;
};
