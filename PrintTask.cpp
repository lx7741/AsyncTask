#include "PrintTask.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include "windows.h"

CPrintTask::CPrintTask()
	:CTask()
{
	m_nTaskType = TaskType_Print;
}

int CPrintTask::Run()
{
	while (i<10)
	{
		Sleep(1000);
		std::cout << "thread_id:" << std::this_thread::get_id() << "    index:" << ++i << std::endl;
	}
	return 0;
}

bool CPrintTask::Compare(CTask* task)
{
	return false;
}
