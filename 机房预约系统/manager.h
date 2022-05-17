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

	//初始化学生容器
	void InitStudentVector();
	//初始化教师容器
	void InitTeacherVector();
	//初始化机房容器
	void InitComputerRoomVector();
	//检查id是否重复
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

	//初始化容器
	void InitVector();
	//添加账号
	void AddAccount();
	//查看账号
	void ShowAccount();
	//查看机房信息
	void ShowComputer();
	//清空预约记录
	void ClearFile();
};