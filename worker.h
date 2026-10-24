#pragma once
#include <iostream>
class worker
{
public:
	virtual void showInfo() = 0;
	virtual std::string getdepName() = 0;
	int m_id;
	std::string m_name;
	int m_did;
	virtual ~worker() {}
};
