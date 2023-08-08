#pragma once
#include<vector>
#include<iostream>
#include"FlagMember.h"

//输出调度表函数
void printSchedule(const std::vector<std::vector<FlagMember*>>& schedule, const std::string& location);

//贪心算法
void greedySchedule(vector<vector<FlagMember*>>& schedule, vector<FlagMember>& members, const string& location);