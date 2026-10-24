#pragma once
#include "worker.h"
class employee : public worker
{
public:
	employee(int id, std::string name, int did);
	virtual void showInfo();
	virtual std::string getdepName();
};