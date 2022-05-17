#include "systemManager.h"


//���˵�����
void SystemManager::ShowMenu() {
	cout << "===================== ��ӭ�������ǲ��ͻ���ԤԼϵͳ =====================" << endl;
	cout << endl << "������������ݣ� " << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                1.ѧ������                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                2.��    ʦ                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                3.�� �� Ա                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                0.��    ��                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "����������ѡ�� " << endl;
}

//�û�ע����¼
void SystemManager::Logout(Identity*& identity) {
	delete identity;
	identity = NULL;
	cout << "�û�ע����¼�ɹ���" << endl;
}

//�������Ա�Ӳ˵�����
void SystemManager::ManagerMenu(Identity* &manager)  { //�����Ǵ���Identityָ������ã��൱��manager�����ı����������Ͳ��ǿ��������ģ������Ч��
	while (true) {
		//���ù���Ա�Ӳ˵�
		manager->OperateMenu();

		//������ָ��תΪ���࣬����������������ӿ�
		Manager* man = (Manager*)manager;

		//�����û���ѡ��
		int select = 0;
		cin >> select;

		switch (select) {
		case 1: //����˺�
			man->AddAccount();
			break;
		case 2: //�鿴�˺�
			man->ShowAccount();
			break;
		case 3: //�鿴����ԤԼ��Ϣ
			man->ShowComputer();
			break;
		case 4: //���ԤԼ
			man->ClearFile();
			break;
		case 0: //ע����¼
			this->Logout(manager);
			return;
			break;
		default:
			cout << "����ѡ��������������룡" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//����ѧ���Ӳ˵�����
void SystemManager::StudentMenu(Identity*& student) {
	while (true) {
		student->OperateMenu();

		Student* stu = (Student*)student;

		int select = 0;
		cin >> select; //�����û���ѡ��

		switch (select) {
		case 1: //����ԤԼ
			stu->ApplyOrder();
			break;
		case 2: //�鿴����ԤԼ
			stu->ShowMyOrder();
			break;
		case 3: //�鿴������ԤԼ
			stu->ShowAllOrder();
			break;
		case 4: //ȡ������ԤԼ
			stu->CancleOrder();
			break;
		case 0: //ע����¼
			this->Logout(student);
			return;
			break;
		default:
			cout << "����ѡ��������������룡" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//�����ʦ�Ӳ˵�����
void SystemManager::TeacherMenu(Identity*& teacher) {
	while (true) {
		teacher->OperateMenu();

		Teacher* t = (Teacher*)teacher;

		int select = 0;
		cin >> select; //�����û���ѡ��

		switch (select) {
		case 1: //�鿴ԤԼ
			t->ShowAllOrder();
			break;
		case 2: //���ԤԼ
			t->ValidOrder();
			break;
		case 0: //ע����¼
			this->Logout(teacher);
			return;
			break;
		default:
			cout << "����ѡ��������������룡" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//��¼���� ����1�ǲ����ļ��� ����2�ǲ����������
void SystemManager::LoginIn(string fileName, int type) {
	//����ָ�룬����ָ���������
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open()) {
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	//�����û���Ϣ
	int id = 0;
	string name, pwd;

	if (type == 1) {
		cout << "����������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "����������ְ���ţ�" << endl;
		cin >> id;
	}
	cout << "�����������û�����" << endl;
	cin >> name;
	cout << "�������������룺" << endl;
	cin >> pwd;


	int fId = 0; //���ļ��ж�ȡ��id��
	string fName; //���ļ��л�ȡ������
	string fPwd; //���ļ��л�ȡ����

	if (type == 1) {
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) { //ÿ�ζ����ʱ�������ո�ͻ���������Ըպÿ������ζ���

			if (fId == id && fName == name && fPwd == pwd) {
				cout << "ѧ����֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);
				//����ѧ����ݵ��Ӳ˵�
				this->StudentMenu(person);

				return;
			}
		}
		cout << "ѧ����֤��¼ʧ�ܣ�" << endl;
	}
	else if (type == 2) {
		//��ʦ�����֤
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) { //ÿ�ζ����ʱ�������ո�ͻ���������Ըպÿ������ζ���

			if (fId == id && fName == name && fPwd == pwd) {
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);
				//�����ʦ��ݵ��Ӳ˵�
				this->TeacherMenu(person);

				return;
			}
		}
		cout << "��ʦ��֤��¼ʧ�ܣ�" << endl;
	}
	else if (type == 3) {
		//����Ա�����֤
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd) {
				cout << "����Ա��¼��֤�ɹ���" << endl;
				system("pause");
				system("cls");

				person = new Manager(name, pwd);
				//�������Ա����Ӳ˵�
				this->ManagerMenu(person);

				return;
			}
		}
		cout << "����Ա��֤��¼ʧ�ܣ�" << endl;
	}
	else {
		cout << "��֤���ʧ�ܣ�" << endl;
	}
}

//�˳�ϵͳ
void SystemManager::ExitSystem() {
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}