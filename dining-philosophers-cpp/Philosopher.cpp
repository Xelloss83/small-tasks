#include <thread>

#include "Philosopher.h"
#include "ScopeGuard.h"

// helper to cover trying to obtain a fork, creating scope guard on fork on success
// or incrementing fail count and returning false on fail.
#define TRY_ACQUIRE_FORK_RETURN_ON_FAIL(fork, guard, failed_count) \
	if (!fork.TryAcquire()) \
	{ \
		++failed_count; \
		return false; \
	} \
	auto guard = MakeScopeGuard([&] { fork.Release(); });

// helper to cover fork obtaining with blocking until fork is obtained
// and creation of scope guard on that fork to automatically release it.
#define ACQUIRE_FORK(fork, guard) \
	fork.Acquire(); \
	auto guard = MakeScopeGuard([&] { fork.Release(); });


Philosopher::Philosopher(Fork& left_fork, Fork& right_fork, const std::atomic_bool& stop_signal)
	: m_left_fork(left_fork)
	, m_right_fork(right_fork)
	, m_stop_signal(stop_signal)
{

}

Philosopher::~Philosopher()
{

}

void Philosopher::Dine()
{
	while (!m_stop_signal)
	{
		if (!DecideToEat() || !Eat())
			// think in case philosopher does not want to eat or was not able to eat
			Think();
	}
}

bool Philosopher::Eat()
{
	// choosing ACQUIRE_FORK or TRY_ACQUIRE_FORK_RETURN_ON_FAIL will affect
	// philosopher behavior - will he think in case he cannot eat, or will
	// he wait for forks availability without thinking

	ACQUIRE_FORK(m_left_fork, left_guard);
	//TRY_ACQUIRE_FORK_RETURN_ON_FAIL(m_left_fork, left_guard, m_failed_attempts);

	//ACQUIRE_FORK(m_right_fork, right_guard);
	TRY_ACQUIRE_FORK_RETURN_ON_FAIL(m_right_fork, right_guard, m_failed_attempts);

	auto duration = GetDuration();
	auto end = std::chrono::steady_clock::now() + duration;
	while (std::chrono::steady_clock::now() < end)
		;

	m_eat_time += duration;
	++m_successed_attempts;
	return true;
}

void Philosopher::Think()
{
	auto duration = GetDuration();
	std::this_thread::sleep_for(duration);
	m_think_time += duration;
}

bool Philosopher::DecideToEat()
{
	// decide with equal probability
	std::bernoulli_distribution d;
	return d(m_random_engine);
}

std::chrono::milliseconds Philosopher::GetDuration(unsigned short min /*= 1*/, unsigned short max /*= 1000*/)
{
	std::uniform_int_distribution<> ms(min, max);
	return std::chrono::milliseconds(ms(m_random_engine));
}

/*
	Statistics
*/

std::chrono::milliseconds Philosopher::EatTime() const
{
	return m_eat_time;
}

std::chrono::milliseconds Philosopher::ThinkTime() const
{
	return m_think_time;
}

size_t Philosopher::FailedEatAttempts() const
{
	return m_failed_attempts;
}

size_t Philosopher::SuccessedEatAttempts() const
{
	return m_successed_attempts;
}