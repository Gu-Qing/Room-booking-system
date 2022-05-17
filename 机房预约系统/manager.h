#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

class Manager : public Identity {

private:
	vector<Student> vStudent;
	vector<Teacher> vTeacher;
	vector<ComputerRoom> vComputerRoom;

	//��ʼ��ѧ������
	void InitStudentVector();
	//��ʼ����ʦ����
	void InitTeacherVector();
	//��ʼ����������
	void InitComputerRoomVector();
	//���id�Ƿ��ظ�
	bool CheckRepeat(int id, int type);

public :
	Manager();
	Manager(string name, string pwd);

	string getManagerName() const;
	void setManagerName(string name);
	string getManagerPwd() const;
	void setManagerPwd(string pwd);
	vector<Student> getVectorStu() const;
	void setVectorStu(vector<Student>& stu);
	vector<Teacher> getVectorTeacher() const;
	void setVectorTeacher(vector<Teacher>& teacher);

	virtual void OperateMenu();

	//��ʼ������
	void InitVector();
	//����˺�
	void AddAccount();
	//�鿴�˺�
	void ShowAccount();
	//�鿴������Ϣ
	void ShowComputer();
	//���ԤԼ��¼
	void ClearFile();
};