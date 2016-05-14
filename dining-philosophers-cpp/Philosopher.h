#pragma once

#include <random>
#include <chrono>

#include "Fork.h"

class Philosopher
{
public:
	Philosopher(Fork& left_fork, Fork& right_fork, const std::atomic_bool& stop_signal);
	~Philosopher();

	void Dine(); // to be called to start eating and thinking

	// statistics
	std::chrono::milliseconds EatTime() const;
	std::chrono::milliseconds ThinkTime() const;
	size_t FailedEatAttempts() const;
	size_t SuccessedEatAttempts() const;

private:
	bool Eat(); // covers eating process
	void Think(); // covers thinking process

	bool DecideToEat(); // to decide is philosopher want to eat
	std::chrono::milliseconds GetDuration(unsigned short min = 0, unsigned short max = 1000); // get duration in interval

	Fork& m_left_fork;
	Fork& m_right_fork;

	const std::atomic_bool& m_stop_signal;

	std::mt19937_64 m_random_engine{ std::random_device{}() };
	
	// statistics
	std::chrono::milliseconds m_eat_time{ 0 };
	std::chrono::milliseconds m_think_time{ 0 };
	size_t m_failed_attempts{ 0 };
	size_t m_successed_attempts{ 0 };
};

