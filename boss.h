#pragma once
#include "worker.h"
class boss : public worker
{
public:
	boss(int id, std::string name, int did);
	virtual void showInfo();
	virtual std::string getdepName();
};

