#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "globalFile.h"

using namespace std;

class OrderFile {
private:

	//��¼ԤԼ����
	int m_Size;
	//��¼����ԤԼ��Ϣ������ ��һ��int��ԤԼ��Ϣ���������ڶ���map�е�����string��key�������ԣ�value��ʵֵ
	map<int, map<string, string>> m_OrderData;


	void mySplit(string str, map<string, string> &m);
	//��ʼ��ԤԼ��Ϣ
	void InitOrderData();

public :

	OrderFile();
	int getSize() const;
	void setSize(int size);
	map<int, map<string, string>> getOrderData() const;
	void setOrderDate(int ind, string str, string value);

	//����ԤԼ��¼
	void UpdateOrder();

};