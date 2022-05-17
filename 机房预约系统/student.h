#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "identity.h"
#include "computerRoom.h"
#include "globalFile.h"
#include "orderFile.h"

using namespace std;

class Student : public Identity{
private:
	int m_Id;

	//��������
	vector<ComputerRoom> vComputer;

	//��ʼ����������
	void InitComputerRoom();

public :

	Student();
	Student(int id, string name, string pwd);

	int getStudentId() const;
	void setStudentId(int id);
	string getStudentName() const;
	void setStudentName(string name);
	string getStudentPwd() const;
	void setStudentPwd(string pwd);
	vector<ComputerRoom> getComputerRoom();
	void setComputerRoom(vector<ComputerRoom> &v);


	//�˵�����
	virtual void OperateMenu();

	//����ԤԼ
	void ApplyOrder();
	//�鿴����ԤԼ
	void ShowMyOrder();
	//�鿴����ԤԼ
	void ShowAllOrder();
	//ȡ��ԤԼ
	void CancleOrder();
};