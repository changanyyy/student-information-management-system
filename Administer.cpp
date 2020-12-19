#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include"Administer.h"
#include"MainWindow.h"
#include"Student.h"

using namespace std;

//全部课程数组（当前课程）
extern Course courStudent[30];
extern int CourseCountStudent;
extern int studentnum;

extern student Stu[20];

void ShowAdminister() {
	cout << "=======================================================================================================\n\n";
	cout << "1.注销登录 2.录入课程信息 3.查看全部课程信息 4.增加课程 5.删除课程 6.修改课程 7.查看具体课程 8.发布通知\n";
	cout << "=======================================================================================================\n\n";
	cout << "请选择需要的功能：";
	char function;
	cin >> function;
	switch (function) {
	case '1': Logout(); break;
	case '2': PutinCourseInformation(); break;
	case '3': ScanAllCourseInformation(); break;
	case '4': AddCourse(); break;
	case '5': DeleteCourse(); break;
	case '6': ChangeCourse(); break;
	case '7': ScanSpecificCourse(); break;
	case '8': tongzhi(); break;
	default:cout << "抱歉无此操作，请重新选择"; Sleep(2000); system("cls"); ShowAdminister(); break;
	}
	return;
}

//注销函数
void Logout() {
	system("cls");
	cout << "============================================================================================\n\n";
	cout << "                                     请稍等，正在注销			   							\n";
	cout << "============================================================================================\n\n";
	Sleep(500);
	system("cls");
	cout << "============================================================================================\n\n";
	cout << "                                     恭喜你！注销成功！			   							\n";
	cout << "============================================================================================\n\n";
	returnMainWindow(NULL);
}

void PutinCourseInformation() {
	CourseCountStudent = 0;
	char FileName[40];
	cout << "请输入需要导入的文件名称：";
	cin >> FileName;
	FILE* pfile = fopen(FileName, "r+t");
	if (pfile == NULL) {
		returnAdminister("无法打开此文件，请重新输入");
	}
	while (!feof(pfile)) {
		fscanf(pfile, "%3s", &courStudent[CourseCountStudent].CourseID);
		fscanf(pfile, "\t");
		fscanf(pfile, "%s",&courStudent[CourseCountStudent].CourseName);
		fscanf(pfile, "\t");
		fscanf(pfile, "%s",&courStudent[CourseCountStudent].Teacher);
		fscanf(pfile, "\t");
		fscanf(pfile, "%d\t\t",&courStudent[CourseCountStudent].MaxContent);
		fscanf(pfile, "\t");
		fscanf(pfile, "%d\t\t", &courStudent[CourseCountStudent].CurStudent);
		fscanf(pfile, "\t");
		char temp[20];
		fscanf(pfile, "%s",temp);
		if (!strcmp(temp, "专业课"))courStudent[CourseCountStudent].Major = true;
		else courStudent[CourseCountStudent].Major = false;
		fscanf(pfile, "\n");
		courStudent[CourseCountStudent].Exist = true;
		courStudent[CourseCountStudent].assistant.a = new char* [20];
		for (int j = 0; j < 20; j++)courStudent[CourseCountStudent].assistant.a[j] = new char[30];
		courStudent[CourseCountStudent].assistant.num = 0;
		CourseCountStudent++;
	}
	fclose(pfile);
	//创建当前课程文本
	FILE* pf = fopen("currentcourse.txt","a");
	fclose(pf);
	//每次修改完都导入当前课程文本
	CurrentCourseintotxt();
	returnAdminister("============================================================================================\n\n                                     恭喜你！导入成功！			   							\n============================================================================================\n\n");
	return ;
}
//查看所有课程函数
void ScanAllCourseInformation() {
	cout << "============================================================================================\n\n";
	cout << "课程ID     课程名称			 授课教师    上限人数   目前已选   课程类型\n";
	for (int i = 0; i < CourseCountStudent; i++) 
		//如果这门课程存在的话
		if (courStudent[i].Exist) { ShowCourse(i); cout << endl; }
	cout << "============================================================================================\n\n";
	char c = getchar();
	c = getchar();
	if (c != '~') {
		system("cls");
		ShowAdminister();
	}
	return;
}

void ScanAid() {
	GoToxy(0,12);
	cout << "当前全部课程为：";
	cout << "当前已有课程有\n";
	cout << "============================================================================================\n\n";
	cout << "课程ID     课程名称			 授课教师    上限人数   目前已选   课程类型\n";
	for (int i = 0; i < CourseCountStudent; i++)
		//如果这门课程存在的话
		if (courStudent[i].Exist) { ShowCourse(i); cout << endl; }
	cout << "============================================================================================\n\n";
	return;
}


void AddCourse() {
	int num;
	cout << "请输入需要添加的课程的数量：";
	cin >> num;
	cout << "课程名称 任课教师 可容纳人数 当前人数 课程类别（专业课/非专业课）\n";
	cout << "请输入课程信息(用空格隔开)：";
	char temp[20];
	for (int i = 0; i < num; i++) {
		cout << "第"<<i+1<<"个课程："<<endl;
		cin >> courStudent[CourseCountStudent].CourseName
			>> courStudent[CourseCountStudent].Teacher
			>> courStudent[CourseCountStudent].MaxContent
			>> courStudent[CourseCountStudent].CurStudent
			>> temp;
		for (int j = 0; j < CourseCountStudent; j++) 
			if (!strcmp(courStudent[CourseCountStudent].CourseName, courStudent[j].CourseName)) 
				returnAdminister("不能重复添加课程！！！");
		if (courStudent[CourseCountStudent].MaxContent < courStudent[CourseCountStudent].CurStudent) {
			returnAdminister("添加失败！！！最大可容纳人数小于现有选课人数");
		}
		if (!strcmp(temp, "专业课"))courStudent[CourseCountStudent].Major = true;
		else courStudent[CourseCountStudent].Major = false;
		courStudent[CourseCountStudent].Exist = true;
		char temID[4];
		if (CourseCountStudent < 9) {
			strcpy(temID, "00");
			char temnum[3];
			_itoa(CourseCountStudent +1, temnum, 10);
			strcat(temID, temnum);
		}
		else {
			strcpy(temID, "0");
			char temnum[3];
			_itoa(CourseCountStudent +1, temnum, 10);
			strcat(temID, temnum);
		}
		strcpy(courStudent[CourseCountStudent].CourseID, temID);
		courStudent[CourseCountStudent].assistant.num = 0;
		courStudent[CourseCountStudent].assistant.a = new char* [20];
		for (int j = 0; j < 20; j++)courStudent[CourseCountStudent].assistant.a[j] = new char[30];
		CourseCountStudent++;
	}
	if (CourseCountStudent==1) { CourseCountStudent = 0; returnAdminister("当前课程未进行初始化,无法添加课程"); }
	system("cls");
	CurrentCourseintotxt();
	cout << "============================================================================================\n\n";
	cout << "                                 恭喜你，添加成功！！！！！	    							\n";
	cout << "============================================================================================\n\n";
	Sleep(1000);
	cout << "当前全部课程为：\n";
	ScanAllCourseInformation();
	return;
}
void DeleteCourse() {
	ScanAid();
	GoToxy(0, 6);
	cout << "请输入课程编号：";
	char Deleted[5];
	cin >> Deleted;
	for (int i = 0; i < CourseCountStudent; i++) {

		if (!strcmp(Deleted, courStudent[i].CourseID)) {
			if (courStudent[i].Exist) {
				if (courStudent[i].CurStudent > 0) {
					returnAdminister("删除失败，已有学生选课！！！");
				}
				courStudent[i].Exist = false;
				system("cls");
				cout << "============================================================================================\n\n";
				cout << "                                 恭喜你，删除成功！！！！！	    							\n";
				cout << "============================================================================================\n\n";
				CurrentCourseintotxt();
				cout << "当前全部课程为：\n";
				ScanAllCourseInformation();
			}
			else {
				cout << "删除失败，此课程已被删除！";
				Sleep(2000);
				system("cls");
				ShowAdminister();
			}
		}
	}
	cout << "抱歉，不存在该课程！";
	Sleep(1500);
	system("cls");
	ShowAdminister();
	return;
}

void ChangeCourse() {
	ScanAid();
	GoToxy(0, 6);
	cout << "请输入需要修改的课程的ID：";
	char Change[5];
	cin >> Change;
	for (int i = 0; i < CourseCountStudent; i++) {
		if (!strcmp(Change, courStudent[i].CourseID)) {
			if (!courStudent[i].Exist) {
				cout << "选择失败，此课程已被删除！";
				Sleep(2000);
				system("cls");
				ShowAdminister();
			}
			cout << "需要修改的具体字段（1.授课教师   2.容纳人数）：";
			char command;
			cin >> command;
			if (command == '1') {
				cout << "具体修改为：";
				char name[30];
				cin >> name;
				strcpy(courStudent[i].Teacher, name);
				cout << "修改成功！！！";
				CurrentCourseintotxt();
				Sleep(2000);
				system("cls");
				ShowAdminister();
			}
			else if (command == '2') {
				cout << "具体修改为：";
				int num;
				cin >> num;
				if (num < courStudent[i].CurStudent)returnAdminister("修改的人数小于当前报名人数！修改失败！");
				courStudent[i].MaxContent=num ;
				cout << "修改成功！！！";
				CurrentCourseintotxt();
				Sleep(2000);
				system("cls");
				ShowAdminister();
			}
			else {
				cout << "不存在该操作";
				Sleep(2000);
				system("cls");
				ShowAdminister();

			}

		}
	}
	cout << "抱歉，不存在该课程！";
	Sleep(1500);
	system("cls");
	ShowAdminister();
	return;
}

void ScanSpecificCourse() {
	readinassistant();
	cout << "请输入要查看的课程的ID或名称：";
	char Scan[5];
	cin >> Scan;
	int i = Match2(Scan);
	if (!courStudent[i].Exist)returnAdminister("该课程已被删除！");
	cout << "============================================================================================\n\n";
	cout << "课程ID     课程名称                 授课教师    上限人数   目前已选   课程类型\n";
	ShowCourse(i);
	cout << endl;
	cout << "============================================================================================\n\n";
	cout << "1.查看选课学生名单 2.查看课程报名助教名单 按其他任意键返回\n您还想进行的操作有：";
	char c = getchar();
	c = getchar();
	if (c == '1') {
		cout<<"目前这门课的学生有：\n";
		for (int j = 0; j < courStudent[i].s.size(); j++) {
			if(strcmp(courStudent[i].s[j],"NULL"))
				cout << courStudent[i].s[j]<<" ";
		}
		char c = getchar();
		c = getchar();
		if (c != '~') { system("cls"); ShowAdminister(); }
	}
	else if (c == '2') {
		int x = Match(Scan);
		cout << "目前这门课程的助教有：";
		for (int j = 0; j < courStudent[x].assistant.num; j++) {
			if (strcmp(courStudent[x].assistant.a[j], "NULL"))
				printf("%s", courStudent[i].assistant.a[j]);
			if (j < courStudent[i].assistant.num - 1)printf(",");
		}
		char c = getchar();
		c = getchar();
		if (c != '~') { system("cls"); ShowAdminister(); }
	}
	else { system("cls"); ShowAdminister(); }
	return;
}

int Match2(char* s) {
	int i;
	for (i = 0; i < CourseCountStudent; i++) {
		if (!strcmp(s, courStudent[i].CourseID) || !strcmp(s, courStudent[i].CourseName)) {
			return i;
		}
	}
	returnAdminister("抱歉，这门课程不存在！！！");
	return 0;
}


//把当前课程的信息重新导入当前课程文本
void CurrentCourseintotxt() {
	FILE* pfile = fopen("currentcourse.txt", "w+t");
	if (pfile == NULL) {
		cout << "404 NOT FOUND!!!";
		exit(0);
	}
	for (int i = 0; i < CourseCountStudent; i++) {
		fprintf(pfile, "%s", courStudent[i].CourseID);
		fprintf(pfile, "\t");
		fprintf(pfile, "%s", courStudent[i].CourseName);
		fprintf(pfile, "\t");
		fprintf(pfile, "%s", courStudent[i].Teacher);
		fprintf(pfile, "\t");
		fprintf(pfile, "%d", courStudent[i].MaxContent);
		fprintf(pfile, "\t");
		fprintf(pfile, "%d", courStudent[i].CurStudent);
		fprintf(pfile, "\t");
		if (courStudent[i].Major) {
			fprintf(pfile, "专业课");
		}
		else {
			fprintf(pfile, "非专业课");
		}
		fprintf(pfile, "\t");
		if (courStudent[i].Exist)fprintf(pfile, "1");
		else fprintf(pfile, "0");
		fprintf(pfile, "\n");
	}
	fclose(pfile);
	return;
}

void readcurrent() {
	if (CourseCountStudent != 0)return;
	CourseCountStudent = 0;
	FILE* pfile = fopen("currentcourse.txt", "r+t");
	if (pfile == NULL) {
		return;
	}
	while (!feof(pfile)) {
		fscanf(pfile, "%3s", &courStudent[CourseCountStudent].CourseID);
		fscanf(pfile, "\t");
		fscanf(pfile, "%s", &courStudent[CourseCountStudent].CourseName);
		fscanf(pfile, "\t");
		fscanf(pfile, "%s", &courStudent[CourseCountStudent].Teacher);
		fscanf(pfile, "\t");
		fscanf(pfile, "%d\t\t", &courStudent[CourseCountStudent].MaxContent);
		fscanf(pfile, "\t");
		fscanf(pfile, "%d\t\t", &courStudent[CourseCountStudent].CurStudent);
		fscanf(pfile, "\t");
		char temp[20];
		fscanf(pfile, "%s", temp);
		if (!strcmp(temp, "专业课"))courStudent[CourseCountStudent].Major = true;
		else courStudent[CourseCountStudent].Major = false;
		fscanf(pfile, "\t");
		fscanf(pfile, "%d", &courStudent[CourseCountStudent].Exist);
		fscanf(pfile, "\n");
		courStudent[CourseCountStudent].assistant.a = new char* [20];
		for (int j = 0; j < 20; j++)courStudent[CourseCountStudent].assistant.a[j] = new char[30];
		courStudent[CourseCountStudent].assistant.num = 0;
		CourseCountStudent++;
	}
	fclose(pfile);
	return;
}


void returnAdminister(const char* word) {
	if (word != NULL)cout << word;
	Sleep(1000);
	system("cls");
	ShowAdminister();
}

void dealstudent() {
	for (int i = 0; i < studentnum; i++) {
		char* sname = new char[40];
		char* filename = new char[50];
		MyCourses* t = new MyCourses[30];
		int num = 0;
		strcpy(sname, Stu[i].StudentID);
		strcpy(filename, Stu[i].StudentID);
		strcat(filename, ".txt");
		FILE* pfile = fopen(filename, "r");
		while (!feof(pfile)) {
			fscanf(pfile, "%s", t[num].id);
			fscanf(pfile, "\t");
			fscanf(pfile, "%s", t[num].AssistantName);
			fscanf(pfile, "\n");
			num++;
		}
		fclose(pfile);
		if (strlen(t[0].id) == 0)num--;
		for (int p = 0; p < num; p++) {
			for (int j = 0; j < CourseCountStudent; j++) {
				if (!strcmp(t[p].id, courStudent[j].CourseID)) {
					for (int q = 0; q < courStudent[j].s.size(); j++) {
						if (!strcmp(courStudent[j].s[q], sname)) {
							goto L;
						}
					}
					courStudent[j].s.push_back(sname);
					break;
				}
			}
		L:;
		}
	}
	return;
}

void tongzhi() {
	cout << "请输入您想进行的操作：(1)发布通知(2)删除通知\n";
	char c;
	cin >> c;
	if (c == '1') {
		cout << "请在下方输入您想公布的通知内容\n";
		char* s = new char[200];
		cin >> s;
		FILE* pf = fopen("tongzhi.txt", "w+t");
		fprintf(pf, "%s", s);
		fclose(pf);
		returnAdminister("发布通知成功！！！");
	}
	else if (c == '2') {
		FILE* pf = fopen("tongzhi.txt", "w");
		fprintf(pf, "%s", "c");
		fclose(pf);
		returnAdminister("删除成功!!!");
	}
	else returnAdminister("抱歉，没有此操作");
	return;
}


