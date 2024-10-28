#include"Concepts.h"
#include"Tensor.h"
#include"Graph.h"
#include"AdditionOperation.h"
#include"MultiplicationOperation.h"
#include"NegationOperation.h"
#include"Node.h"
#include"ScalarAdditionOperation.h"
#include"ScalarMultiplicationOperation.h"
#include"SubtractionOperation.h"
#include"OperandNode.h"
#include <vector>
#include <iostream>
#include <fstream>

int main()
{
	try
	{
		Tensor<int, 2, 2, 3> tensor1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::cout << "Tensor1: dynamic " << tensor1;

		std::ofstream testFajl("Test.txt");
		tensor1.serialize(testFajl);
		testFajl.close();

		Tensor<int> tensor3;
		std::ifstream test2("Test.txt");
		tensor3.deserialize(test2);
		std::cout << "Tensor3:dynamic " << tensor3;
		test2.close();

		Tensor<int, 2, 2, 3> tensor4 = { 1,3,5,7,9,11,13,15,17,19,21,23 };
		std::cout << "Tensor4: dynamic " << tensor4;
		std::cout << "Tensor1+Tensor4: " << tensor1 + tensor4;
		std::cout << "Tensor4+3: " << tensor4 + 3;
		std::cout << "Tensor1-Tensor4: " << tensor1 - tensor4;
		std::cout << "Tensor1*Tensor4: " << tensor1 * tensor4;
		std::cout << "Tensor4 * 2: " << tensor4 * 2;
		std::cout << "-Tensor4" << -tensor4;

		Tensor<int> tensor2;
		tensor2.setDims({ 2,2,3 });
		tensor2.setTen({ 1, 2, 3, 4, 5, 6 ,7,8,9,10,11,12 });
		std::cout << "Tensor2: static " << tensor2 << std::endl;

		OperandNode<int, 2, 2, 3> on1(tensor1);
		OperandNode<int, 2, 2, 3> on2(tensor4);

		std::cout << "on1.evaluate: " << on1.evaluate() << std::endl;
		std::cout << "on2.evaluate: " << on2.evaluate() << std::endl;

		Graph<int, 2, 2, 3> g1;
		g1.addNode(std::make_shared<OperandNode<int, 2, 2, 3>>(on1));
		g1.addNode(std::make_shared<OperandNode<int, 2, 2, 3>>(on2));
		std::cout << "g1.evaluate(0): " << g1.evaluate(0) << std::endl;
		std::cout << "g1.evaluate(1): " << g1.evaluate(1) << std::endl;

		/*std::vector<Tensor<int, 2, 2, 3>> vec1;
		vec1.push_back(tensor1);
		vec1.push_back(tensor4);

		AdditionOperation<int, 2, 2, 3> ad1;
		std::cout << "ad1.evaluate(): " << ad1.evaluate(vec1);

		Graph <int,2, 2, 3> g;
		g.addNode(std::make_shared<AdditionOperation<int,2,2,3>>(ad1));*/

		AdditionOperation<int, 2, 2, 3> ad1;
		g1.addNode(std::make_shared<AdditionOperation<int, 2, 2, 3>>(ad1));
		g1.connectNodes(2, 0);
		g1.connectNodes(2, 1);
		std::cout << "g1.evaluate(2): " << g1.evaluate(2) << std::endl;

		Tensor<int, 2, 2, 3> tensor5 = { 1,2,1,2,1,2,1,2,1,2,1,2 };
		OperandNode<int, 2, 2, 3> on3(tensor5);
		g1.addNode(std::make_shared<OperandNode<int, 2, 2, 3>>(on3));

		SubtractionOperation<int, 2, 2, 3> ad2;
		g1.addNode(std::make_shared<SubtractionOperation<int, 2, 2, 3>>(ad2));
		g1.connectNodes(4, 2);
		g1.connectNodes(4, 3);
		std::cout << "g1.evaluate(4):  " << g1.evaluate(4) << std::endl;

		NegationOperation<int, 2, 2, 3> n3;
		g1.addNode(std::make_shared<NegationOperation<int, 2, 2, 3>>(n3));
		g1.connectNodes(5, 4);
		std::cout << "g1.evaluate(5):  " << g1.evaluate(5) << std::endl;

		std::ofstream testGraf("Graf.txt");
		g1.serialize(testGraf);
		testGraf.close();

		Graph<int> deserialized;
		std::ifstream testGraf1("Graf.txt");
		deserialized.deserialize(testGraf1);
		testGraf1.close();

		std::ofstream testic2("Graf1.txt");
		deserialized.serialize(testic2);
		std::cout << "deserialized.evaluate(5): " << deserialized.evaluate(5);
	}
	catch (DimensionsDismatchException& e)
	{
		std::cout << e.what();
	}
	catch (FileAcessException& e)
	{
		std::cout << e.what();
	}
	catch (OperandCountMismatchException& e)
	{
		std::cout << e.what();
	}
	catch (NodeNotFoundException& e)
	{
		std::cout << e.what();
	}
	catch (NodesAlreadyConnectedException& e)
	{
		std::cout << e.what();
	}
	catch (UnsupportedOperationTypeException& e)
	{
		std::cout << e.what();
	}


};