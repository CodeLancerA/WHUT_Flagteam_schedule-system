#  WHUT国旗队调度系统1.0
该系统使用C++实现。

**第一作者：唐灏楠**
**联系方式：lancera163@163.com**

##  源代码权限声明
**开源，但使用代码需要署名第一作者**
**欢迎其他其他国旗队使用本代码**


##  设计方法
### 为了解决这个问题，我们可以采用贪心算法进行调度。贪心算法遵循在每一步选择局部最优解的策略，以达到全局最优解的目标。具体步骤如下：

1. 读取成员文件并将成员信息存储在适当的数据结构中，比如使用一个成员类（FlagMember）来存储姓名、年级、身高等信息，并记录他们不可用的任务时间，同时将每个成员的任务计数初始化为0。

2. 预处理成员信息并创建成员集合，并遍历所有成员以设置他们周一到周五分别在南鉴湖和东西院的不可用时间。

3. 从成员集合中筛选出所有身高超过178的成员，创建一个高成员子集。然后，从原始成员集合中移除这个子集。这将使调度过程在东西任务执行时选择一个身高超过178的成员。

4. **贪心算法**
- 东西院调度表制定:当第三个参数为"EW"时
  1.筛选身高超过178的成员：	vector<FlagMember> highMembers;
	for (const auto& member : members) {
		if (member.getHeight() > 178) {
			highMembers.push_back(member);
		}
	}

- 对于每个周一到周五的上午和下午，执行以下三次迭代：
第一次迭代：对于每个周一到周五的上午和下午
1.从highMembers中筛选出符合该时间段的成员，放入一个timeable的向量
2.对该timeable内的成员的执行任务次数进行排序，选择执行任务次数最少的成员插入到该时间段中。

第二次迭代：对于每个周一到周五的上午和下午
1.从members中筛选出符合该时间段的成员，放入一个timeable的向量
2.对该timeable内的成员的执行任务次数进行排序，选择执行任务次数最少的成员插入到该时间段中。

第三次迭代：对于每个周一到周五的上午和下午，
1.从members中筛选出符合该时间段的成员，放入一个timeable的向量
2.该时间段内中已有的两个成员，如果已经有一个大二及以上的队员，则对该timeable内的成员的执行任务次数进行排序，选择执行任务次数最少的成员插入到该时间段中。
                           如果没有，则在timeable里面筛选出所有大二及以上的成员作放入一个elder向量，再从elder向量中选择一个任务次数最少的成员插入该时间段。

- 南鉴湖校区调度表指定：当第三个参数为"NJ"时
与东西校区调度表步骤大致相同，将时间限制改为符合南鉴湖时间条件，但没有身高限制。
- 对于每个周一到周五的上午和下午，执行以下三次迭代：
第二次迭代：对于每个周一到周五的上午和下午
1.从members中筛选出符合该时间段的成员，放入一个timeable的向量
2.对该timeable内的成员的执行任务次数进行排序，选择执行任务次数最少的成员插入到该时间段中。


第二次迭代：对于每个周一到周五的上午和下午
1.从members中筛选出符合该时间段的成员，放入一个timeable的向量
2.对该timeable内的成员的执行任务次数进行排序，选择执行任务次数最少的成员插入到该时间段中。


第三次迭代：对于每个周一到周五的上午和下午，
1.从members中筛选出符合该时间段的成员，放入一个timeable的向量
2.该时间段内中已有的两个成员，如果已经有一个大二及以上的队员，则对该timeable内的成员的执行任务次数进行排序，选择执行任务次数最少的成员插入到该时间段中。
                           如果没有，则在timeable里面筛选出所有大二及以上的成员作放入一个elder向量，再从elder向量中选择一个任务次数最少的成员插入该时间段。

**贪心算法接口**
-接口：greedySchedule()函数
-第一个参数是要排的表，第二个参数是成员容器，第三个是地点


5. 分别输出东西院和南鉴湖最终的调度表，以如下文本形式输出
-----------------------------------------------------
| EW/NJ | 上午  | 上午   | 上午   | 下午   | 下午   | 下午  |
-----------------------------------------------------
|  日期 | 成员1 | 成员2  | 成员3 | 成员1 | 成员2 | 成员3 |
-----------------------------------------------------
|  周一 |  ...  |  ...  |  ...  |  ...  |  ...  |  ...  |
-----------------------------------------------------
|  周二 |  ...  |  ...  |  ...  |  ...  |  ...  |  ...  |
-----------------------------------------------------
|  周三 |  ...  |  ...  |  ...  |  ...  |  ...  |  ...  |
-----------------------------------------------------
|  周四 |  ...  |  ...  |  ...  |  ...  |  ...  |  ...  |
-----------------------------------------------------
|  周五 |  ...  |  ...  |  ...  |  ...  |  ...  |  ...  |
-----------------------------------------------------
其中左上角的ew和nj由本表是东西院还是南鉴湖决定，ew为东西院，nj为南鉴湖

### 数据结构设计：
成员类：包含姓名、年级、身高、南鉴湖和东西院可用时间（分别储存）和任务计数等属性。

### 原成员信息收集+存储设计
-收集：问卷星调查问卷
-解析：.xlsx格式，去掉第一行和前n列，只剩下成员信息
-存储：python程序：成员信息解析.py 解析后以txt格式存在目录文件夹中
**由于中文编码问题解决在本人能力范围之外（C++就这个麻烦）因此名字拼音字母用收集

### 算法步骤：
1. 读取和解析成员文件，创建成员对象，并将它们存储在一个容器中，例如std::vector<Member>。

4. 遍历所有向量中的成员以设置他们的不可用时间
   
5. 筛选身高超过178的成员，创建一个vector<high Members>，并从vector<Member>中删除这些成员。

6. 创建2个调度表分别存储东西院和南鉴湖的升降旗人员名单，使用二维数组或类似的数据结构来存储每天上午和下午的任务分配，例如std::vector<std::vector<FlagMember*>> schedule(daysPerWeek, std::vector<FlagMember*>(timeSlotsPerDay * membersPerTimeSlot, nullptr));，其中5表示5个工作日，2表示每天上午和下午两个时间段，3表示一个时间段内的任务要安排三个人。

7. 实现贪心算法：先排东西院的表，再排南鉴湖的表。

8. 输出调度表，显示每天上午和下午的任务分配情况。


##  开发日志
**7.26**
-完成了调度表的输出函数，类的设计，以及main函数的主框架

**7.27**
-实现了问卷->txt文件的解析程序

**8.6**
-实现了读取文件，保存到本地数据中的功能

**8.7**
-完成贪心算法基础架构

**8.8**
-程序设计完成
-第一次模拟数据程序成功运行。






































#  WHUT national flag team scheduling system 1.0
This system is implemented in C++

##  Source code permission statement
**Only can be viewed or rewrite by Flag team member**

##  Divising approach
###  To address this problem,we can employ the Greedy Algorithm for scheduling. The Greedy ALgorithms follows the strategy of selecting the locally optimal(最优的) solution at each step, aiming to achieve a globally optimal solution. The specific steps are as follows:

1.Read the member file and store the member imformation in a suitable data structure, such as using a member c class(FlagMember) to store the name, grade, height, and other imformations, while also recoding their unavailale time for tasks and initialize the task count of each membver to 0.

2.Preprocess the member information and make set(集合) of members Iterate all the member in the set to set their unvailable times.

3.Filter out all members with a height above 178 from the member set to create a subset of high members. Then, remove this subset from the original member set. This will allow the scheduling process to choose one member with a height above 178 for East-West task execution.

4.**Greedy Algorithm**
For each morning and afternoon from Monday to Friday, perform the following three iterations:
-East-West campus

First Iteration: For each morning and afternoon of the week, assign one high member from the high member subset who meets the time conditions and has the least taskCount.

Second Iteration: For each morning and afternoon of the week, assign one member from the member set who meets the time conditions and has the least taskCount.

Third Iteration:  For each morning and afternoon of the week, assign one member from the member set who meets the time conditions and has the least taskCount.
*Check each time slot for the week, and if there are no members from sophomore year or above available (to be implemented)*

when ends,integrate the high member subset into the member set.

-NanJian Lake
same,but without height limit.

5.Output the resulting schedule.

###  Data Structure Design:
Member Class: Contains attributes such as name, grade, height, available time, and task count.

###  Algorithm approach:
1.  Read and parse the member file, create member objects, and store them in a container, e.g., std::vector<Member>.

2.  Iterated all member to set thier unvailable times.
   
3.  Filter the members over 178 to create a vector<high Members> and delete them in vector<Member> 

4.  Create a schedule, using a two-dimensional array or similar data structure to store the task assignments for each morning and afternoon of each day, e.g., std::vector<std::vector<Member*>> schedule(5, std::vector<Member*>(2, nullptr));, where 5 represents 5 working days, and 2 represents morning and afternoon time slots each day.
   
5.  Implement the Greedy Algorithm.

6.  Output the schedule, showing the task assignments for each morning and afternoon of each day.

##   Devlog
**7.26**
1. create a repository.
2. whole system sturcture design.
3. class declaration and inplement
4. communicate with team（maybe?）




