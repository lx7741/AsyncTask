#include "Task.h"
#include "AsyncTask.h"
#include "PrintTask.h"




int main()
{
	CPrintTask* task = new CPrintTask();
	CPrintTask* task1 = new CPrintTask();
	CPrintTask* task2 = new CPrintTask();
	CPrintTask* task3 = new CPrintTask();
	CPrintTask* task4 = new CPrintTask();
	CPrintTask* task5 = new CPrintTask();
	CPrintTask* task6 = new CPrintTask();
	CAsyncTask::GetInstance()->PushTask(task,true);
	CAsyncTask::GetInstance()->PushTask(task1,true);
	CAsyncTask::GetInstance()->PushTask(task2,true);
	CAsyncTask::GetInstance()->PushTask(task3,true);
	CAsyncTask::GetInstance()->PushTask(task4, true);
	CAsyncTask::GetInstance()->PushTask(task5, true);
	CAsyncTask::GetInstance()->PushTask(task6, true);
	while (CAsyncTask::GetInstance()->GetTaskSize() > 0)
	{
		Sleep(100);
	}
}