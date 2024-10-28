#pragma once
#include "Node.h"

template <typename T, size_t ... N>
class ScalarAdditionOperation : public Node<T, N...>
{
private:
	T scalar;
public:
	ScalarAdditionOperation(T scalarValue) : scalar(scalarValue) {}

	virtual Tensor<T, N...> evaluate(const std::vector<Tensor<T, N...>>& operands) const override
	{
		if (operands.size() != 1) 
		{
			throw OperandCountMismatchException("Scalar addition operation requires exactly one operand.");
		}

		const Tensor<T, N...>& operand = operands[0];
		Tensor<T, N...> result = operand + scalar;
		return result;
	}
	virtual int getOperation() const override
	{
		return 0;
	};
	virtual std::ofstream& serialize(std::ofstream& os) const override
	{
		os << "A" << scalar;
		return os;
	}

};