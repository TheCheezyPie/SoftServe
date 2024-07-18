#pragma once

#include <type_traits>
#include <typeinfo>
#include <exception>
#include <variant>

struct BadCastException : public std::exception
{
	const char* what() const throw()
	{
		return "Bad cast exception";
	}
};

class AnyType
{
public:
	AnyType() {};

	template <typename T>
	AnyType(T val)
	{
		value = val;
	}

	// Copy constructors and assignment operators
	AnyType(const AnyType& other)
	{
		value = other.value;
	}
	AnyType& operator=(const AnyType& other)
	{
		value = other.value;
		return *this;
	}

	// Move constructors and assignment operators
	AnyType(AnyType&& other) noexcept
	{
		value = std::move(other.value);
	}
	AnyType& operator=(AnyType&& other) noexcept
	{
		value = std::move(other.value);
		return *this;
	}

	void Swap(AnyType& other)
	{
		std::swap(value, other.value);
	}

	// returns void if the type is not one of the specified types
	const type_info& GetType() const
	{
		switch (value.index())
		{
		case 0:
			return typeid(int);
		case 1:
			return typeid(float);
		case 2:
			return typeid(double);
		case 3:
			return typeid(char);
		case 4:
			return typeid(bool);
		default:
			break;
		}

		return typeid(void);
	}

	void Destroy()
	{
		value = 0;
	}

	template <typename T>
	AnyType operator=(const T& NewValue)
	{
		value = NewValue;
		return *this;
	}

	template <typename T>
	T To() const
	{
		if (std::holds_alternative<T>(value))
		{
			return std::get<T>(value);
		}
		else
		{
			throw BadCastException();
		}
	}

	int ToInt() const
	{
		if (std::holds_alternative<int>(value))
		{
			return std::get<int>(value);
		}
		else
		{
			throw BadCastException();
		}
	}

	double ToDouble() const
	{
		if (std::holds_alternative<double>(value))
		{
			return std::get<double>(value);
		}
		else
		{
			throw BadCastException();
		}
	}

private:
	std::variant<int, float, double, char, bool> value;

};