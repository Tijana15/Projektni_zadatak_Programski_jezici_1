#pragma once
#include "Node.h"

template <typename T, size_t ... N>
class NegationOperation : public Node<T, N...>
{
public:
	virtual Tensor<T, N...> evaluate(const std::vector<Tensor<T, N...>>& operands) const override
	{
		if (operands.size() != 1)
		{
			throw OperandCountMismatchException("Negation operation requires exactly one operand.");
		}

		const Tensor<T, N...>& operand = operands[0];
		Tensor<T, N...> result = -operand;
		return result;
	}
	virtual int getOperation() const override
	{
		return 0;
	};
	virtual std::ofstream& serialize(std::ofstream& os) const override
	{
		os << "!";
		return os;
	}

};