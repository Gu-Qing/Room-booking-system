#include "manager.h"

Manager::Manager() {
	this->m_Name = "";
	this->m_Pwd = "";
	this->InitVector();
}
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->InitVector();
}

string Manager::getManagerName() const {
	return  this->m_Name;
}
void Manager::setManagerName(string name) {
	this->m_Name = name;
}
string Manager::getManagerPwd() const {
	return this->m_Pwd;
}
void Manager::setManagerPwd(string pwd) {
	this->m_Pwd = pwd;
}
vector<Student> Manager::getVectorStu() const {
	return this->vStudent;
}
void Manager::setVectorStu(vector<Student>& stu){
	this->vStudent = stu;
}
vector<Teacher> Manager::getVectorTeacher() const {
	return this->vTeacher;
}
void Manager::setVectorTeacher(vector<Teacher>& teacher) {
	this->vTeacher = teacher;
}

void Manager::OperateMenu() {
	
	cout << endl << "欢迎管理员： " << this->m_Name << " 登录！" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                1.添加账号                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                2.查看账号                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                3.查看机房                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                4.清空预约                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                0.注销登录                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "请输入您的选择： " << endl;
}

//初始化学生容器
void Manager::InitStudentVector() {
	this->vStudent.clear();
	ifstream ifs;
	//读取文件中的学生信息
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "读取文件失败！" << endl;
		return;
	}
	Student s;
	int id = 0;
	string name = "", pwd = "";
	while (ifs >> id && ifs >> name && ifs >> pwd) {
		s.setStudentId(id);
		s.setStudentName(name);
		s.setStudentPwd(pwd);
		this->vStudent.push_back(s);
	}
	cout << "当前的学生数量为：" << this->vStudent.size() << endl;
	ifs.close();
}
//初始化教师容器
void Manager::InitTeacherVector() {
	this->vTeacher.clear();
	ifstream ifs;
	//读取教师信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "读取文件失败！" << endl;
		return;
	}

	Teacher t;
	int id = 0;
	string name = "", pwd = "";
	while (ifs >> id && ifs >> name && ifs >> pwd) {
		t.setTeacherId(id);
		t.setTeacherName(name);
		t.setTeacherPwd(pwd);
		this->vTeacher.push_back(t);
	}

	cout << "当前教师数量为：" << this->vTeacher.size() << endl;

	ifs.close();
}
//初始化机房容器
void Manager::InitComputerRoomVector() {
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom computerRoom;
	int roomId = 0;
	int maxCapacity = 0;
	bool roomIsFree = true;
	while (ifs >> roomId && ifs >> maxCapacity && ifs >> roomIsFree) {
		computerRoom.setRoomId(roomId);
		computerRoom.setMaxCapacity(maxCapacity);
		computerRoom.setRoomIsFree(roomIsFree);
		this->vComputerRoom.push_back(computerRoom);
	}
	cout << "机房的数量为：" << this->vComputerRoom.size() << endl;
	ifs.close();
}
//检查id是否重复
bool Manager::CheckRepeat(int id, int type) {
	if (type == 1) { //检测学生
		for (vector<Student>::iterator it = this->vStudent.begin();  it != this->vStudent.end(); it++) {
			if (id == it->getStudentId()) {
				return true;
			}
		}
	}
	else if (type == 2) { //检测教师
		for (vector<Teacher>::iterator it = this->vTeacher.begin(); it != this->vTeacher.end(); it++) {
			if (id == it->getTeacherId()) {
				return true;
			}
		}
	}
	else {
		cout << "检测重复出现错误！" << endl;
	}
	return false;
}

//初始化容器
void Manager::InitVector() {
	this->InitStudentVector();
	this->InitTeacherVector();
	this->InitComputerRoomVector();
}

//添加账号
void Manager::AddAccount() {
	cout << "请输入添加账号的类型：" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;

	string fileName; //擦欧总文件名
	string tips; //id号提示
	string errorTip; //错误提示

	ofstream ofs;

	int select = 0;
	while (true) {
		cin >> select;

		if (select == 1) {
			//添加学生
			fileName = STUDENT_FILE;
			tips = "请输入学号：";
			errorTip = "学生学号重复，请重新输入！";
			break;
		}
		else if (select == 2) {
			//添加教师
			fileName = TEACHER_FILE;
			tips = "请输入职工号：";
			errorTip = "教师职工号重复，请重新输入！";
			break;
		}
		else {
			cout << "输入选择错误，请重新输入！" << endl;
		}

	}

	ofs.open(fileName, ios::out | ios::app); //追加的方式写文件

	int id;
	string name;
	string pwd;

	while (true) {
		cout << tips << endl;
		cin >> id;
		bool flag = this->CheckRepeat(id, select);
		if (flag) {
			cout << errorTip << endl;
		}
		else {
			break;
		}
	}
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl; //向文件添加数据，每个数据用空格分割

	cout << "添加成功！" << endl;

	ofs.close();

	this->InitVector(); //每次添加完人员后，重新获取文件中的数据
}

//打印学生信息
void PrintStudent(Student &s) {
	cout << "学号：" << s.getStudentId() << "\t姓名：" << s.getStudentName() << "\t密码：" << s.getStudentPwd() << endl;
}
//打印教师信息
void PrintTeacher(Teacher& t) {
	cout << "教师：" << t.getTeacherId() << "\t姓名：" << t.getTeacherName() << "\t密码：" << t.getTeacherPwd() << endl;
}
//查看账号
void Manager::ShowAccount() {
	cout << "请选择查看的内容：" << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有老师" << endl;

	int select = 0;
	while (true) {
		cin >> select;

		if (select == 1) {
			cout << "所有学生信息如下：" << endl;
			for_each(this->vStudent.begin(), this->vStudent.end(), PrintStudent);
			break;
		}
		else if (select == 2) {
			cout << "所有教师信息如下：" << endl;
			for_each(this->vTeacher.begin(), this->vTeacher.end(), PrintTeacher);
			break;
		}
		else {
			cout << "输入选择错误！请重新输入！" << endl;
		}
	}

}
//查看机房信息
void Manager::ShowComputer() {
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = this->vComputerRoom.begin(); it != this->vComputerRoom.end(); it++) {
		cout << "机房编号：" << it->getRoomId() << "\t机房最大容量：" << it->getMaxCapacity()
			<< "机房是否被预约：" << (it->getRoomIsFree() ? "机房已被预约" : "机房为空闲状态") << endl;
	}
}
//清空预约记录
void Manager::ClearFile() {

	int select = 0;
	while (true) {
		cout << "您将要清空预约记录，请问是否确认？" << endl;
		cout << "1.确认" << endl;
		cout << "2.返回" << endl;
		cin >> select;
		if (select == 1) {
			ofstream ofs(ORDER_FILE, ios::trunc);
			ofs.close();
			cout << "清空成功！" << endl;
			break;
		}
		else if (select == 2) {
			break;
		}
		else {
			cout << "输入错误！请重新输入！" << endl;
		}
	}
}