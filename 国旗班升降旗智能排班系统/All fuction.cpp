#include<vector>
#include<iostream>
#include"FlagMember.h"
#include<algorithm>
void printSchedule(const std::vector<std::vector<FlagMember*>>& schedule, const std::string& location) {
    std::cout << "| " << location << " | 上午 | 上午 | 上午 | -- | 下午 | 下午 | 下午 |" << std::endl;
    std::cout << "| 日期 | 成员1 | 成员2 | 成员3 | -- | 成员1 | 成员2 | 成员3 |" << std::endl;
    std::string daysOfWeek[5] = { "周一", "周二", "周三", "周四", "周五" };

    for (int i = 0; i < 5; ++i) {
        std::cout << "| " << daysOfWeek[i] << " | ";
        for (int j = 0; j < 6; ++j) {
            if (j == 3) {
                std::cout << " -- | ";
            }

            if (schedule[i][j] != nullptr) {
                std::cout << schedule[i][j]->getName() << " | ";
            }
            else {
                std::cout << " ... | ";
            }
        }
        std::cout << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
    }
}

void greedySchedule(vector<vector<FlagMember*>>& schedule, vector<FlagMember>& members, const string& location)
{
    const int daysPerWeek = 5;
    const int timeSlotsPerDay = 2;
    const int membersPerTimeSlot = 3;

    if (location == "EW") { //东西院调度
        //1.筛选身高超过178的成员
        vector<FlagMember> highMembers;
        for (const auto& member : members) {
            if (member.getHeight() > 180) {
                highMembers.push_back(member);
            }
        }
        //对于每个周一到周五的上午和下午，执行三次迭代
        // 第一次迭代：插入满足条件的高成员
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr;

                // 从高成员中筛选出满足时间条件的成员
                vector<FlagMember*> timeable;
                for (auto& member : highMembers) {
                    if (!member.isEWtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);    //储存成员指针
                    }
                }

                //对时间表中的成员按照任务计数排序
                sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                    return a->getTaskCount() < b->getTaskCount();
                    });


                // 选择任务计数最少的成员插入到时间段中
                if (!timeable.empty()) {
                    selectedMember = timeable[0];
                    schedule[day][timeSlot * membersPerTimeSlot] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addEWunavailableTime((day + 1) * 10 + timeSlot + 1);    //添加不可用时间

                    // 在这里也复制一个新的FlagMember对象，并更新任务计数
                    FlagMember newMember = *selectedMember;
                    // 将新的成员对象插入到members中，替换原来的成员对象
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }


            }
        }
        // 第二次迭代：插入满足条件的普通成员
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr; // 用于存储被选中的成员的指针

                //从成员中筛选出满足时间条件的成员
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isEWtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }
                //对时间表中的成员按照任务计数排序
                sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                    return a->getTaskCount() < b->getTaskCount();
                    });


                // 选择任务计数最少的成员插入到时间段中
                if (!timeable.empty()) {
                    selectedMember = timeable[0];
                    schedule[day][timeSlot * membersPerTimeSlot + 1] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addEWunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // 在这里也复制一个新的FlagMember对象，并更新任务计数
                    FlagMember newMember = *selectedMember;
                    // 将新的成员对象插入到members中，替换原来的成员对象
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }

            }
        }
        // 第三次迭代：插入满足条件的大二及以上成员
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr;

                // 从成员中筛选出满足时间条件的成员，放入timeable向量
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isEWtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }

                // 如果时间段已有两个成员，且已有一个大二及以上的成员
                if (schedule[day][timeSlot * membersPerTimeSlot]->getGrade() >= 2 ||
                    schedule[day][timeSlot * membersPerTimeSlot + 1]->getGrade() >= 2) {
                    // 使用 std::sort 对 timeable 进行排序，按照任务计数升序排序
                    sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                        return a->getTaskCount() < b->getTaskCount();
                        });


                    // 选择任务计数最少的成员插入到时间段中
                    selectedMember = timeable[0];
                }
                else {
                    // 筛选出所有大二及以上的成员，放入elders向量
                    vector<FlagMember*> elders;
                    for (auto& member : timeable) {
                        if (member->getGrade() >= 2) {
                            elders.push_back(member);
                        }
                    }

                    if (!elders.empty()) {
                        // 使用 std::sort 对 elder 进行排序，按照任务计数升序排序
                        sort(elders.begin(), elders.end(), [](const FlagMember* a, const FlagMember* b) {
                            return a->getTaskCount() < b->getTaskCount();
                            });


                        // 选择任务计数最少的大二及以上成员插入到时间段中
                        selectedMember = elders[0];
                    }
                    else if (!timeable.empty()) {
                        // 使用 std::sort 对 timeable 进行排序，按照任务计数升序排序
                        sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                            return a->getTaskCount() < b->getTaskCount();
                            });


                        // 选择任务计数最少的成员插入到时间段中
                        selectedMember = timeable[0];
                    }
                }

                // 插入选定的成员并更新任务计数和不可用时间
                if (selectedMember != nullptr) {    
                    schedule[day][timeSlot * membersPerTimeSlot + 2] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addEWunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // 在这里也复制一个新的FlagMember对象，并更新任务计数
                    FlagMember newMember = *selectedMember;
                    // 将新的成员对象插入到members中，替换原来的成员对象
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }
            }
        }

        // 将 EW 成员的不可用时间添加到 NJ 成员的不可用时间中
        for (FlagMember member : members) {
            vector<int> ewUnavailableTimes = member.getEWunavailableTimes();
            for (auto& othermember : members) {
                if (othermember.getName() == member.getName()) {
                    othermember.addNJunavailableTimes(ewUnavailableTimes);
                }
            }
        }

        printSchedule(schedule, "EW");	//东西院

    }
    else if (location == "NJ") {
        //第一次迭代：
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr; // 用于存储被选中的成员的指针

                //从成员中筛选出满足时间条件的成员
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isNJtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }
                //对时间表中的成员按照任务计数排序
                sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                    return a->getTaskCount() < b->getTaskCount();
                    });


                // 选择任务计数最少的成员插入到时间段中
                if (!timeable.empty()) {
                    selectedMember = timeable[0];
                    schedule[day][timeSlot * membersPerTimeSlot] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addNJunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // 在这里也复制一个新的FlagMember对象，并更新任务计数
                    FlagMember newMember = *selectedMember;
                    // 将新的成员对象插入到members中，替换原来的成员对象
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }

            }
        }
        //第二次迭代：
         // 第二次迭代：插入满足条件的普通成员
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr; // 用于存储被选中的成员的指针

                //从成员中筛选出满足时间条件的成员
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isNJtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }
                //对时间表中的成员按照任务计数排序
                sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                    return a->getTaskCount() < b->getTaskCount();
                    });


                // 选择任务计数最少的成员插入到时间段中
                if (!timeable.empty()) {
                    selectedMember = timeable[0];
                    schedule[day][timeSlot * membersPerTimeSlot + 1] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addNJunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // 在这里也复制一个新的FlagMember对象，并更新任务计数
                    FlagMember newMember = *selectedMember;
                    // 将新的成员对象插入到members中，替换原来的成员对象
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }

            }
        }
        // 第三次迭代：插入满足条件的大二及以上成员
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr;

                // 从成员中筛选出满足时间条件的成员，放入timeable向量
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isNJtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }

                // 如果时间段已有两个成员，且已有一个大二及以上的成员
                if (schedule[day][timeSlot * membersPerTimeSlot]->getGrade() >= 2 ||
                    schedule[day][timeSlot * membersPerTimeSlot + 1]->getGrade() >= 2) {
                    // 使用 std::sort 对 timeable 进行排序，按照任务计数升序排序
                    sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                        return a->getTaskCount() < b->getTaskCount();
                        });


                    // 选择任务计数最少的成员插入到时间段中
                        selectedMember = timeable[0];
                }
                else {
                    // 筛选出所有大二及以上的成员，放入elders向量
                    vector<FlagMember*> elders;
                    for ( auto& member : timeable) {
                        if (member->getGrade() >= 2) {
                            elders.push_back(member);
                        }
                    }

                    if (!elders.empty()) {
                        // 使用 std::sort 对 elder 进行排序，按照任务计数升序排序
                        sort(elders.begin(), elders.end(), [](const FlagMember* a, const FlagMember* b) {
                            return a->getTaskCount() < b->getTaskCount();
                            });


                        // 选择任务计数最少的大二及以上成员插入到时间段中
                        selectedMember = elders[0];
                    }
                    else if (!timeable.empty()) {
                        // 使用 std::sort 对 timeable 进行排序，按照任务计数升序排序
                        sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                            return a->getTaskCount() < b->getTaskCount();
                            });


                        // 选择任务计数最少的成员插入到时间段中
                        selectedMember = timeable[0];
                    }
                }

                // 插入选定的成员并更新任务计数和不可用时间
                if (selectedMember != nullptr) {
                    schedule[day][timeSlot * membersPerTimeSlot + 2] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addNJunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // 在这里也复制一个新的FlagMember对象，并更新任务计数
                    FlagMember newMember = *selectedMember;
                    // 将新的成员对象插入到members中，替换原来的成员对象
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }
            }
        }
        printSchedule(schedule, "NJ");	//南鉴湖
    }


}
