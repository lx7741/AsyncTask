#include "AsyncTask.h"
#include "Task.h"

std::atomic_int CAsyncTask::m_pSequence = 0;
std::threadpool CAsyncTask::m_pThreadPool;
CAsyncTask::CAsyncTask()
{
	m_pSequence = 0;
	m_pThreadPool.setMaxThread(3);
}


CAsyncTask::~CAsyncTask()
{

}


CAsyncTask * CAsyncTask::GetInstance()
{
	static CAsyncTask instance;
	return &instance;
}

int CAsyncTask::PushTask(CTask* task, bool bStart)
{
	CTask* info = HasTask(task);
    SAutoLock autoLock(m_taskListLock);
    int nTaskId = ++m_pSequence;
    task->m_nTaskId = nTaskId;
    m_lTaskInfos.emplace_back(task);
	if (bStart)
		Start(nTaskId);
    return nTaskId;
}

CTask* CAsyncTask::GetTask(int nTaskId)
{
    for (std::list<CTask*>::iterator iter = m_lTaskInfos.begin(); iter != m_lTaskInfos.end(); iter++)
    {
        CTask* info = *iter;
        if (info && info->GetTaskId() == nTaskId)
        {
            return info;
        }
    }
    return NULL;
}

bool CAsyncTask::Start(int nTaskId)
{
    if (nTaskId == -1)
        return false;
	if (IsRuning(nTaskId))
	{
		return false;
	}
    CTask* task = GetTask(nTaskId);
	m_pThreadPool.commit(Run, this, task);
	return true;
}

bool CAsyncTask::RemoveTask(int nTaskId)
{
	SAutoLock autoLock(m_taskListLock);
	for (std::list<CTask*>::iterator iter = m_lTaskInfos.begin(); iter != m_lTaskInfos.end(); iter++)
	{
		CTask* task = *iter;
		if (task && task->GetTaskId() == nTaskId)
		{
			m_lTaskInfos.erase(iter);
			return true;
		}
	}
	return false;
}

bool CAsyncTask::Cancel(int nTaskId, bool bWait)
{
	SAutoLock autoLock(m_taskListLock);
	for (std::list<CTask*>::iterator iter = m_lTaskInfos.begin(); iter != m_lTaskInfos.end(); iter++)
	{
		CTask* task = *iter;
        if (task && task->GetTaskId() == nTaskId)
        {
            task->Cancel();
			while (bWait)
			{
				Sleep(100);
				if(task->GetTaskStatus() == TaskStatus_Completed)
					break;
			}
            m_lTaskInfos.erase(iter);
	        return true;
        }
	}
	return false;
}

bool CAsyncTask::CancelAll()
{
	SAutoLock autoLock(m_taskListLock);
	for (std::list<CTask*>::iterator iter = m_lTaskInfos.begin(); iter != m_lTaskInfos.end(); iter++)
	{
		CTask* task = *iter;
        if (task)
        {
            task->Cancel();
        }
	}
    m_lTaskInfos.clear();
	return true;
}

int CAsyncTask::GetTaskSize()
{
	return m_lTaskInfos.size();
}

bool CAsyncTask::Run(CAsyncTask* owner, CTask* task)
{
    CAsyncTask* _This = owner;
    if (!task->IsCancel())
    {
        task->m_nStatus = TaskStatus_Running;
        bool res = task->Run();
        task->m_nStatus = TaskStatus_Completed;
    }
    _This->RemoveTask(task->GetTaskId());
    
	return true;
}

bool CAsyncTask::IsRuning(int nTaskId)
{
	SAutoLock autoLock(m_taskListLock);
	for (std::list<CTask*>::iterator it = m_lTaskInfos.begin(); it != m_lTaskInfos.end(); it++)
	{
        CTask* task = *it;
        if (task && task->GetTaskId() == nTaskId)
        {
            bool bRun = task->IsRun();
            return bRun;
        }		
	}
	return false;
}

CTask* CAsyncTask::HasTask(CTask* task)
{
    SAutoLock autoLock(m_taskListLock);
    for (std::list<CTask*>::iterator it = m_lTaskInfos.begin(); it != m_lTaskInfos.end(); it++)
    {
        CTask* info = *it;
        TaskType type = info->GetTaskType();
        if (type == task->GetTaskType())
        {
			bool res = task->Compare(info);
			if (res)
				return info;
        }
    }
    return NULL;
}


const std::list<CTask*> CAsyncTask::GetTasks()
{
	return m_lTaskInfos;
}


