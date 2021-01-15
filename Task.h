#pragma once
//�������
enum TaskType
{
	TaskType_None,
	TaskType_Print
};

enum TaskStatus
{
    TaskStatus_Waitting,//�ȴ�
    TaskStatus_Running,//��������
    TaskStatus_Pauseed,//��ͣ
    TaskStatus_Completed,//����
    TaskStatus_Cancel,//ȡ��
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
