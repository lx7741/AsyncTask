#include "Task.h"

CTask::CTask(ITaskSink* sink, void* data)
{
    m_nTaskType   = TaskType_None;
    m_nStatus     = TaskStatus_Waitting;
    m_nTaskId     = -1;
	m_pSink       = sink;
	m_pData       = data;
	m_nProgress   = 0;
}


CTask::~CTask()
{

}

int CTask::GetTaskId()
{
    return m_nTaskId;
}

TaskStatus CTask::GetTaskStatus()
{
    return m_nStatus;
}

TaskType CTask::GetTaskType()
{
    return m_nTaskType;
}

void* CTask::GetData()
{
	return m_pData;
}

int CTask::GetProgress()
{
	return m_nProgress;
}

bool CTask::Cancel()
{
    m_nStatus = TaskStatus_Cancel;
    return true;
}

bool CTask::Pause()
{
	m_nStatus = TaskStatus_Pauseed;
	return true;
}

bool CTask::IsRun()
{
	return m_nStatus == TaskStatus_Running;
}

bool CTask::IsCancel()
{
	return m_nStatus == TaskStatus_Cancel;
}

void CTask::SendTaskStart()
{
	if (m_pSink)
	{
		m_pSink->OnTaskStart(this, m_pData, nullptr);
	}
}

int CTask::SendResult(int res, void * data)
{
	if (m_pSink)
	{
		m_pSink->OnTaskFinish(this, res, m_pData, data);
	}
	return 1;
}

void CTask::SendProgress(int pos)
{
	m_nProgress = pos;
	if (m_pSink)
	{
		m_pSink->OnTaskProgress(this, pos, 100);
	}
}
