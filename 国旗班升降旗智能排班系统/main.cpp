#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "FlagMember.h"
#include <vector>
#include "All fuction.h"
#include <io.h>
#include <fcntl.h>

using namespace std;


int main() {
	// 1.读取和解析成员文件，创建成员对象，并将它们存储在一个容器中
	vector<FlagMember> members;	//二维容器，储存成员信息
	ifstream inFile("成员时间.txt",ios::in,ios::binary);	//创建输入流打开文件
	if (!inFile) {
		cerr << "无法打开文件" << endl;
		return 1;
	}
	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);	//字符串流创建
		string name, temp;		//准备变量来储存解析后的数据
		int grade, height;
		vector<int> njTimes, ewTimes;
		ss >> name >> grade >> height;	//使用字符串流解析姓名，年级和身高
		while (ss >> temp) {
			if (temp.find("ew") != string::npos) {
				try {
					int time = stoi(temp.substr(0, temp.size() - 2));
					ewTimes.push_back(time);
				}
				catch (const std::invalid_argument& e) {
					cerr << "错误的时间格式：" << temp << endl;
					// 可以选择继续处理其他时间，或者直接返回错误
				}
			}
			else if (temp.find("nj") != string::npos) {
				try {
					int time = stoi(temp.substr(0, temp.size() - 2));
					njTimes.push_back(time);
				}
				catch (const std::invalid_argument& e) {
					cerr << "错误的时间格式：" << temp << endl;
					// 可以选择继续处理其他时间，或者直接返回错误
				}
			}
		}

		//创建成员对象,设置不可用时间,并添加到容器中
		FlagMember member(name, grade, height);
		member.setEWunavailableTimes(ewTimes);
		member.setNJunavailableTimes(njTimes);
		members.push_back(member);
	}

	//2.输出队员信息
	for (const auto& member : members) {
		cout << "姓名：" << member.getName() << endl;
		cout << "年级：" << member.getGrade() << endl;
		cout << "身高：" << member.getHeight() << endl;

		cout << "不可用时间（南鉴湖）：";
		for (int time : member.getNJunavailableTimes()) {
			cout << time << " ";
		}
		cout << endl;

		cout << "不可用时间（东西院）：";
		for (int time : member.getEWunavailableTimes()) {
			cout << time << " ";
		}
		cout << endl;

		cout << "已执行任务次数：" << member.getTaskCount() << endl;
		cout << "=============================" << endl;
	}
	

	//3.创建调度表
	const int daysPerWeek = 5;
	const int timeSlotsPerDay = 2;
	const  int membersPerTimeSolt = 3;
	vector<vector<FlagMember*>> ewSchedule(daysPerWeek, vector<FlagMember*>(timeSlotsPerDay * membersPerTimeSolt, nullptr));	//东西院调度表初始化
	vector<vector<FlagMember*>> njSchedule(daysPerWeek, vector<FlagMember*>(timeSlotsPerDay * membersPerTimeSolt, nullptr));	//南鉴湖调度表初始化

	// 4.贪心算法实现，先排东西院，再排南鉴湖
	greedySchedule(ewSchedule,members, "EW");    // 东西院调度

	//东西院排完后合并highMembers和members后再排南鉴湖
	greedySchedule(njSchedule, members, "NJ");    // 南鉴湖调度


	return 0;
}
