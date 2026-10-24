#include "manager.h"
using namespace std;
manager::manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_did = did;
}
void manager::showInfo()
{
	cout << "职工编号：" << this->m_id << "\t职工姓名：" << this->m_name << "\t职工部门：" << manager::getdepName() << endl;
}
string manager::getdepName()
{
	return string("经理");
}