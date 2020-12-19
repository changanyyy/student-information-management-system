#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<Windows.h>
#include<vector>
#include"Administer.h"
#include"MainWindow.h"
#include"Student.h"

using namespace std;

//当前学校所有课程的情况，通过showstudent导入
Course courStudent[30];
int CourseCountStudent = 0;


//我自己的课程
MyCourses MyCourse[30];
//我自己课程的数量，通过刚进来时从student1导入
//导入在主窗口进行
int coursenum;

extern student Stu[40];
extern int studentnum;

extern char* StudentID;



//读进来我的课程情况，包括已选课程ID和助教
void WriteStudent(char* studentID) {
	coursenum=0;
	char filename[20];
	strcpy(filename, studentID);
	strcat(filename, ".txt");
	FILE* pfile = fopen(filename, "r+t");
	if (pfile == NULL) {
		cout << "404 NOT FOUND";
		Sleep(1000);
		exit(0);
	}
	while (!feof(pfile)) {
		fscanf(pfile, "%s", MyCourse[coursenum].id);
		fscanf(pfile, "\t");
		fscanf(pfile, "%s", MyCourse[coursenum].AssistantName);
		fscanf(pfile, "\n");
		coursenum++;
	}
	fclose(pfile);
	if (strlen(MyCourse[0].id) == 0)coursenum--;
	return;
}

//展示学生端的主要函数
void ShowStudent() {
	checkassistant();
	GoToxy(0, 0);
	cout << "=======================================================================================================\n\n";
	cout << " 1.注销登录  2.查看课程信息  3.选课  4.查看个人课表  5.退课  6.举手报名助教  7.选择个人助教  8.修改密码\n\n";
	cout << "=======================================================================================================\n\n";
	cout << "请选择需要的功能：" ;
	char function;
	cin >> function;
	//提供进入其他功能的接口，采用switch函数
	switch (function) {
	case '1': strcpy(MyCourse[0].id,""); Logout(); break;
	case '2': ScanCourse(); break;
	case '3': SelectCourse(); break;
	case '4': ScanMyCourse(); break;
	case '5': QuitCourse(); break;
	case '6': BeAssistant(); break;
	case '7': SelectAssistant(); break;
	case '8': changepwd(); break;
	default : returnStudent("抱歉无此操作，请重新选择"); break;
	}
	return;
}

//学生注册显示函数
void RegisterStudent() {
	cout << "============================================================================================\n\n";
	cout << "                              欢迎来到南京大学计算机系！！！！                               \n";
	cout << "============================================================================================\n\n";
	cout << "请输入用户名：\n";
	cout << "请输入密码：\n";
	cout << "请再次确认密码：\n";
	//设置确认密码选项，以免输错
	char UserName[20];
	char Password[20];
	char ConfirmPassword[20];
	GoToxy(7, 5);
	cin >> UserName;
	GoToxy(6, 6);
	strcpy(Password, getpwd());
	GoToxy(8, 7);
	strcpy(ConfirmPassword, getpwd());
	if (!strcmp(Password, ConfirmPassword)) 
		//功能函数，完成注册的一系列功能性操作
		SucceedRegisterStudent(UserName, Password);
	else returnMainWindow("两次输入的密码不一致，请重新注册！！！");
	return;
}

//学生注册功能函数
void SucceedRegisterStudent(char* UserName, char* Password) {
	student All[30];
	int count = 0;
	//先将student的ID和密码导入All
	FILE* pfile = fopen("student.txt", "r");
	if (pfile == NULL) {
		pfile = fopen("student.txt", "a");
		fclose(pfile);
		goto L;
	}
	pfile = fopen("student.txt", "r");
	while (!feof(pfile)) {
		fscanf(pfile, "%[^','],%s", &All[count].StudentID, &All[count].StudentPassword);
		fscanf(pfile, "\n");
		count++;
	}
	fclose(pfile);
	//增加一个新注册的用户
	L: strcpy(All[count].StudentID, UserName);
	strcpy(All[count].StudentPassword, Password);
	count++;
	//再把完整的新数组导回去
	FILE* pf = fopen("student.txt", "w");
	if (pf == NULL) {
		cout << "ERROR!";
		exit(0);
	}
	for (int i = 0; i < count; i++) {
		fprintf(pf, "%s", All[i].StudentID);
		fprintf(pf, ",");
		fprintf(pf, "%s", All[i].StudentPassword);
		fprintf(pf, "\n");
	}
	fclose(pf);
	//创建新用户相关课程文件
	Createfile(UserName);
	cout << "注册成功！！！";
	Sleep(1500);
	system("cls");
	ShowMainWindow();
	return ;
}
//创建文件函数，用于创建一个文件
void Createfile(char* fname)
{
	strcat(fname, ".txt");
	FILE *fp = fopen(fname, "a");
	fclose(fp);
	return ;
}

//查看全部课程函数
void ScanCourse() {
	cout << "============================================================================================\n\n";
	cout << "课程ID     课程名称                 授课教师    上限人数   目前已选   课程类型\n";
	for (int i = 0; i < CourseCountStudent; i++) 
		if (courStudent[i].Exist) {ShowCourse(i);cout << endl;}
	cout << "============================================================================================\n\n";
	//设置按任意键继续功能
	char c = getchar();
	c = getchar();
	if (c != '~') {
		system("cls");
		ShowStudent();
	}
	return;
}
//选课函数
void SelectCourse() {
	ScanAids();
	GoToxy(0, 7);
	cout << "请输入课程ID:";
	char ID[5];
	cin >> ID;
	for (int i = 0; i < CourseCountStudent; i++) {
		if (!strcmp(ID, courStudent[i].CourseID)) {
			//该门课程存在的话
			if (courStudent[i].Exist) {
				//对于课程人数已满的特殊情况处理
				if (courStudent[i].MaxContent == courStudent[i].CurStudent) {
					//进行良好的回显，显示现有课程
					cout << "============================================================================================\n\n";
					cout << "课程ID     课程名称                 授课教师    上限人数   目前已选   课程类型\n";
					ShowCourse(i);
					cout << "\n============================================================================================\n\n";
					returnStudent("该课程人数已满！！！无法选择！！！");
				}
				//对已选此课的特殊请况处理
				for (int j = 0; j < coursenum; j++) {
					if (!strcmp(ID, MyCourse[j].id)) {
						returnStudent("已选该课，无法重复选择");
					}
				}
				//录入到个人信息数组里
				strcpy(MyCourse[coursenum].id, ID);
				strcpy(MyCourse[coursenum++].AssistantName, "NULL");
				//个人信息数组导入个人信息文本
				WritePersonal();
				//录入到全部课程数组里，选课人数+1
				int x = Match(ID);
				courStudent[x].CurStudent++;
				courStudent[x].s.push_back(StudentID);
				//课程信息导入全部课程文本
				CurrentCourseintotxt();
				returnStudent("============================================================================================\n\n					恭喜你！！！选课成功！！！                              \n\n============================================================================================\n\n");
			}
		}
	}
	//不存在这门课的特殊处理
	returnStudent("您选的这门课不存在，请重新选择！！！");
	return;
}
//查看我的课程函数
void ScanMyCourse() {
	cout << "============================================================================================\n\n";
	cout << "课程ID     课程名称                 授课教师    上限人数   目前已选   课程类型     个人助教\n";
	if (CourseCountStudent > 0) {
		for (int i = 0; i < coursenum; i++) {
			//添加其他东西
			for (int j = 0; j < CourseCountStudent; j++) {
				if (!strcmp(MyCourse[i].id, courStudent[j].CourseID)) {
					if (!courStudent[j].Exist)break;
					ShowCourse(j);
					break;
				}
			}
			if (!strcmp(MyCourse[i].AssistantName, "NULL")) { cout << endl; continue; }
			else printf("%-10s\n", MyCourse[i].AssistantName);
		}
	}
	else cout << "暂无课程！！！！\n";
	cout << "============================================================================================\n\n";
	char c = getchar();
	c = getchar();
	if (c != '~') {
		system("cls");
		ShowStudent();
	}
	return;
}
//退课函数
void QuitCourse() {
	ScanAidd();
	GoToxy(0, 6);
	cout << "请输入您想要退选的课程ID：";
	char ID[5];
	cin >> ID;
	for (int i = 0; i < coursenum; i++) {
		if (!strcmp(ID, MyCourse[i].id)) {
			for (int j = 0; j < CourseCountStudent; j++) {
				if (!strcmp(ID, courStudent[j].CourseID)) {
					//对全部课程数组操作
					courStudent[j].CurStudent--;
					//取消助教身份
					Dealquitassistant(j);
					//立刻将信息导入全部课程文本
					CurrentCourseintotxt();
					//接下来利用函数对个人信息数组操作
					DeletePersonal(i);
					//导入个人信息文本
					WritePersonal();
					//导入助教文本
					writeassistant();
					int x = Match(ID);
					for (int i = 0; i < courStudent[x].s.size(); i++) {
						if (!strcmp(StudentID, courStudent[x].s[i])) {
							courStudent[x].s.erase(courStudent[x].s.begin()+i);
						}
					}
				}
			}
			system("cls");
			//显示是否符合要求
			IsEnough();
			cout << "\n恭喜你，退课成功！！！\n当前已选课程有：\n";
			//给予回显，让用户看看自己选了什么
			ScanMyCourse();
		}
	}
	returnStudent("抱歉，您未选择这门课程！！！");
	return;
}

//如果退课的话，课程里的助教身份也应该取消
void Dealquitassistant(int index) {
	for (int i = 0; i < courStudent[index].assistant.num; i++) {
		if (!strcmp(courStudent[index].assistant.a[i], StudentID)) strcpy(courStudent[index].assistant.a[i], "NULL");
	}
}

void BeAssistant() {
	readinassistant();
	cout << "请输入对应课程ID或名称：";
	char tem[20];
	cin >> tem;
	if (BeinCourse(tem) < 0) {
		returnStudent("您还未选这门课！！！");
	}
	int index = Match(tem);
	for (int i = 0; i < courStudent[index].assistant.num; i++) {
		if (!strcmp(courStudent[index].assistant.a[i], StudentID)) returnStudent("您已是该课程助教，无需重复报名！！！");
	}
	//修改全部课程数组
	//将全部课程数组的助教信息写入文件
	strcpy(courStudent[index].assistant.a[courStudent[index].assistant.num], StudentID);
	courStudent[index].assistant.num++;
	writeassistant();
	returnStudent("报名成功！！！");
	return;
}

//查看这门课的位置
int Match(char* s) {
	int i;
	for (i = 0; i < CourseCountStudent; i++) {
		if (!strcmp(s,courStudent[i].CourseID)||!strcmp(s,courStudent[i].CourseName)) {
			return i;
		}
	}
	if(CourseCountStudent!=0&&coursenum!=0)returnStudent("抱歉，这门课程不存在！！！");
	return 0;
}



//把助教信息从助教文本导入全部课程数组
void readinassistant() {
	FILE* pfile = fopen("assistant.txt","r+t");
	if (pfile == NULL) {
		pfile = fopen("assistant.txt", "a");
		fclose(pfile);
		return;
	}
	pfile = fopen("assistant.txt", "r+t");
	while (!feof(pfile)) {
		char ID[30];
		fscanf(pfile, "%s", ID);
		fscanf(pfile, "\t");
		for (int i = 0; i < CourseCountStudent; i++) {
			if (!strcmp(ID, courStudent[i].CourseID)){
				courStudent[i].assistant.num = 0;
				char tem[100];
				fscanf(pfile, "%s", tem);
				char* token;
				token = strtok(tem, ",");
				while (token != NULL) {
					strcpy(courStudent[i].assistant.a[courStudent[i].assistant.num], token);
					courStudent[i].assistant.num++;
					token = strtok(NULL, ",");
				}
			}
		}
		fscanf(pfile, "\n");
	}
	fclose(pfile);
	return;
}
//把助教信息写入助教文件
void writeassistant() {
	FILE* pfile = fopen("assistant.txt", "w+t");
	if (pfile == NULL) {
		cout << "ERROR";
		exit(0);
	}
	for (int i = 0; i < CourseCountStudent; i++) {
		if (checkhave(i))continue;
		fprintf(pfile, "%s", courStudent[i].CourseID);
		fprintf(pfile, "\t");
		for (int j = 0; j < courStudent[i].assistant.num; j++) {
			if (strcmp(courStudent[i].assistant.a[j], "NULL")) {
				fprintf(pfile, "%s", courStudent[i].assistant.a[j]);
				if (j < courStudent[i].assistant.num - 1)fprintf(pfile, ",");
			}
		}
		fprintf(pfile, "\n");
	}
    fclose(pfile);
	return;
}

void SelectAssistant(){
	readinassistant();
	cout << "请输入课程ID或名称：";
	char ID[30];
	cin >> ID;
	int x = Match(ID);
	//特殊情况处理
	if (!courStudent[x].Exist) returnStudent("抱歉该门课程不存在");
	for (int i = 0; i < coursenum; i++) {
		if (!strcmp(courStudent[x].CourseID, MyCourse[i].id)) goto K;
	}
	cout << "抱歉，您未选择此门课程！！！\n您已选择的课程有：\n";
	ScanMyCourse();
	K:	if (courStudent[x].assistant.num == 0) returnStudent("抱歉该门课程暂时没有助教");
	cout << "目前这门课程的助教有：";
	for (int i = 0; i < courStudent[x].assistant.num; i++) {
		if (strcmp(courStudent[x].assistant.a[i], "NULL"))printf("%s  ", courStudent[x].assistant.a[i]);
	}
	cout << "\n请在上述助教中选择你的助教：";
	char a[30];
	cin >> a;
	if (!strcmp(a, StudentID))returnStudent("抱歉，不能选择自己为助教！");
	for (int i = 0; i < courStudent[x].assistant.num; i++) {
		if (!strcmp(courStudent[x].assistant.a[i], a))goto L;
	}
	returnStudent("该课程没有此助教");
	L:
	for (int i = 0; i < coursenum; i++) {
		if (!strcmp(ID, MyCourse[i].id)) {
			strcpy(MyCourse[i].AssistantName,a);
			WritePersonal(); 
			returnStudent("恭喜你！！！成功选择助教！！！");
		}
	}
	return;
}


//将个人信息数组写入个人信息文本
void WritePersonal() {
	char filename[30];
	strcpy(filename, StudentID);
	strcat(filename, ".txt");
	FILE* pfile = fopen(filename, "w+t");
	if (pfile == NULL) {
		cout << "404 NOT FOUND!!!";
		Sleep(1500);
		exit(0);
	}
	for (int i = 0; i < coursenum;i++) {
		fprintf(pfile, "%s", MyCourse[i].id);
		fprintf(pfile, "\t");
		if (strcmp(MyCourse[i].AssistantName,"NULL"))fprintf(pfile, "%s", MyCourse[i].AssistantName);
		else fprintf(pfile, "%s", "NULL");
		fprintf(pfile, "\n");
	}
	fclose(pfile);
	return;
}
//把删除的课程从个人信息数组中删除
void DeletePersonal(int i) {
	for (int j = i; j < coursenum-1; j++) {
		MyCourse[j] = MyCourse[j + 1];
	}
	coursenum--;
	return;
}
//判断课程数量是否达标，给予显示
void IsEnough() {
	int isnum = 0, notnum = 0;
	for (int i = 0; i < coursenum; i++) {
		for (int j = 0; j < CourseCountStudent; j++) {
			if (!strcmp(MyCourse[i].id, courStudent[j].CourseID)) {
				if (courStudent[j].Major)isnum++;
				else notnum++;
			}
		}
	}
	if (isnum >= 4 && notnum >= 2)cout << "您选的课程数量已经达标！！！";
	else if (isnum < 4 && notnum >= 2) {
		cout << "根据学院要求，您选的课程数目不达标！！！";
		cout << "仍差" << 4 - isnum << "门专业课";
	}
	else if (isnum >= 4 && notnum < 2) {
		cout << "根据学院要求，您选的课程数目不达标！！！";
		cout << "仍差" << 2 - notnum << "门专业课";
	}
	else {
		cout << "根据学院要求，您选的课程数目不达标！！！";
		cout << "仍差" << 4 - isnum << "门专业课和"<<2-notnum<<"门非专业课";
	}
	return;
}
//输出序号为i的课程信息
void ShowCourse(int i) {
	printf("%-10s", courStudent[i].CourseID);
	printf("%-30s", courStudent[i].CourseName);
	printf("%-10s", courStudent[i].Teacher);
	printf("\t%d\t", courStudent[i].MaxContent);
	printf("%d\t\t", courStudent[i].CurStudent);
	if (courStudent[i].Major)printf("%-10s", "专业课");
	else printf("%-10s", "非专业课");
	return;
}

//判断学生是否已经在这门课里
int BeinCourse(char* courseID) {
	for (int i = 0; i < coursenum; i++) {
		if (!strcmp(courseID, MyCourse[i].id)) {
			return i;
		}
	}
	return -10;
}

//异常处理之后返回学生主界面
void returnStudent(const char * word) {
	if(word!=NULL)cout << word;
	Sleep(1000);
	system("cls");
	ShowStudent();
}

void checkassistant() {
	readinassistant();
	for (int i = 0; i < coursenum; i++) {
		int x = Match(MyCourse[i].id);
		if (CourseCountStudent == 0)return;
		if (!strcmp(MyCourse[i].AssistantName, "NULL"))continue ;
		for (int j = 0; j < courStudent[x].assistant.num; j++) {
			if (!strcmp(courStudent[x].assistant.a[j], MyCourse[i].AssistantName)) return;
		}
		GoToxy(10, 15);
		cout << "您的" << courStudent[x].CourseName << "课程的助教" << MyCourse[i].AssistantName << "已经退课！！！"<<endl;
	}
	return;
}

bool checkhave(int i) {
	if (courStudent[i].assistant.num == 0)return true;
	else {
		for (int j = 0; j < courStudent[i].assistant.num; j++) {
			if (strcmp(courStudent[i].assistant.a[j], "NULL"))return false;
		}
		return true;
	}
}


void ScanAids() {
	GoToxy(0, 14);
	cout << "当前全部课程为：";
	cout << "您当前未选课程有：\n";
	cout << "============================================================================================\n\n";
	cout << "课程ID     课程名称			 授课教师    上限人数   目前已选   课程类型\n";
	for (int i = 0; i < CourseCountStudent; i++)
		//如果这门课程存在的话
		if (courStudent[i].Exist) {
			for (int j = 0; j < coursenum; j++) {
				if (!strcmp(MyCourse[j].id, courStudent[i].CourseID))goto L;
			}
			ShowCourse(i);
			cout << endl;
		L:;
		}
	cout << "============================================================================================\n\n";
	return;
}
void ScanAidd() {
	GoToxy(0, 14);
	cout << "当前全部课程为：";
	cout << "您当前已选课程有：\n";
	cout << "============================================================================================\n\n";
	cout << "课程ID     课程名称			 授课教师    上限人数   目前已选   课程类型\n";
	for (int i = 0; i < coursenum; i++) {
		//添加其他东西
		for (int j = 0; j < CourseCountStudent; j++) {
			if (!strcmp(MyCourse[i].id, courStudent[j].CourseID)) {
				if (!courStudent[j].Exist)break;
				ShowCourse(j);
				break;
			}
		}
		if (!strcmp(MyCourse[i].AssistantName, "NULL")) { cout << endl; continue; }
		else printf("%-10s\n", MyCourse[i].AssistantName);
	}
	cout << "============================================================================================\n\n";
	return;
}

void changepwd() {
	cout<< "请输入您原来的密码：\n";
	cout << "请输入新密码：\n";
	cout << "请确认新密码：\n";
	char old[30];
	char np[30];
	char cnp[30];
	GoToxy(10, 7);
	strcpy(old, getpwd());
	GoToxy(7, 8);
	strcpy(np, getpwd());
	GoToxy(7, 9);
	strcpy(cnp, getpwd());
	for (int i = 0; i < studentnum; i++) {
		if (!strcmp(StudentID, Stu[i].StudentID)) {
			if (!strcmp(old, Stu[i].StudentPassword)) {
				if (!strcmp(np, cnp)) {
					strcpy(Stu[i].StudentPassword, np);
					FILE* pf = fopen("student.txt", "w");
					if (pf == NULL) {
						cout << "ERROR!";
						exit(0);
					}
					for (int i = 0; i < studentnum; i++) {
						fprintf(pf, "%s", Stu[i].StudentID);
						fprintf(pf, ",");
						fprintf(pf, "%s", Stu[i].StudentPassword);
						fprintf(pf, "\n");
					}
					fclose(pf);
					returnStudent("密码修改成功！！！");
				}
				else returnStudent("抱歉，两次密码输入不一致！！！");
			}
			else returnStudent("抱歉，原密码输入错误");
		}
	}
	return;
}