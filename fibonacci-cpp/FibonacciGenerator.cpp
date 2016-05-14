#include "FibonacciGenerator.h"
#include <cmath>


FibonacciGenerator::FibonacciGenerator(size_t initial_index /*= 0*/)
{
	if (initial_index != 0)
		Reset(initial_index);
}

FibonacciGenerator::~FibonacciGenerator()
{

}

size_t FibonacciGenerator::Index() const
{
	return m_index;
}

size_t FibonacciGenerator::Value() const
{
	return m_value;
}

void FibonacciGenerator::IterateNext()
{
	auto sum = m_previous_value + m_value;
	m_previous_value = m_value;
	m_value = sum;

	++m_index;
}

FibonacciGenerator& FibonacciGenerator::operator++()
{
	IterateNext();
	return *this;
}

FibonacciGenerator FibonacciGenerator::operator++(int unused)
{
	FibonacciGenerator temp = *this;
	IterateNext();
	return temp;
}

void FibonacciGenerator::IterateBack()
{
	if (m_index == 0)
		return;

	if (m_index == 1)
	{
		Reset();
		return;
	}

	--m_index;
	m_value = m_previous_value;
	m_previous_value = GetIndexValue(m_index - 1);
}

FibonacciGenerator& FibonacciGenerator::operator--()
{
	IterateBack();
	return *this;
}

FibonacciGenerator FibonacciGenerator::operator--(int unused)
{
	auto temp = *this;
	IterateBack();
	return temp;
}

FibonacciGenerator::operator size_t() const
{
	return Value();
}

void FibonacciGenerator::Reset(size_t initial_index /*= 0*/)
{
	m_index = initial_index;

	if (initial_index == 0)
	{
		m_value = 0;
		m_previous_value = 1;
	}
	else
	{
		m_value = GetIndexValue(initial_index);
		m_previous_value = GetIndexValue(initial_index - 1);
	}
}

size_t FibonacciGenerator::GetIndexValue(size_t index) const
{
	auto sqrt_5 = sqrt(5);
	return static_cast<size_t>((pow(1 + sqrt_5, index) - pow(1 - sqrt_5, index)) / (pow(2, index) * sqrt_5));
}
