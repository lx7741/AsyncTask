#pragma once
#include <list>
#include "Task.h"
#include "threadpool.h"
#include "AutoLock.h"


class CAsyncTask
{
private:
	CAsyncTask();
	~CAsyncTask();
public:
	static CAsyncTask * GetInstance();

    int PushTask(CTask* task,bool bStart = false);

    CTask* GetTask(int nTaskId);

	bool Start(int nTaskId);

	bool RemoveTask(int nTaskId);

	bool Cancel(int nTaskId,bool bWait = false);

	bool CancelAll();

	int  GetTaskSize();

    bool IsRuning(int nTaskId);

    CTask* HasTask(CTask* task);

	const std::list<CTask*> GetTasks();

protected:
	static bool Run(CAsyncTask* owner,CTask* task);

private:
	mutable SCriticalSection      m_taskListLock;
	static std::atomic_int        m_pSequence;
	static std::threadpool	      m_pThreadPool;//OCRÏß³Ì
	std::list<CTask*>             m_lTaskInfos;

};
