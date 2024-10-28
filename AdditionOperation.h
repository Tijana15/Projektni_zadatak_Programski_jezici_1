#pragma once
#include "Node.h"  

template <typename T, size_t ... N>
class AdditionOperation : public Node<T, N...>
{
public:
	virtual Tensor<T, N...> evaluate(const std::vector<Tensor<T, N...>>& operands) const override
	{
		if (operands.size() != 2) 
		{
			throw OperandCountMismatchException("Addition operation requires exactly two operands.");
		}

		const Tensor<T, N...>& operand1 = operands[0];
		const Tensor<T, N...>& operand2 = operands[1];
		/* Tensor<T, N...> result = {};
		 for (size_t i = 0; i < operand1.size(); i++)
		 {
			 result[i] = operand1[i] + operand2[i];
		 }
		 return result;*/
		return operand1 + operand2;
	}
	virtual int getOperation() const override
	{
		return 0;
	};
	virtual std::ofstream& serialize(std::ofstream& os) const override
	{
		os << "+";
		return os;
	}


};

