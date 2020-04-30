#include<iostream>
using namespace std;
#include"orderFile.h"

string key;
string value;
map<string, string> m;
int pos = 0;
void sub(string& str) {
	pos = str.find(":");
	if (pos != -1) {
		key = str.substr(0, pos);
		// data:1
		value = str.substr(pos + 1, str.size()- pos -1 );
		m.insert(make_pair(key, value));
	}
}

//构造函数
OrderFile::OrderFile() {
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string data;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;
	this->m_Size = 0;

	while (ifs >> data && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status) {
		// 测试代码
		/*cout << data << endl;
		cout << interval << endl;
		cout << stuId << endl;
		cout << stuName << endl;
		cout << roomId << endl;
		cout << status << endl;
		cout << endl;*/

		sub(data);
		sub(interval);
		sub(stuId);
		sub(stuName);
		sub(roomId);
		sub(status);

		//map中的string是按照字母顺序来排列key值的
		this->m_OrderData.insert(make_pair(this->m_Size, m));
		++this->m_Size;
		m.clear();
	}
	ifs.close();
	////test code
	//for (map<int, map<string, string>>::iterator it = m_OrderData.begin(); it != m_OrderData.end(); ++it) {
	//	cout << "条数：" << it->first << " " << "value= " << endl;
	//	for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); ++mit) {
	//		cout << " key = " << mit->first << " " << " value =  " << mit->second << " ";
	//	}
	//	cout << endl;
	//}

}

//更新预约记录
void OrderFile::updateOrder() {
	if (this->m_Size == 0) {
		return;
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; ++i) {
		ofs << "data:" << this->m_OrderData[i]["data"] << " ";
		ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
		ofs << "roomID:" << this->m_OrderData[i]["roomID"] << " ";
		ofs << "status:" << this->m_OrderData[i]["status"] << " ";
		ofs << "stuId:" << this->m_OrderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_OrderData[i]["stuName"] << endl;
	}
	ofs.close();
}