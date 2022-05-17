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
//��ʼ��������Ϣ
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
	cout << "��������Ϊ��" << this->vComputer.size() << endl;
	ifs.close();
}

//�˵�����
void Student::OperateMenu() {

	cout << endl << "��ӭѧ������ " << this->m_Name << " ��¼��" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                1.����ԤԼ                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                2.�鿴�ҵ�ԤԼ              |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                3.�鿴����ԤԼ              |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                4.ȡ��ԤԼ                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                0.ע����¼                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "����������ѡ�� " << endl;
}

//����ԤԼ
void Student::ApplyOrder() {
	int date = 0; //����
	int interval = 0; //ʱ���
	int room = 0; //�������

	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "- 1.��һ" << endl;
	cout << "- 2.�ܶ�" << endl;
	cout << "- 3.����" << endl;
	cout << "- 4.����" << endl;
	cout << "- 5.����" << endl;

	while (true) {
		cin >> date;
		if (date > 0 && date < 6) {
			break;
		}
		else {
			cout << "�����������������룡" << endl;
		}
	}
	cout << "����������ԤԼʱ��Σ�" << endl;
	cout << "- 1.����" << endl;
	cout << "- 2.����" << endl;
	while (true) {
		cin >> interval;
		if (interval > 0 && interval < 3) {
			break;
		}
		else {
			cout << "�����������������룡" << endl;
		}
	}

	cout << "��ѡ�������" << endl;
	for (vector<ComputerRoom>::iterator it = this->vComputer.begin(); it != this->vComputer.end(); it++) {
		cout << "- " << it->getRoomId() << ".��������Ϊ��" << it->getMaxCapacity() << endl;
	}
	while (true) {
		cin >> room;
		if (room > 0 && room < this->vComputer.size() + 1) {
			break;
		}
		else {
			cout << "�����������������룡" << endl;
		}
	}
	cout << "ԤԼ�ɹ�������У�" << endl;

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
//�鿴����ԤԼ
void Student::ShowMyOrder() {

	OrderFile of;

	if (!of.getSize()) {
		cout << "��ԤԼ��¼��" << endl;
		return;
	}
	for (int i = 0; i < of.getSize(); i++) {
		//.c_str()��ת��Ϊc�����ַ�����Ȼ������atoiתΪint
		if (this->getStudentId() == atoi(of.getOrderData()[i]["stuId"].c_str())) {
			//�ҵ��������ԤԼ
			cout << "ԤԼ���ڣ��� " << of.getOrderData()[i]["date"];
			cout << "\tʱ��Σ�" << (of.getOrderData()[i]["interval"] == "1" ? "����" : "����");
			cout << "\t�����ţ�" << of.getOrderData()[i]["roomId"];
			string status = "\t״̬��";
			//1.�����	2.��ԤԼ	-1.ԤԼʧ��		0.ȡ��ԤԼ
			if (of.getOrderData()[i]["status"] == "1") {
				status += "�����";
			}
			else if (of.getOrderData()[i]["status"] == "2") {
				status += "��ԤԼ";
			}
			else if (of.getOrderData()[i]["status"] == "-1") {
				status += "ԤԼʧ��";
			}
			else {
				status += "ȡ��ԤԼ";
			}
			cout << status << endl;
		}
	}
}
//�鿴����ԤԼ
void Student::ShowAllOrder() {
	OrderFile of;
	if (!of.getSize()) {
		cout << "��ԤԼ��¼��" << endl;
		return;
	}
	for (int i = 0; i < of.getSize(); i++) {
		cout << i + 1 << ". ";
		cout << "ԤԼ���ڣ��� " << of.getOrderData()[i]["date"];
		cout << "\tʱ��Σ�" << (of.getOrderData()[i]["interval"] == "1" ? "����" : "����");
		cout << "\tѧ�ţ�" << of.getOrderData()[i]["stuId"];
		cout << "\t������" << of.getOrderData()[i]["stuName"];
		cout << "\t������ţ�" << of.getOrderData()[i]["roomId"];
		string status = "\t״̬��";
		if (of.getOrderData()[i]["status"] == "1") {
			status += "�����";
		}
		else if (of.getOrderData()[i]["status"] == "2") {
			status += "ԤԼ�ɹ�";
		}
		else if (of.getOrderData()[i]["status"] == "-1") {
			status += "ԤԼʧ��";
		}
		else {
			status += "ȡ��ԤԼ";
		}
		cout << status << endl;
	}
}
//ȡ��ԤԼ
void Student::CancleOrder() {
	OrderFile of;
	if (!of.getSize()) {
		cout << "��ԤԼ��¼��" << endl;
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼��" << endl;
	int index = 0; //������ʾ�û����ǵڼ�����Ϣ
	vector<int> v; //�������ѧ��������к�ԤԼ�ɹ�����Ϣ
	for (int i = 0; i < of.getSize(); i++) {
		//���ж�������ѧ��
		if (this->m_Id == atoi(of.getOrderData()[i]["stuId"].c_str())) {
			//��ɸѡ״̬������л�ԤԼ�ɹ�
			if (of.getOrderData()[i]["status"] == "1" || of.getOrderData()[i]["status"] == "2") {
				v.push_back(i);
				cout << (++index) << ". ";
				cout << "ԤԼ���ڣ��� " << of.getOrderData()[i]["date"];
				cout << "\tʱ��Σ�" << (of.getOrderData()[i]["interal"] == "1" ? "����" : "����");
				cout << "\t������ţ�" << of.getOrderData()[i]["roomId"];
				string status = "\t״̬��";
				if (of.getOrderData()[i]["status"] == "1") {
					status += "�����";
				}
				else if (of.getOrderData()[i]["status"] == "2") {
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}

	cout << "������Ҫȡ���ļ�¼������0���ز˵�" << endl;
	int select = 0;

	while (true) {
		cin >> select;
		if (select > 0 && select <= v.size()) {
			//��Ϊv�Ǵ�0��ʼ��ģ����û��Ǵ�1��ʼѡ�ģ�����Ҫ-1
			of.setOrderDate(v[select - 1],"status", "0");
			of.UpdateOrder();
			cout << "��ȡ��ԤԼ��" << endl;
			break;
		}
		else if (select == 0) {
			break;
		}
		else {
			cout << "�����������������룡" << endl;
		}
	}
}
