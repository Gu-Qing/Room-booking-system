#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
using namespace std;

class SystemManager {

public :

	//主菜单界面
	void ShowMenu();

	//用户注销登录
	void Logout(Identity*& manager);

	//进入管理员子菜单界面
	void ManagerMenu(Identity* &identity);

	//进入学生子菜单界面
	void StudentMenu(Identity* &student);

	//进入教师子菜单界面
	void TeacherMenu(Identity*& teacher);

	//登录功能 参数1是操作文件名 参数2是操作身份类型
	void LoginIn(string fileName, int type);

	//退出系统
	void ExitSystem();
};