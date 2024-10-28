#pragma once
#include <concepts>
#include <memory>
#include <vector>

template <typename T>
concept Addable = requires (T & a, T & b)
{
	{a + b}->std::convertible_to<T>;
};

template<typename T>
concept Subtractable = requires(T & a, T & b)
{
	{a - b}->std::convertible_to<T>;
};

template<typename T>
concept Multiplayable = requires(T & a, T & b)
{
	{a* b}->std::convertible_to<T>;
};

template<typename T>
concept Negatable = requires(T & a)
{
	{-a}->std::convertible_to<T>;
};

template<typename T>
concept Scalable = requires(T & a, double b)
{
	{a* b}->std::convertible_to<T>;
	{a + b}->std::convertible_to<T>;
};

template<typename T>
concept OverloadedOperators = Addable<T> && Subtractable<T> && Multiplayable<T> && Negatable<T> && Scalable<T>;

template <typename T>
concept Serializable = requires(std::ofstream & fileO, T & a)
{
	{fileO << a}->std::convertible_to<std::ifstream&>;
};

template<typename T>
concept Deserializable = requires(std::ifstream & fileI, T & a)
{
	{fileI >> a}->std::convertible_to<std::ifstream&>;
};

template <typename T>
concept Graphable = Serializable<T> && Deserializable<T>;