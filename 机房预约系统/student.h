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

	//机房容器
	vector<ComputerRoom> vComputer;

	//初始化机房容器
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


	//菜单界面
	virtual void OperateMenu();

	//申请预约
	void ApplyOrder();
	//查看自身预约
	void ShowMyOrder();
	//查看所有预约
	void ShowAllOrder();
	//取消预约
	void CancleOrder();
};