#ifndef _ADMINISTER_H
#define _ADMINISTER_H
#include"Student.h"
#include<vector>

//助教结构体
struct Assistant {
	char** a;
	int num;
};

//课程结构体
struct Course {
	char CourseID[5];//课程ID
	char CourseName[30];//课程名称
	char Teacher[20];//任课教师姓名
	int MaxContent;//最大容纳人数
	int CurStudent;//当前学生数目
	bool Major;//是否是专业课
	bool Exist;//该课程存在状态（是否被管理员删除）
	Assistant assistant;//所有的助教
	vector<char*> s;//已选课程学生
};



//展示管理员端的主界面
void ShowAdminister();
//注销函数
void Logout();
//把课程信息放入课程数组
void PutinCourseInformation();
//查看全部课程信息
void ScanAllCourseInformation();

void ScanAid();

//添加课程
void AddCourse();
//删除课程
void DeleteCourse();
//修改课程
void ChangeCourse();
//查看特定课程
void ScanSpecificCourse();
//将课程从数组导入到文本
void CurrentCourseintotxt();
//读取当前课程文本
void readcurrent();
//错误时给予提示并返回管理员端主界面
void returnAdminister(const char* word);
//判断某门课在数组中位置
int Match2(char* s);
//在每次登录时，读取每个课程的学生，保证信息一致
void dealstudent();


void tongzhi();

#endif // !_ADMINISTER_H
