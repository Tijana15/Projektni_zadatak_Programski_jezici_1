#pragma once
#include <memory>
#include <set>
#include "Node.h"

template<typename T, size_t ... N>
class OperandNode : public Node<T,N...>
{
private:
	std::vector<size_t> dims;
	std::shared_ptr<Tensor<T,N...>> pointT;
public:
	OperandNode() : pointT(nullptr), dims{} {}

	OperandNode(const Tensor<T, N...>& tensor) : pointT(std::make_shared<Tensor<T,N...>>(tensor)), dims(tensor.getDim()) {}

	virtual Tensor<T, N...> evaluate(const std::vector<Tensor<T, N...>>& operands = {}) const
	{
		if (operands.size() == 0)
		{
			return *pointT;
		}
		else
		{
			throw OperandCountMismatchException("Error");
		}
	}

	virtual int getOperation() const 
	{
		return 1;
	}

	std::vector<size_t> getDim() const
	{
		return dims;
	}
	virtual std::ofstream& serialize(std::ofstream& os) const override
	{
		os << "o ";
		(*pointT).serialize(os);
		return os;
	}


};
