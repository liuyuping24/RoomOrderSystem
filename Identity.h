#pragma once
#include <string>
using namespace std;
#include <string>

class Identity {
public:
	
	// �����˵�
	// �����麯����һ��Ҫ�йؼ���virtual �� = 0��
	// ����̳и�����麯�������Բ��ӹؼ��� virtual��
	// ���಻������� = 0����Ϊ������һ��������
	virtual void operMenu() = 0;

	// user name;
	string m_Name;
	// user password
	string m_Pwd;
};
