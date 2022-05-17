#pragma once //防止头文件重复包含
#include <iostream>
using namespace std;

//抽象类，身份基类
class Identity {

protected :
	string m_Name;
	string m_Pwd;

public :
	//操作菜单，纯虚函数
	virtual void OperateMenu() = 0;
};