#include <iostream>
#include <thread>

#include "Philosopher.h"
#include "Fork.h"

void main()
{
	const short numer_of_philosophers = 5;

	std::vector<Philosopher> philosophers;
	std::vector<Fork> forks(numer_of_philosophers);
	std::atomic_bool stop_signal = false;

	philosophers.reserve(numer_of_philosophers);

	for (short i = 0; i < numer_of_philosophers; ++i)
	{
		int left = i;
		int right = (i + 1) % numer_of_philosophers;
		if (left > right)
			// use strict order approach
			// fork on the left always has lower number
			std::swap(left, right);

		philosophers.emplace_back(forks[left], forks[right], stop_signal);
	}

	std::vector<std::thread> threads;
	threads.reserve(numer_of_philosophers);
	for (auto& ph : philosophers)
		threads.emplace_back([&] { ph.Dine(); });

	std::wcout << L"Press Enter to stop...\n";
	std::wcin.get();

	stop_signal.store(true, std::memory_order_release);
	for (auto& th : threads)
		th.join();

	std::wcout << L"Results:\n";
	for (auto& ph : philosophers)
	{
		std::wcout
			<< L"Eat "
			<< ph.SuccessedEatAttempts()
			<< L" times for "
			<< ph.EatTime().count()
			<< L" milliseconds. Failed to eat "
			<< ph.FailedEatAttempts()
			<< L" times. Was thinking for "
			<< ph.ThinkTime().count()
			<< L" milliseconds"
			<< std::endl;
	}

	std::wcout << L"Press Enter...\n";
	std::wcin.get();
}
