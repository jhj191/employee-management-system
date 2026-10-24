#include "workerManager.h"
#include <windows.h>
using namespace std;
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	WorkerManager wm;
	while (true)
	{
		int choice = wm.readChoice();
		switch (choice)
		{
		case 0: // 退出
			wm.exitSystem();
			break;
		case 1: // 添加
			wm.addWorker();
			break;
		case 2: // 显示
			wm.showEmp();
			break;
		case 3: // 删除
			wm.delEmp();
			break;
		case 4: // 修改
			wm.modEmp();
			break;
		case 5: // 查找
			wm.findEmp();
			break;
		case 6: // 排序
			wm.sortEmp();
			break;
		case 7: // 清空
			wm.cleanFile();
			break;
		default:
			system("cls");
			break;
		}
	};
	system("pause");
	return 0;
}