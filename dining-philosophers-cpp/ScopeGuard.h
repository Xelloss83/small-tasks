#pragma once

template<typename Lambda>
class ScopeGuard
{
public:
	explicit ScopeGuard(const Lambda& op) : m_op(op) {}
	~ScopeGuard() { if (!m_dismissed) Finalize(); }

	void Dismiss() { m_dismissed = true; }

private:
	void Finalize()
	{
		Dismiss();
		m_op();
	}

	Lambda m_op;
	bool m_dismissed = false;
};

template<typename Lambda>
ScopeGuard<Lambda> MakeScopeGuard(const Lambda& op)
{
	return ScopeGuard<Lambda>(op);
}