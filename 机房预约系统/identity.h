#pragma once //��ֹͷ�ļ��ظ�����
#include <iostream>
using namespace std;

//�����࣬��ݻ���
class Identity {

protected :
	string m_Name;
	string m_Pwd;

public :
	//�����˵������麯��
	virtual void OperateMenu() = 0;
};