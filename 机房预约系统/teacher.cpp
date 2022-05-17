#include "teacher.h"

Teacher::Teacher() {
	this->m_TeacherId = 0;
	this->m_Name = "";
	this->m_Pwd = "";
}
Teacher::Teacher(int tId, string name, string pwd) {
	this->m_TeacherId = tId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

int Teacher::getTeacherId() const {
	return this->m_TeacherId;
}
void Teacher::setTeacherId(int id) {
	this->m_TeacherId = id;
}
string Teacher::getTeacherName() const {
	return this->m_Name;
}
void Teacher::setTeacherName(string name) {
	this->m_Name = name;
}
string Teacher::getTeacherPwd() const {
	return this->m_Pwd;
}
void Teacher::setTeacherPwd(string pwd) {
	this->m_Pwd = pwd;
}

void Teacher::OperateMenu() {

	cout << endl << "欢迎教师： " << this->m_Name << "\t登录！" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                1.查看预约                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                2.审核预约                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                0.注销登录                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "请输入您的选择： " << endl;
}

//查看所有预约
void Teacher::ShowAllOrder() {
	OrderFile of;
	if (!of.getSize()) {
		cout << "无预约记录！" << endl;
		return;
	}

	for (int i = 0; i < of.getSize(); i++) {
		cout << i + 1 << ". ";
		cout << "预约日期：周 " << of.getOrderData()[i]["date"];
		cout << "\t时间段：" << (of.getOrderData()[i]["interval"] == "1" ? "上午" : "下午");
		cout << "\t学号：" << of.getOrderData()[i]["stuId"];
		cout << "\t姓名：" << of.getOrderData()[i]["stuName"];
		cout << "\t机房编号：" << of.getOrderData()[i]["roomId"];
		string status = "\t状态：";
		if (of.getOrderData()[i]["status"] == "1") {
			status += "审核中";
		}
		else if (of.getOrderData()[i]["status"] == "2") {
			status += "预约成功";
		}
		else if (of.getOrderData()[i]["status"] == "2") {
			status += "预约失败，审核未通过";
		}
		else {
			status += "预约已取消";
		}
		cout << status << endl;
	}
}

//审核所有预约
void Teacher::ValidOrder() {
	OrderFile of;
	if (!of.getSize()) {
		cout << "无预约记录！" << endl;
		return;
	}

	cout << "待审核预约记录如下：" << endl;

	vector<int> v;
	int index = 0;

	for (int i = 0; i < of.getSize(); i++) {
		if (of.getOrderData()[i]["status"] == "1") {
			v.push_back(i);
			cout << ++index << ". ";
			cout << "预约日期：" << of.getOrderData()[i]["date"];
			cout << "\t时间段：" << (of.getOrderData()[i]["interval"] == "1" ? "上午" : "下午");
			cout << "\t学生编号：" << of.getOrderData()[i]["stuId"];
			cout << "\t学生姓名：" << of.getOrderData()[i]["stuName"];
			cout << "\t机房编号：" << of.getOrderData()[i]["roomId"];
			cout << "\t状态：审核中" << endl;
		}
	}

	cout << "请输入审核的预约记录，输入0返回菜单：" << endl;
	int select = 0;

	while (true) {
		cin >> select;
		if (select > 0 && select <= v.size()) {
			cout << "请输入审核结果：" << endl;
			cout << "- 1.通过" << endl;
			cout << "- 2.不通过" << endl;
			int ret;
			cin >> ret;

			if (ret == 1) {
				of.setOrderDate(v[select - 1], "status", "2");
			}
			else {
				of.setOrderDate(v[select - 1], "status", "-1");
			}
			of.UpdateOrder();
			cout << "审核完毕！" << endl;
			break;
		}
		else if (select == 0) {
			break;
		}
		else {
			cout << "输入选择错误，请重新输入！" << endl;
		}
	}
}