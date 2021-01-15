#pragma once
#include "Task.h"
class CPrintTask :public CTask
{
public:
	CPrintTask();
protected:
	virtual int Run() override;

	virtual bool Compare(CTask* task) override;

private:
	int i;
};

