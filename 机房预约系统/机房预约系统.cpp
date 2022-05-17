#include "systemManager.h"
using namespace std;

int main() {

	SystemManager systemManager;

	while (true) {
		systemManager.ShowMenu();
		int select;
		cin >> select;

		switch (select) {
		case 1: //ѧ��
			systemManager.LoginIn(STUDENT_FILE, 1);
			break;
		case 2: //��ʦ
			systemManager.LoginIn(TEACHER_FILE, 2);
			break;
		case 3: //����Ա
			systemManager.LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //�˳�
			systemManager.ExitSystem();
			break;
		default:
			cout << "��������������ѡ��" << endl;
			break;
		}

		system("pause");
		system("cls");
	}


	return 0;
}