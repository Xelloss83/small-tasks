#include <iostream>
#include <vector>

#include "FibonacciGenerator.h"

void main()
{
	const size_t limit = 1000;

	{
		std::wcout << L"Even Fibonacci numbers less than " << limit << std::endl;

		std::vector<size_t> fib_from_generator;
		std::vector<size_t> fib_from_iterative;
		FillFibonacciSequenceWithGenerator(fib_from_generator, [](size_t val) { return val % 2 == 0; }, limit);
		FillFibonacciSequenceIterative(fib_from_iterative, [](size_t val) { return val % 2 == 0; }, limit);

		auto gen_it = fib_from_generator.begin();
		auto iter_it = fib_from_iterative.begin();

		for (; gen_it != fib_from_generator.end() && iter_it != fib_from_iterative.end(); ++gen_it, ++iter_it)
			std::wcout << L"From generator: " << *gen_it << L", iterative: " << *iter_it << std::endl;

		if (gen_it != fib_from_generator.end() || iter_it != fib_from_iterative.end())
			std::wcout << L"Incorrect sequence length generated." << std::endl;
	}

	{
		std::vector<size_t> fib_from_recursion;
		{
			FibonacciSequenceGeneratorRecurse<std::vector<size_t>> gen(fib_from_recursion, limit);
		}

		std::wcout << L"\nFibonacci numbers less than " << limit << " from recursion" << std::endl;
		for (auto& val : fib_from_recursion)
			std::wcout << val << L" ";
	}
	
	{
		std::wcout << L"\n\nSum of all even Fibonacci numbers in interval [0, " << limit << ") is: "
			<< CalculateFibonacciSum(0, limit, [](size_t val) { return val % 2 == 0; })
			<< std::endl;
	}

	std::wcout << L"\nPress enter..." << std::endl;
	std::wcin.get();
}