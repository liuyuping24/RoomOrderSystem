#pragma once
#include<iostream>
#include"globalFile.h"
#include<string>
#include <map>
#include<fstream>
using namespace std;

class OrderFile {
public:
	//���캯��
	OrderFile();

	//����ԤԼ��¼
	void updateOrder();

	// ��¼ԤԼ��¼
	int m_Size;

	//��¼����ԤԼ��Ϣ�������� key��¼ԤԼ������valueʹ��Ƕ��map������¼��ֵ����Ϣ
	map<int, map<string, string>> m_OrderData;
	
};