#include "workerManager.h"
using namespace std;
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		this->m_num = 0;
		this->m_arr = nullptr;
		this->fileIsEmpyt = true;
		ifs.close();
		return;
	}
	this->m_num = get_num();
	if (m_num == 0)
	{
		this->m_arr = nullptr;
		this->fileIsEmpyt = true;
		ifs.close();
		return;
	}
	this->fileIsEmpyt = false;
	this->m_arr = new worker * [this->m_num];
	init_emp();
	ifs.close();
}
void WorkerManager::ShowMenu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！  *********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
int WorkerManager::readChoice()
{
	int n = 0;
	bool ok = true;
	while (true)
	{
		system("cls");
		ShowMenu();
		if (ok)
		{
			cout << "请输入您的选项：";
		}
		else
		{
			cout << "输入失败，请再次输入您的选项：";
		}
		if (cin >> n)
		{
			return n;
		}
		if (cin.eof())
		{
			cout << "输入结束，程序退出。" << endl;
			exit(0);
		}
		cin.clear();
		cin.ignore(1024, '\n');
		ok = false;
	}
}
void WorkerManager::exitSystem()
{
	cout << "感谢您的使用！" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::addWorker()
{
	system("cls");
	cout << "请输入您要添加的员工的数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = addNum + this->m_num;
		worker** newSpace = new worker * [newSize];
		if (this->m_arr != nullptr)
		{
			for (int i = 0;i < m_num;++i)
			{
				newSpace[i] = m_arr[i];
			}
		}
		for (int i = 0;i < addNum;++i)
		{
			int id = 0;
			string name;
			int did = 0;
			cout << "请输入第" << i + 1 << "位员工的编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "位员工的姓名：" << endl;
			cin >> name;
			cout << "请输入第" << i + 1 << "位员工的部门编号（1=员工，2=经理，3=老板）：" << endl;
			cin >> did;
			worker* worker0 = nullptr;
			switch (did)
			{
			case 1:
				worker0 = new employee(id, name, did);
				break;
			case 2:
				worker0 = new manager(id, name, did);
				break;
			case 3:
				worker0 = new boss(id, name, did);
				break;
			default:break;
			}
			if (worker0 == nullptr)
			{
				--i;
				cout << "请重现输入有效部门编号！本次不记录。" << endl;
				continue;
			}
			newSpace[this->m_num + i] = worker0;
		}
		delete[] this->m_arr;
		this->m_arr = newSpace;
		this->m_num = newSize;
		fileIsEmpyt = false;
		saveFile();
		cout << "成功添加" << addNum << "名职工！" << endl;
	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
}
void WorkerManager::saveFile()
{
	ofstream ofs;
	ofs.open(fileName, ios::out);
	for (int i = 0;i < m_num;++i)
	{
		if (this->m_arr[i] == nullptr) continue;
		ofs << m_arr[i]->m_id << "   " << m_arr[i]->m_name << "   " << m_arr[i]->m_did << endl;
	}
	ofs.close();
}
int WorkerManager::get_num()
{
	int id = 0;
	string name;
	int did = 0;
	int num = 0;
	ifstream ifs;
	ifs.open(fileName, ios::in);
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		++num;
	}
	ifs.close();
	return num;
}
void WorkerManager::init_emp()
{
	ifstream ifs;
	ifs.open(fileName, ios::in);
	int id = 0;
	string name;
	int did = 0;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker* worker0 = nullptr;
		switch (did)
		{
		case 1:worker0 = new employee(id, name, did);
			break;
		case 2:worker0 = new manager(id, name, did);
			break;
		case 3:worker0 = new boss(id, name, did);
			break;
		default:break;
		}
		this->m_arr[index++] = worker0;
	}
}
void WorkerManager::showEmp()
{
	system("cls");
	if (this->fileIsEmpyt)
	{
		cout << "文件不存在或数据为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_num;++i)
		{
			this->m_arr[i]->showInfo();
		}
	}
	system("pause");
}
int WorkerManager::isExeist(int id)
{
	int index = -1;
	for (int i = 0;i < this->m_num;++i)
	{
		if (id == this->m_arr[i]->m_id)
		{
			index = i;
		}
	}
	return index;
}
void WorkerManager::delEmp()
{
	system("cls");
	if (fileIsEmpyt)
	{
		cout << "文件不存在或数据为空！" << endl;
	}
	else
	{
		cout << "请输入想要删除职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index = isExeist(id);
		if (index != -1)
		{
			delete this->m_arr[index];
			for (int i = index;i < m_num - 1;++i)
			{
				this->m_arr[i] = this->m_arr[i + 1];
			}
			--m_num;
			if (this->m_num == 0)
			{
				this->fileIsEmpyt = true;
			}
			this->m_arr[this->m_num] = nullptr;
			this->saveFile();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "未找到该编号" << endl;
		}
	}
	system("pause");
}
void WorkerManager::modEmp()
{
	system("cls");
	if (fileIsEmpyt)
	{
		cout << "文件不存在或数据为空！" << endl;
	}
	else
	{
		cout << "请输入您要改的员工的编号" << endl;
		int Sid = 0;
		cin >> Sid;
		int temp = isExeist(Sid);
		if (temp != -1)
		{
			delete this->m_arr[temp];
			cout << "找到编号为" << Sid << "的员工" << endl;
		label_1:
			cout << "请输入新的员工编号：" << endl;
			int id = 0;
			string name;
			int did = 0;
			cin >> id;
			cout << "请输入新的名字：" << endl;
			cin >> name;
			cout << "请输入新的职位（1=员工，2=经理，3=老板）：" << endl;
			cin >> did;
			worker* worker0 = nullptr;
			switch (did)
			{
			case 1:
				worker0 = new employee(id, name, did);
				break;
			case 2:
				worker0 = new manager(id, name, did);
				break;
			case 3:
				worker0 = new boss(id, name, did);
				break;
			default:
				break;
			}
			if (worker0 == nullptr)
			{
				cout << "请重现输入有效部门编号！本次不记录。" << endl;
				goto label_1;
			}
			this->m_arr[temp] = worker0;
			this->saveFile();
			cout << "更改完成！" << endl;
		}
		else
		{
			cout << "未找到该编号的员工" << endl;
		}
	}
	system("pause");
}
void WorkerManager::findEmp()
{
	system("cls");
	if (fileIsEmpyt)
	{
		cout << "文件不存在或数据为空！" << endl;
	}
	else
	{
		cout << "请输入您要查找的方式：" << endl << "1=按照编号查找" << endl << "2=按照姓名查找" << endl;
		int uChoice = 0;
		cin >> uChoice;
		if (uChoice == 1)
		{
			cout << "请输入您要查找的编号；" << endl;
			int cId = -1;
			cin >> cId;
			int temp = isExeist(cId);
			if (temp != -1)
			{
				cout << "已找到该编号的员工：" << endl;
				this->m_arr[temp]->showInfo();
			}
			else
			{
				cout << "找不到该员工" << endl;
			}

		}
		else if (uChoice == 2)
		{
			cout << "请输入您要查找的姓名；" << endl;
			string s;
			bool ok = false;
			cin >> s;
			for (int i = 0;i < this->m_num;++i)
			{
				if (s == this->m_arr[i]->m_name)
				{
					cout << "成功查找到编号为" << this->m_arr[i]->m_id << "的员工" << endl;
					this->m_arr[i]->showInfo();
					ok = true;
				}
			}
			if (ok == false)
			{
				cout << "未找到该员工" << endl;
			}

		}
		else
		{
			cout << "输入不是有效值！" << endl;
		}
	}
	system("pause");

}
bool cmpById(worker* a, worker* b)
{
	return a->m_id < b->m_id;
}
bool cmpByIdDesc(worker* a, worker* b)
{
	return a->m_id > b->m_id;
}
void WorkerManager::sortEmp()
{
	system("cls");
	if (fileIsEmpyt)
	{
		cout << "文件不存在或数据为空！" << endl;
	}
	else
	{
		cout << "请输入您要排序的方式：" << endl << "1=升序" << endl << "2=降序" << endl;
		int uChoice = 0;
		cin >> uChoice;
		if (uChoice == 1)
		{
			sort(this->m_arr, this->m_arr + this->m_num, cmpById);
			this->saveFile();
			cout << "升序排序成功！" << endl;
		}
		else if (uChoice == 2)
		{
			sort(this->m_arr, this->m_arr + m_num, cmpByIdDesc);
			this->saveFile();
			cout << "降序排序成功！" << endl;
		}
		else
		{
			cout << "输入不是有效值！" << endl;
		}
	}
	system("pause");
}
void WorkerManager::cleanFile()
{
	system("cls");
	if (fileIsEmpyt)
	{
		cout << "文件不存在或数据为空！" << endl;
	}
	else
	{
		cout << "确认删除？" << endl << "1=确认" << endl << "2=返回" << endl;
		int uChoice = 0;
		cin >> uChoice;
		if (uChoice == 1)
		{
			ofstream ofs(fileName, ios::trunc);
			this->release();
			cout << "删除成功" << endl;
		}
		else if (uChoice == 2)
		{
			cout << "取消删除" << endl;
		}
		else
		{
			cout << "输入不是有效值！" << endl;
		}
	}
	system("pause");
}

WorkerManager::~WorkerManager()
{
	this->release();
}
void WorkerManager::release()
{
	if (m_arr != nullptr)
	{
		for (int i = 0;i < this->m_num;++i)
		{
			delete m_arr[i];
			m_arr[i] = nullptr;
		}
		delete[] m_arr;
		m_arr = nullptr;
		this->fileIsEmpyt = true;
		this->m_num = 0;
	}
}