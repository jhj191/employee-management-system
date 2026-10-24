#pragma once
#include "worker.h"
class manager : public worker
{
public:
	manager(int id, std::string name, int did);
	virtual void showInfo();
	virtual std::string getdepName();
};
