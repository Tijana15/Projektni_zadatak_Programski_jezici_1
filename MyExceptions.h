#pragma once
#include <exception>
class DimensionsDismatchException : public std::exception
{
public:
	using std::exception::exception;
};
class FileAcessException : public std::exception
{
public:
	using std::exception::exception;
};
class OperandCountMismatchException : public std::exception
{
public:
	using std::exception::exception;
};
class NodeNotFoundException : public std::exception
{
public:
	using std::exception::exception;
};
class NodesAlreadyConnectedException : public std::exception
{
	using std::exception::exception;
};
class UnsupportedOperationTypeException :public std::exception
{
	using std::exception::exception;
};