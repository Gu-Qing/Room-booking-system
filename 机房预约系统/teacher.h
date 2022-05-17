#pragma once
#include <iostream>
#include <vector>
#include "identity.h"
#include "orderFile.h"

using namespace std;

class Teacher : public Identity{
private :
	int m_TeacherId;

public :
	Teacher();
	Teacher(int tId, string name, string pwd);
	int getTeacherId() const;
	void setTeacherId(int id);
	string getTeacherName() const;
	void setTeacherName(string name);
	string getTeacherPwd() const;
	void setTeacherPwd(string pwd);

	virtual void OperateMenu();

	//查看所有预约
	void ShowAllOrder();

	//审核所有预约
	void ValidOrder();
};