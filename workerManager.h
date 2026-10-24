#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
const std::string fileName = "file.txt";
class WorkerManager
{
public:
	WorkerManager();
	void ShowMenu();
	int readChoice();
	void exitSystem();
	void addWorker();
	void saveFile();
	int get_num();
	void init_emp();
	void showEmp();
	int isExeist(int id);
	void delEmp();
	void modEmp();
	void findEmp();
	void sortEmp();
	void cleanFile();
	~WorkerManager();
	void release();
	int m_num;
	worker** m_arr;
	bool fileIsEmpyt;
};