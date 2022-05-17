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

	cout << endl << "��ӭ��ʦ�� " << this->m_Name << "\t��¼��" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                1.�鿴ԤԼ                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                2.���ԤԼ                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t|                0.ע����¼                  |" << endl;
	cout << "\t\t|                                            |" << endl;
	cout << "\t\t -------------------------------------------- " << endl;
	cout << "����������ѡ�� " << endl;
}

//�鿴����ԤԼ
void Teacher::ShowAllOrder() {
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
		else if (of.getOrderData()[i]["status"] == "2") {
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else {
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
}

//�������ԤԼ
void Teacher::ValidOrder() {
	OrderFile of;
	if (!of.getSize()) {
		cout << "��ԤԼ��¼��" << endl;
		return;
	}

	cout << "�����ԤԼ��¼���£�" << endl;

	vector<int> v;
	int index = 0;

	for (int i = 0; i < of.getSize(); i++) {
		if (of.getOrderData()[i]["status"] == "1") {
			v.push_back(i);
			cout << ++index << ". ";
			cout << "ԤԼ���ڣ�" << of.getOrderData()[i]["date"];
			cout << "\tʱ��Σ�" << (of.getOrderData()[i]["interval"] == "1" ? "����" : "����");
			cout << "\tѧ����ţ�" << of.getOrderData()[i]["stuId"];
			cout << "\tѧ��������" << of.getOrderData()[i]["stuName"];
			cout << "\t������ţ�" << of.getOrderData()[i]["roomId"];
			cout << "\t״̬�������" << endl;
		}
	}

	cout << "��������˵�ԤԼ��¼������0���ز˵���" << endl;
	int select = 0;

	while (true) {
		cin >> select;
		if (select > 0 && select <= v.size()) {
			cout << "��������˽����" << endl;
			cout << "- 1.ͨ��" << endl;
			cout << "- 2.��ͨ��" << endl;
			int ret;
			cin >> ret;

			if (ret == 1) {
				of.setOrderDate(v[select - 1], "status", "2");
			}
			else {
				of.setOrderDate(v[select - 1], "status", "-1");
			}
			of.UpdateOrder();
			cout << "�����ϣ�" << endl;
			break;
		}
		else if (select == 0) {
			break;
		}
		else {
			cout << "����ѡ��������������룡" << endl;
		}
	}
}