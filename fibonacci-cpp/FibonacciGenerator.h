#pragma once

#include <functional>

/*
	Fibonacci value generator. Generates values one by one on request.
	Support not only going to the next greater value, but also
	going back to lesser value. Can be done by ++ (--) operators
	and IterateNext (IterateBack) methods.
	Support automatic conversion to current value.
	Possible to initialize to value of any index.
	Binet's Fibonacci Number Formula is used to calculate value of
	arbitrary index. Standard rule is used to generate next value.
*/
class FibonacciGenerator
{
public:
	explicit FibonacciGenerator(size_t initial_index = 0);
	~FibonacciGenerator();

	size_t Index() const;
	size_t Value() const;
	
	void IterateNext();
	FibonacciGenerator& operator++();
	FibonacciGenerator operator++(int unused);

	void IterateBack();
	FibonacciGenerator& operator--();
	FibonacciGenerator operator--(int unused);

	operator size_t() const;

	void Reset(size_t initial_index = 0);

private:
	// Use Binet's Fibonacci Number Formula to get value of arbitrary index
	size_t GetIndexValue(size_t index) const;

	size_t m_index = 0;
	size_t m_value = 0;
	size_t m_previous_value = 1;
};


/*
	Recursively fill passed container with Fibonacci numbers with values less than requested.
	To save stack space during recursion (to not to pass limit and generated values)
	class is introduced. Generated values and generation limit are stored as that class
	fields, so only one pointer is stored on the stack on each level of recursion.
*/
template <typename Container>
class FibonacciSequenceGeneratorRecurse
{
public:
	explicit FibonacciSequenceGeneratorRecurse(Container& container, size_t less_than = 1000)
		: m_values(container)
		, m_limit(less_than)
	{
		if (less_than == 0)
			return;

		m_values.push_back(0);
		m_values.push_back(1);

		FillSequenceRecurse();
	}

	FibonacciSequenceGeneratorRecurse(const FibonacciSequenceGeneratorRecurse<Container>&) = delete;
	FibonacciSequenceGeneratorRecurse(const FibonacciSequenceGeneratorRecurse<Container>&&) = delete;
	FibonacciSequenceGeneratorRecurse& operator=(const FibonacciSequenceGeneratorRecurse<Container>&) = delete;
	FibonacciSequenceGeneratorRecurse& operator=(const FibonacciSequenceGeneratorRecurse<Container>&&) = delete;

private:
	void FillSequenceRecurse()
	{
		auto prev_it = --m_values.end();
		auto last_it = prev_it--;

		auto sum = *prev_it + *last_it;
		if (sum >= m_limit)
			return;

		m_values.push_back(sum);

		FillSequenceRecurse();
	}

	Container& m_values;
	size_t m_limit = 0;
};

template <template <typename, typename> class Container>
void FillFibonacciSequenceWithGenerator(Container<size_t, std::allocator<size_t>>& container, const std::function<bool(size_t)>& pred = [](size_t) { return true; }, size_t less_than = 1000)
{
	for (FibonacciGenerator fib_gen; fib_gen < less_than; ++fib_gen)
	{
		if (pred(fib_gen))
			container.push_back(fib_gen);
	}
}

template <template <typename, typename> class Container>
void FillFibonacciSequenceIterative(Container<size_t, std::allocator<size_t>>& container, const std::function<bool(size_t)>& pred = [](size_t) { return true; }, size_t less_than = 1000)
{
	size_t current_val = 0;
	size_t prev_val = 1;

	while (current_val < less_than)
	{
		if (pred(current_val))
			container.push_back(current_val);
		auto sum = current_val + prev_val;
		prev_val = current_val;
		current_val = sum;
	}
}

inline size_t CalculateFibonacciSum(size_t not_less_than = 0, size_t smaller_than = 1000, const std::function<bool(size_t)>& pred = [](size_t) { return true; })
{
	size_t result = 0;
	for (FibonacciGenerator gen; gen < smaller_than; ++gen)
	{
		if (gen >= not_less_than && pred(gen))
			result += gen;
	}

	return result;
}