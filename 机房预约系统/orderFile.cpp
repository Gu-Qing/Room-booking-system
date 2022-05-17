#include "orderFile.h"

OrderFile::OrderFile() {
	this->m_Size = 0;
	this->InitOrderData();
}

//截取预约状态
void OrderFile::mySplit(string str, map<string, string> &m) {
	int pos = str.find(":"); //4
	if (pos != -1) {
		string key = str.substr(0, pos);
		string value = str.substr(pos + 1, str.size() - pos - 1); //size=9, pos=4, size-pos-1=5-1=4个
		m.insert(make_pair(key, value));
	}
}
//初始化预约信息
void OrderFile::InitOrderData() {
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date; //日期
	string interval; //时间短
	string stuId; //学生编号
	string stuName; //学生姓名
	string roomId; //机房编号
	string status; //状态

	this->m_Size = 0;

	while (ifs >> date && ifs >> interval && ifs >> stuId
		&& ifs >> stuName && ifs >> roomId && ifs >> status) {
		//cout << date << " " << interval << " " << stuId << " " << stuName << " " << roomId << " " << status << endl;

		string key;
		string value;
		map<string, string> m;
		mySplit(date, m);
		mySplit(interval, m);
		mySplit(stuId, m);
		mySplit(stuName, m);
		mySplit(roomId, m);
		mySplit(status, m);

		//将小map容器放入大map容器
		this->m_OrderData.insert(make_pair(this->m_Size, m));
		++this->m_Size;
	}
	ifs.close();

	//for (map<int, map<string, string>>::iterator it = m_OrderData.begin(); it != m_OrderData.end(); it++) {
	//	cout << "条数为： " << it->first << " 值： " << endl;
	//	for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++) {
	//		cout << "key = " << mit->first << " value = " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

int OrderFile::getSize() const {
	return this->m_Size;
}
void OrderFile::setSize(int size) {
	this->m_Size = size;
}
map<int, map<string, string>> OrderFile::getOrderData() const {
	return this->m_OrderData;
}
void OrderFile::setOrderDate(int ind, string str, string value) {
	this->m_OrderData[ind][str] = value;
}

//更新预约记录
void OrderFile::UpdateOrder() {
	if (!this->m_Size) {
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++) {
		ofs << "date:" << this->m_OrderData[i]["date"] << " ";
		ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_OrderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_OrderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_OrderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_OrderData[i]["status"] << endl;
	}
	ofs.close();
}