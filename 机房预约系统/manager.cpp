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
	
	cout << endl << "��ӭ����Ա�� " << this->m_Name << " ��¼��" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                1.����˺�                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                2.�鿴�˺�                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                3.�鿴����                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                4.���ԤԼ                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                0.ע����¼                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "����������ѡ�� " << endl;
}

//��ʼ��ѧ������
void Manager::InitStudentVector() {
	this->vStudent.clear();
	ifstream ifs;
	//��ȡ�ļ��е�ѧ����Ϣ
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
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
	cout << "��ǰ��ѧ������Ϊ��" << this->vStudent.size() << endl;
	ifs.close();
}
//��ʼ����ʦ����
void Manager::InitTeacherVector() {
	this->vTeacher.clear();
	ifstream ifs;
	//��ȡ��ʦ��Ϣ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
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

	cout << "��ǰ��ʦ����Ϊ��" << this->vTeacher.size() << endl;

	ifs.close();
}
//��ʼ����������
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
	cout << "����������Ϊ��" << this->vComputerRoom.size() << endl;
	ifs.close();
}
//���id�Ƿ��ظ�
bool Manager::CheckRepeat(int id, int type) {
	if (type == 1) { //���ѧ��
		for (vector<Student>::iterator it = this->vStudent.begin();  it != this->vStudent.end(); it++) {
			if (id == it->getStudentId()) {
				return true;
			}
		}
	}
	else if (type == 2) { //����ʦ
		for (vector<Teacher>::iterator it = this->vTeacher.begin(); it != this->vTeacher.end(); it++) {
			if (id == it->getTeacherId()) {
				return true;
			}
		}
	}
	else {
		cout << "����ظ����ִ���" << endl;
	}
	return false;
}

//��ʼ������
void Manager::InitVector() {
	this->InitStudentVector();
	this->InitTeacherVector();
	this->InitComputerRoomVector();
}

//����˺�
void Manager::AddAccount() {
	cout << "����������˺ŵ����ͣ�" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.�����ʦ" << endl;

	string fileName; //��ŷ���ļ���
	string tips; //id����ʾ
	string errorTip; //������ʾ

	ofstream ofs;

	int select = 0;
	while (true) {
		cin >> select;

		if (select == 1) {
			//���ѧ��
			fileName = STUDENT_FILE;
			tips = "������ѧ�ţ�";
			errorTip = "ѧ��ѧ���ظ������������룡";
			break;
		}
		else if (select == 2) {
			//��ӽ�ʦ
			fileName = TEACHER_FILE;
			tips = "������ְ���ţ�";
			errorTip = "��ʦְ�����ظ������������룡";
			break;
		}
		else {
			cout << "����ѡ��������������룡" << endl;
		}

	}

	ofs.open(fileName, ios::out | ios::app); //׷�ӵķ�ʽд�ļ�

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
	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl; //���ļ�������ݣ�ÿ�������ÿո�ָ�

	cout << "��ӳɹ���" << endl;

	ofs.close();

	this->InitVector(); //ÿ���������Ա�����»�ȡ�ļ��е�����
}

//��ӡѧ����Ϣ
void PrintStudent(Student &s) {
	cout << "ѧ�ţ�" << s.getStudentId() << "\t������" << s.getStudentName() << "\t���룺" << s.getStudentPwd() << endl;
}
//��ӡ��ʦ��Ϣ
void PrintTeacher(Teacher& t) {
	cout << "��ʦ��" << t.getTeacherId() << "\t������" << t.getTeacherName() << "\t���룺" << t.getTeacherPwd() << endl;
}
//�鿴�˺�
void Manager::ShowAccount() {
	cout << "��ѡ��鿴�����ݣ�" << endl;
	cout << "1.�鿴����ѧ��" << endl;
	cout << "2.�鿴������ʦ" << endl;

	int select = 0;
	while (true) {
		cin >> select;

		if (select == 1) {
			cout << "����ѧ����Ϣ���£�" << endl;
			for_each(this->vStudent.begin(), this->vStudent.end(), PrintStudent);
			break;
		}
		else if (select == 2) {
			cout << "���н�ʦ��Ϣ���£�" << endl;
			for_each(this->vTeacher.begin(), this->vTeacher.end(), PrintTeacher);
			break;
		}
		else {
			cout << "����ѡ��������������룡" << endl;
		}
	}

}
//�鿴������Ϣ
void Manager::ShowComputer() {
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = this->vComputerRoom.begin(); it != this->vComputerRoom.end(); it++) {
		cout << "������ţ�" << it->getRoomId() << "\t�������������" << it->getMaxCapacity()
			<< "�����Ƿ�ԤԼ��" << (it->getRoomIsFree() ? "�����ѱ�ԤԼ" : "����Ϊ����״̬") << endl;
	}
}
//���ԤԼ��¼
void Manager::ClearFile() {

	int select = 0;
	while (true) {
		cout << "����Ҫ���ԤԼ��¼�������Ƿ�ȷ�ϣ�" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2.����" << endl;
		cin >> select;
		if (select == 1) {
			ofstream ofs(ORDER_FILE, ios::trunc);
			ofs.close();
			cout << "��ճɹ���" << endl;
			break;
		}
		else if (select == 2) {
			break;
		}
		else {
			cout << "����������������룡" << endl;
		}
	}
}