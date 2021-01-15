#pragma once
//任务基础
enum TaskType
{
	TaskType_None,
	TaskType_Print
};

enum TaskStatus
{
    TaskStatus_Waitting,//等待
    TaskStatus_Running,//正在运行
    TaskStatus_Pauseed,//暂停
    TaskStatus_Completed,//结束
    TaskStatus_Cancel,//取消
};

class ITaskSink
{
	friend class CTask;
public:
	virtual int OnTaskStart(CTask* task, void* wparam, void* lparam) = 0;
	virtual int OnTaskProgress(CTask* task, double bLoaded, double dTotal) = 0;
	virtual int OnTaskFinish(CTask* task, int nRes, void* wparam, void* lparam) = 0;
};

class CTask
{
    friend class CAsyncTask;
public:
    CTask(ITaskSink* sink = nullptr,void* data = nullptr);
    ~CTask();

    int GetTaskId();

    TaskStatus GetTaskStatus();

    TaskType GetTaskType();

	void* GetData();

	int GetProgress();

protected:
    virtual int Run() = 0;

	virtual bool Compare(CTask* task) = 0;

    virtual bool Cancel();

    virtual bool Pause();

    virtual bool IsRun();

    virtual bool IsCancel();

	virtual void SendTaskStart();

	virtual int	 SendResult(int res, void* data = nullptr);

	virtual void SendProgress(int pos);
protected:
	int        m_nProgress;
	int        m_nTaskId;
	ITaskSink* m_pSink;
	TaskStatus m_nStatus;
	TaskType   m_nTaskType;
	void*	   m_pData;
};
