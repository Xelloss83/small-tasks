#pragma once

#include <atomic>

class Fork
{
public:
	Fork();
	~Fork();

	bool TryAcquire();
	void Acquire();
	void Release();
	bool IsAcquired() const;

private:
	std::atomic_bool m_acquired { false };
};

