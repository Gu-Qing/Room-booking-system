#include "systemManager.h"


//主菜单界面
void SystemManager::ShowMenu() {
	cout << "===================== 欢迎来到传智播客机房预约系统 =====================" << endl;
	cout << endl << "请输入您的身份： " << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                1.学生代表                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                2.教    师                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                3.管 理 员                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                0.退    出                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "请输入您的选择： " << endl;
}

//用户注销登录
void SystemManager::Logout(Identity*& identity) {
	delete identity;
	identity = NULL;
	cout << "用户注销登录成功！" << endl;
}

//进入管理员子菜单界面
void SystemManager::ManagerMenu(Identity* &manager)  { //这里是传入Identity指针的引用，相当于manager是它的别名，这样就不是拷贝过来的，提高了效率
	while (true) {
		//调用管理员子菜单
		manager->OperateMenu();

		//将父类指针转为子类，调用子类离的其他接口
		Manager* man = (Manager*)manager;

		//接受用户的选择
		int select = 0;
		cin >> select;

		switch (select) {
		case 1: //添加账号
			man->AddAccount();
			break;
		case 2: //查看账号
			man->ShowAccount();
			break;
		case 3: //查看机房预约信息
			man->ShowComputer();
			break;
		case 4: //清空预约
			man->ClearFile();
			break;
		case 0: //注销登录
			this->Logout(manager);
			return;
			break;
		default:
			cout << "输入选项错误，请重新输入！" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//进入学生子菜单界面
void SystemManager::StudentMenu(Identity*& student) {
	while (true) {
		student->OperateMenu();

		Student* stu = (Student*)student;

		int select = 0;
		cin >> select; //接收用户的选择

		switch (select) {
		case 1: //申请预约
			stu->ApplyOrder();
			break;
		case 2: //查看自身预约
			stu->ShowMyOrder();
			break;
		case 3: //查看所有人预约
			stu->ShowAllOrder();
			break;
		case 4: //取消自身预约
			stu->CancleOrder();
			break;
		case 0: //注销登录
			this->Logout(student);
			return;
			break;
		default:
			cout << "输入选择错误，请重新输入！" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//进入教师子菜单界面
void SystemManager::TeacherMenu(Identity*& teacher) {
	while (true) {
		teacher->OperateMenu();

		Teacher* t = (Teacher*)teacher;

		int select = 0;
		cin >> select; //接收用户的选择

		switch (select) {
		case 1: //查看预约
			t->ShowAllOrder();
			break;
		case 2: //审核预约
			t->ValidOrder();
			break;
		case 0: //注销登录
			this->Logout(teacher);
			return;
			break;
		default:
			cout << "输入选择错误，请重新输入！" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

//登录功能 参数1是操作文件名 参数2是操作身份类型
void SystemManager::LoginIn(string fileName, int type) {
	//父类指针，用于指向子类对象
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open()) {
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	//接受用户信息
	int id = 0;
	string name, pwd;

	if (type == 1) {
		cout << "请输入您的学号：" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "请输入您的职工号：" << endl;
		cin >> id;
	}
	cout << "请输入您的用户名：" << endl;
	cin >> name;
	cout << "请输入您的密码：" << endl;
	cin >> pwd;


	int fId = 0; //从文件中读取的id号
	string fName; //从文件中获取的姓名
	string fPwd; //从文件中获取密码

	if (type == 1) {
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) { //每次读入的时候碰到空格就会结束，所以刚好可以依次读入

			if (fId == id && fName == name && fPwd == pwd) {
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");

				person = new Student(id, name, pwd);
				//进入学生身份的子菜单
				this->StudentMenu(person);

				return;
			}
		}
		cout << "学生验证登录失败！" << endl;
	}
	else if (type == 2) {
		//教师身份验证
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) { //每次读入的时候碰到空格就会结束，所以刚好可以依次读入

			if (fId == id && fName == name && fPwd == pwd) {
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");

				person = new Teacher(id, name, pwd);
				//进入教师身份的子菜单
				this->TeacherMenu(person);

				return;
			}
		}
		cout << "教师验证登录失败！" << endl;
	}
	else if (type == 3) {
		//管理员身份验证
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd) {
				cout << "管理员登录验证成功！" << endl;
				system("pause");
				system("cls");

				person = new Manager(name, pwd);
				//进入管理员身份子菜单
				this->ManagerMenu(person);

				return;
			}
		}
		cout << "管理员验证登录失败！" << endl;
	}
	else {
		cout << "验证身份失败！" << endl;
	}
}

//退出系统
void SystemManager::ExitSystem() {
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}