#include "student.h"

Student::Student() {
	this->m_Id = 0;
	this->m_Name = "";
	this->m_Pwd = "";
	this->InitComputerRoom();
}
Student::Student(int id, string name, string pwd) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->InitComputerRoom();
}
int Student::getStudentId() const {
	return this->m_Id;
}
void Student::setStudentId(int id) {
	this->m_Id = id;
}
string Student::getStudentName() const {
	return this->m_Name;
}
void Student::setStudentName(string name) {
	this->m_Name = name;
}
string Student::getStudentPwd() const {
	return this->m_Pwd;
}
void Student::setStudentPwd(string pwd) {
	this->m_Pwd = pwd;
}
vector<ComputerRoom> Student::getComputerRoom() {
	return this->vComputer;
}
void Student::setComputerRoom(vector<ComputerRoom>& v) {
	this->vComputer = v;
}
//初始化机房信息
void Student::InitComputerRoom() {
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	cout << ifs.is_open() << endl;

	ComputerRoom computerRoom;
	int roomId = 0;
	int maxCapacity = 0;
	bool roomIsFree = true;
	while (ifs >> roomId && ifs >> maxCapacity && ifs >> roomIsFree) {
		computerRoom.setRoomId(roomId);
		computerRoom.setMaxCapacity(maxCapacity);
		computerRoom.setRoomIsFree(roomIsFree);
		this->vComputer.push_back(computerRoom);
	}
	cout << "机房数量为：" << this->vComputer.size() << endl;
	ifs.close();
}

//菜单界面
void Student::OperateMenu() {

	cout << endl << "欢迎学生代表： " << this->m_Name << " 登录！" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                1.申请预约                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                2.查看我的预约              |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                3.查看所有预约              |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                4.取消预约                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                0.注销登录                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "请输入您的选择： " << endl;
}

//申请预约
void Student::ApplyOrder() {
	int date = 0; //日期
	int interval = 0; //时间段
	int room = 0; //机房编号

	cout << "机房开放时间为周一到周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "- 1.周一" << endl;
	cout << "- 2.周二" << endl;
	cout << "- 3.周三" << endl;
	cout << "- 4.周四" << endl;
	cout << "- 5.周五" << endl;

	while (true) {
		cin >> date;
		if (date > 0 && date < 6) {
			break;
		}
		else {
			cout << "输入有误，请重新输入！" << endl;
		}
	}
	cout << "请输入申请预约时间段：" << endl;
	cout << "- 1.上午" << endl;
	cout << "- 2.下午" << endl;
	while (true) {
		cin >> interval;
		if (interval > 0 && interval < 3) {
			break;
		}
		else {
			cout << "输入有误，请重新输入！" << endl;
		}
	}

	cout << "请选择机房：" << endl;
	for (vector<ComputerRoom>::iterator it = this->vComputer.begin(); it != this->vComputer.end(); it++) {
		cout << "- " << it->getRoomId() << ".机房容量为：" << it->getMaxCapacity() << endl;
	}
	while (true) {
		cin >> room;
		if (room > 0 && room < this->vComputer.size() + 1) {
			break;
		}
		else {
			cout << "输入有误，请重新输入！" << endl;
		}
	}
	cout << "预约成功！审核中！" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->getStudentId() << " ";
	ofs << "stuName:" << this->getStudentName() << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
}
//查看自身预约
void Student::ShowMyOrder() {

	OrderFile of;

	if (!of.getSize()) {
		cout << "无预约记录！" << endl;
		return;
	}
	for (int i = 0; i < of.getSize(); i++) {
		//.c_str()是转换为c风格的字符串，然后在用atoi转为int
		if (this->getStudentId() == atoi(of.getOrderData()[i]["stuId"].c_str())) {
			//找到了自身的预约
			cout << "预约日期：周 " << of.getOrderData()[i]["date"];
			cout << "\t时间段：" << (of.getOrderData()[i]["interval"] == "1" ? "上午" : "下午");
			cout << "\t机房号：" << of.getOrderData()[i]["roomId"];
			string status = "\t状态：";
			//1.审核中	2.已预约	-1.预约失败		0.取消预约
			if (of.getOrderData()[i]["status"] == "1") {
				status += "审核中";
			}
			else if (of.getOrderData()[i]["status"] == "2") {
				status += "已预约";
			}
			else if (of.getOrderData()[i]["status"] == "-1") {
				status += "预约失败";
			}
			else {
				status += "取消预约";
			}
			cout << status << endl;
		}
	}
}
//查看所有预约
void Student::ShowAllOrder() {
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
		else if (of.getOrderData()[i]["status"] == "-1") {
			status += "预约失败";
		}
		else {
			status += "取消预约";
		}
		cout << status << endl;
	}
}
//取消预约
void Student::CancleOrder() {
	OrderFile of;
	if (!of.getSize()) {
		cout << "无预约记录！" << endl;
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录：" << endl;
	int index = 0; //用于提示用户这是第几条信息
	vector<int> v; //存放自身学号下审核中和预约成功的信息
	for (int i = 0; i < of.getSize(); i++) {
		//先判断是自身学号
		if (this->m_Id == atoi(of.getOrderData()[i]["stuId"].c_str())) {
			//再筛选状态，审核中或预约成功
			if (of.getOrderData()[i]["status"] == "1" || of.getOrderData()[i]["status"] == "2") {
				v.push_back(i);
				cout << (++index) << ". ";
				cout << "预约日期：周 " << of.getOrderData()[i]["date"];
				cout << "\t时间段：" << (of.getOrderData()[i]["interal"] == "1" ? "上午" : "下午");
				cout << "\t机房编号：" << of.getOrderData()[i]["roomId"];
				string status = "\t状态：";
				if (of.getOrderData()[i]["status"] == "1") {
					status += "审核中";
				}
				else if (of.getOrderData()[i]["status"] == "2") {
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入要取消的记录，输入0返回菜单" << endl;
	int select = 0;

	while (true) {
		cin >> select;
		if (select > 0 && select <= v.size()) {
			//因为v是从0开始存的，而用户是从1开始选的，所以要-1
			of.setOrderDate(v[select - 1],"status", "0");
			of.UpdateOrder();
			cout << "已取消预约！" << endl;
			break;
		}
		else if (select == 0) {
			break;
		}
		else {
			cout << "输入有误！请重新输入！" << endl;
		}
	}
}
