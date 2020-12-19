#ifndef _STUDENT_H
#define _STUDENT_H


#include<iostream>
#include"Administer.h"

using namespace std;
//我的课程结构体，利用该结构体数组存储我的课程
struct MyCourses {
	char id[5];
	char AssistantName[30];
};


//把学生个人信息录入个人信息数组
void WriteStudent(char* studentID);
//1.注册函数 2.注册成功后处理数据函数 3.创建个人文件函数
void RegisterStudent();
void SucceedRegisterStudent(char* UserName,char* Password);
void Createfile(char* fname);
//学生端主界面函数
void ShowStudent();
//查看全部课程函数
void ScanCourse();
//选课函数
void SelectCourse();
//查看我的课程函数
void ScanMyCourse();
//退课函数
void QuitCourse();
//取消助教身份
void Dealquitassistant(int index);
//报名助教函数
void BeAssistant();
//同管理员端Match2
int Match(char* s);
//读入助教信息函数
void readinassistant();
//将助教信息写入文本函数
void writeassistant();
//挑选助教函数
void SelectAssistant();
//将个人信息写入个人文本函数
void WritePersonal();
//删除自己对应课程函数
void DeletePersonal(int i);
//判断选课是否符合要求
void IsEnough();
//展示单个课程
void ShowCourse(int i);
//判断自己是否在某课程中
int BeinCourse(char* courseID);
//遇到错误给予提示并返回学生端主界面
void returnStudent(const char* word);
//检查助教是否退课
void checkassistant();
//检查某门课是否有助教
bool checkhave(int i);

void changepwd();

void ScanAids();
void ScanAidd();


#endif // !_STUDENT_H