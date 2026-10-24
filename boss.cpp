#include "boss.h"
using namespace std;
boss::boss(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_did = did;
}
void boss::showInfo()
{
	cout << "职工编号：" << this->m_id << "\t职工姓名：" << this->m_name << "\t职工部门：" << boss::getdepName() << endl;
}
string boss::getdepName()
{
	return string("老板");
}