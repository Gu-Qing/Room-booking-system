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

	//���˵�����
	void ShowMenu();

	//�û�ע����¼
	void Logout(Identity*& manager);

	//�������Ա�Ӳ˵�����
	void ManagerMenu(Identity* &identity);

	//����ѧ���Ӳ˵�����
	void StudentMenu(Identity* &student);

	//�����ʦ�Ӳ˵�����
	void TeacherMenu(Identity*& teacher);

	//��¼���� ����1�ǲ����ļ��� ����2�ǲ����������
	void LoginIn(string fileName, int type);

	//�˳�ϵͳ
	void ExitSystem();
};