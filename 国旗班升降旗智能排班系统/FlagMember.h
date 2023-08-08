#pragma once

#include<string>
#include<vector>

using namespace std;

class FlagMember {
public:
	//构造函数
	FlagMember(const string& name, int grade, int height);

	//获取成员姓名
	std::string getName() const;

	//获取成员年级
	int getGrade() const;

	//获取成员身高
	int getHeight() const;

	//设置成员不可用时间
	void setNJunavailableTimes(const vector<int>& njtimes);
	void setEWunavailableTimes(const vector<int>& ewtimes);

	//添加成员不可用时间
	void addNJunavailableTime(int unabletime);
	void addEWunavailableTime(int unabletime);

	//获取成员不可用时间
	vector<int> getNJunavailableTimes() const;
	vector<int> getEWunavailableTimes() const;

	//判断某时间是否为成员的不可用时间
	bool isNJtimeUnavailable(int njtime) const;
	bool isEWtimeUnavailable(int ewtime) const;

	//增加成员已执行任务次数
	void increaseTaskCount();

	//获取成员已执行任务次数
	int getTaskCount() const;

	// 定义比较运算符，比较成员的某个属性（例如姓名或 ID）
	bool operator==(const FlagMember& other) const {
		return this->name == other.name; 
	}

	// 定义不等运算符
	bool operator!=(const FlagMember& other) const {
		return !(*this == other);
	}

private:
	string name;	//成员姓名
	int grade;		//成员年级
	int height;		//成员身高
	vector<int> NJunavailableTimes;	//成员南鉴湖不可用时间
	vector<int> EWunavailableTimes;	//成员东西院不可用时间
	int taskCount = 0;	//已执行任务次数
};