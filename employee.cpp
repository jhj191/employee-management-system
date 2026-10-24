#include "employee.h"
using namespace std;
employee::employee(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_did = did;
}
void employee::showInfo()
{
	cout << "职工编号：" << this->m_id << "\t职工姓名：" << this->m_name << "\t职工部门：" << employee::getdepName() << endl;
}
string employee::getdepName()
{
	return string("员工");
}