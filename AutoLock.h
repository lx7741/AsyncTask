#pragma once
#include "windows.h"
class SCriticalSection
{
public:
	SCriticalSection();
	virtual ~SCriticalSection();

	void Enter();
	void Leave();
protected:
	CRITICAL_SECTION    m_cs;
};

class SAutoLock
{
public:
	SAutoLock(SCriticalSection & cs) :m_cs(cs)
	{
		m_cs.Enter();
	}

	~SAutoLock()
	{
		m_cs.Leave();
	}
protected:
	SCriticalSection & m_cs;
};