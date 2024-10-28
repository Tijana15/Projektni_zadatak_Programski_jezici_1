#pragma once
#include <vector>
#include <type_traits>
#include <iostream>
#include <fstream>
#include <functional>
#include"Concepts.h"
#include"Tensor.h"
#include"Node.h"
#include"OperandNode.h"
#include"AdditionOperation.h"
#include"MultiplicationOperation.h"
#include"NegationOperation.h"
#include"ScalarAdditionOperation.h"
#include"ScalarMultiplicationOperation.h"
#include"SubtractionOperation.h"

template <typename T, size_t ... N>
class Graph
{
private:
	//static std::map<std::string, std::function<std::shared_ptr<Node>()>> operationFactoryMap;
	std::vector<std::shared_ptr<const Node<T, N...>>> nodes;
	std::vector<std::vector<int>> neighborhoodMatrix;

public:
	Graph()
	{
		nodes = {};
		neighborhoodMatrix = {};
	}

	void addNode(std::shared_ptr<const Node<T, N...>> node)
	{
		if (node != nullptr)
		{
			nodes.push_back(node);
			size_t newSize = nodes.size();
			for (size_t i = 0; i < newSize - 1; i++) {
				neighborhoodMatrix[i].push_back(0);
			}
			neighborhoodMatrix.push_back(std::vector<int>(newSize, 0));
		}
		else
		{
			throw NodeNotFoundException("Try to add empty node failed.");
		}
	}

	void connectNodes(int source, int destination)
	{
		if (source >= nodes.size() || destination >= nodes.size())
		{
			throw NodeNotFoundException("Node not found.");
		}

		if (source == destination)
		{
			throw std::invalid_argument("Cannot connect a node to itself.");
		}
		if (neighborhoodMatrix[source][destination] == 1)
		{
			throw NodesAlreadyConnectedException("Nodes are already connected.");
		}
		neighborhoodMatrix[source][destination] = 1;
	}


	Tensor<T, N...> evaluate(size_t nodeId)
	{
		if (nodeId >= nodes.size())
			throw std::out_of_range("ID doesn't exist!");

		if (nodes[nodeId]->getOperation())
			return nodes[nodeId]->evaluate();
		else
		{
			std::vector<Tensor<T, N...>> operands;
			for (size_t i = 0; i < nodes.size(); i++)
			{
				if (neighborhoodMatrix[nodeId][i])
				{
					Tensor<T, N...> temp = this->evaluate(i);
					operands.push_back(temp);
				}
			}
			return nodes[nodeId]->evaluate(operands);
		}
	}
	void printMatrix(std::ofstream& os)const
	{
		for (size_t i = 0; i < nodes.size(); i++)
		{
			for (size_t j = 0; j < nodes.size(); j++)
			{
				os << neighborhoodMatrix[i][j] << " ";
			}
		}
	}
	std::ofstream& serialize(std::ofstream& os)const
	{
		os << nodes.size() << std::endl;
		for (auto& node : nodes)
		{
			node->serialize(os);
			os << std::endl;
		}
		printMatrix(os);
		return os;

	}
	void deserialize(std::ifstream& inFile)
	{
		size_t graphSize;
		inFile >> graphSize;
		char nodeType;
		for (size_t i = 0; i < graphSize; i++)
		{
			inFile >> nodeType;
			if (nodeType == 'o')
			{
				Tensor<T, N...> tensor;
				tensor.deserialize(inFile);
				//nodes.push_back(std::make_shared < OperandNode<T, N...>(tensor));
				OperandNode<T, N...> operandNode(tensor);
				this->addNode(std::make_shared<OperandNode<T, N...>>(operandNode));
			}
			else if (nodeType == '-')
			{
				SubtractionOperation<T, N...> subtraction;
				this->addNode(std::make_shared<SubtractionOperation<T, N...>>(subtraction));

			}
			else if (nodeType == '+')
			{
				AdditionOperation<T, N...> addition;
				this->addNode(std::make_shared<AdditionOperation<T, N...>>(addition));
			}
			else if (nodeType == '*')
			{
				MultiplicationOperation<T, N...> multi;
				this->addNode(std::make_shared<MultiplicationOperation<T, N...>>(multi));

			}
			else if (nodeType == '!')
			{
				NegationOperation<T, N...> negation;
				this->addNode(std::make_shared<NegationOperation<T, N...>>(negation));
			}
			/*else if (nodeType == 'A')
			{
				T scalar;
				inFile >> scalar;
				ScalarAdditionOperation<T, N...> scA(scalar);
				this->addNode(std::make_shared<ScalarAdditionOperation<T, N...>>(scA));

			}
			else if (nodeType == 'M')
			{
				T scalar;
				inFile>> scalar;
				ScalarMultiplicationOperation<T, N...> scM(scalar);
				this->addNode(std::make_shared<ScalarMultiplicationOperation<T, N...>>(scM));

			}*/
			else
			{
				throw UnsupportedOperationTypeException("Unsupported operation type: " + nodeType);
			}

		}
		for (int i = 0; i < graphSize; i++)
		{
			for (int j = 0; j < graphSize; j++)
			{
				inFile >> neighborhoodMatrix[i][j];
			}
		}
	}
};
