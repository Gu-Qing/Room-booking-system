#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "globalFile.h"

using namespace std;

class OrderFile {
private:

	//记录预约条数
	int m_Size;
	//记录所有预约信息的容器 第一个int是预约信息的条数，第二个map中的两个string，key代表属性，value是实值
	map<int, map<string, string>> m_OrderData;


	void mySplit(string str, map<string, string> &m);
	//初始化预约信息
	void InitOrderData();

public :

	OrderFile();
	int getSize() const;
	void setSize(int size);
	map<int, map<string, string>> getOrderData() const;
	void setOrderDate(int ind, string str, string value);

	//更新预约记录
	void UpdateOrder();

};