#include "systemManager.h"
using namespace std;

int main() {

	SystemManager systemManager;

	while (true) {
		systemManager.ShowMenu();
		int select;
		cin >> select;

		switch (select) {
		case 1: //学生
			systemManager.LoginIn(STUDENT_FILE, 1);
			break;
		case 2: //教师
			systemManager.LoginIn(TEACHER_FILE, 2);
			break;
		case 3: //管理员
			systemManager.LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //退出
			systemManager.ExitSystem();
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			break;
		}

		system("pause");
		system("cls");
	}


	return 0;
}