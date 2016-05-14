#include <thread>

#include "Fork.h"

Fork::Fork()
{

}

Fork::~Fork()
{

}

bool Fork::TryAcquire()
{
	return !m_acquired.exchange(true, std::memory_order_acquire);
}

void Fork::Acquire()
{
	while (!m_acquired.exchange(true, std::memory_order_acquire))
		std::this_thread::yield();
}

void Fork::Release()
{
	m_acquired.store(false, std::memory_order_release);
}

bool Fork::IsAcquired() const
{
	return m_acquired.load(std::memory_order_acq_rel);
}
