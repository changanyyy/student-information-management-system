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

//ȫ���γ����飨��ǰ�γ̣�
extern Course courStudent[30];
extern int CourseCountStudent;
extern int studentnum;

extern student Stu[20];

void ShowAdminister() {
	cout << "=======================================================================================================\n\n";
	cout << "1.ע����¼ 2.¼��γ���Ϣ 3.�鿴ȫ���γ���Ϣ 4.���ӿγ� 5.ɾ���γ� 6.�޸Ŀγ� 7.�鿴����γ� 8.����֪ͨ\n";
	cout << "=======================================================================================================\n\n";
	cout << "��ѡ����Ҫ�Ĺ��ܣ�";
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
	default:cout << "��Ǹ�޴˲�����������ѡ��"; Sleep(2000); system("cls"); ShowAdminister(); break;
	}
	return;
}

//ע������
void Logout() {
	system("cls");
	cout << "============================================================================================\n\n";
	cout << "                                     ���Եȣ�����ע��			   							\n";
	cout << "============================================================================================\n\n";
	Sleep(500);
	system("cls");
	cout << "============================================================================================\n\n";
	cout << "                                     ��ϲ�㣡ע���ɹ���			   							\n";
	cout << "============================================================================================\n\n";
	returnMainWindow(NULL);
}

void PutinCourseInformation() {
	CourseCountStudent = 0;
	char FileName[40];
	cout << "��������Ҫ������ļ����ƣ�";
	cin >> FileName;
	FILE* pfile = fopen(FileName, "r+t");
	if (pfile == NULL) {
		returnAdminister("�޷��򿪴��ļ�������������");
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
		if (!strcmp(temp, "רҵ��"))courStudent[CourseCountStudent].Major = true;
		else courStudent[CourseCountStudent].Major = false;
		fscanf(pfile, "\n");
		courStudent[CourseCountStudent].Exist = true;
		courStudent[CourseCountStudent].assistant.a = new char* [20];
		for (int j = 0; j < 20; j++)courStudent[CourseCountStudent].assistant.a[j] = new char[30];
		courStudent[CourseCountStudent].assistant.num = 0;
		CourseCountStudent++;
	}
	fclose(pfile);
	//������ǰ�γ��ı�
	FILE* pf = fopen("currentcourse.txt","a");
	fclose(pf);
	//ÿ���޸��궼���뵱ǰ�γ��ı�
	CurrentCourseintotxt();
	returnAdminister("============================================================================================\n\n                                     ��ϲ�㣡����ɹ���			   							\n============================================================================================\n\n");
	return ;
}
//�鿴���пγ̺���
void ScanAllCourseInformation() {
	cout << "============================================================================================\n\n";
	cout << "�γ�ID     �γ�����			 �ڿν�ʦ    ��������   Ŀǰ��ѡ   �γ�����\n";
	for (int i = 0; i < CourseCountStudent; i++) 
		//������ſγ̴��ڵĻ�
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
	cout << "��ǰȫ���γ�Ϊ��";
	cout << "��ǰ���пγ���\n";
	cout << "============================================================================================\n\n";
	cout << "�γ�ID     �γ�����			 �ڿν�ʦ    ��������   Ŀǰ��ѡ   �γ�����\n";
	for (int i = 0; i < CourseCountStudent; i++)
		//������ſγ̴��ڵĻ�
		if (courStudent[i].Exist) { ShowCourse(i); cout << endl; }
	cout << "============================================================================================\n\n";
	return;
}


void AddCourse() {
	int num;
	cout << "��������Ҫ��ӵĿγ̵�������";
	cin >> num;
	cout << "�γ����� �ον�ʦ ���������� ��ǰ���� �γ����רҵ��/��רҵ�Σ�\n";
	cout << "������γ���Ϣ(�ÿո����)��";
	char temp[20];
	for (int i = 0; i < num; i++) {
		cout << "��"<<i+1<<"���γ̣�"<<endl;
		cin >> courStudent[CourseCountStudent].CourseName
			>> courStudent[CourseCountStudent].Teacher
			>> courStudent[CourseCountStudent].MaxContent
			>> courStudent[CourseCountStudent].CurStudent
			>> temp;
		for (int j = 0; j < CourseCountStudent; j++) 
			if (!strcmp(courStudent[CourseCountStudent].CourseName, courStudent[j].CourseName)) 
				returnAdminister("�����ظ���ӿγ̣�����");
		if (courStudent[CourseCountStudent].MaxContent < courStudent[CourseCountStudent].CurStudent) {
			returnAdminister("���ʧ�ܣ�����������������С������ѡ������");
		}
		if (!strcmp(temp, "רҵ��"))courStudent[CourseCountStudent].Major = true;
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
	if (CourseCountStudent==1) { CourseCountStudent = 0; returnAdminister("��ǰ�γ�δ���г�ʼ��,�޷���ӿγ�"); }
	system("cls");
	CurrentCourseintotxt();
	cout << "============================================================================================\n\n";
	cout << "                                 ��ϲ�㣬��ӳɹ�����������	    							\n";
	cout << "============================================================================================\n\n";
	Sleep(1000);
	cout << "��ǰȫ���γ�Ϊ��\n";
	ScanAllCourseInformation();
	return;
}
void DeleteCourse() {
	ScanAid();
	GoToxy(0, 6);
	cout << "������γ̱�ţ�";
	char Deleted[5];
	cin >> Deleted;
	for (int i = 0; i < CourseCountStudent; i++) {

		if (!strcmp(Deleted, courStudent[i].CourseID)) {
			if (courStudent[i].Exist) {
				if (courStudent[i].CurStudent > 0) {
					returnAdminister("ɾ��ʧ�ܣ�����ѧ��ѡ�Σ�����");
				}
				courStudent[i].Exist = false;
				system("cls");
				cout << "============================================================================================\n\n";
				cout << "                                 ��ϲ�㣬ɾ���ɹ�����������	    							\n";
				cout << "============================================================================================\n\n";
				CurrentCourseintotxt();
				cout << "��ǰȫ���γ�Ϊ��\n";
				ScanAllCourseInformation();
			}
			else {
				cout << "ɾ��ʧ�ܣ��˿γ��ѱ�ɾ����";
				Sleep(2000);
				system("cls");
				ShowAdminister();
			}
		}
	}
	cout << "��Ǹ�������ڸÿγ̣�";
	Sleep(1500);
	system("cls");
	ShowAdminister();
	return;
}

void ChangeCourse() {
	ScanAid();
	GoToxy(0, 6);
	cout << "��������Ҫ�޸ĵĿγ̵�ID��";
	char Change[5];
	cin >> Change;
	for (int i = 0; i < CourseCountStudent; i++) {
		if (!strcmp(Change, courStudent[i].CourseID)) {
			if (!courStudent[i].Exist) {
				cout << "ѡ��ʧ�ܣ��˿γ��ѱ�ɾ����";
				Sleep(2000);
				system("cls");
				ShowAdminister();
			}
			cout << "��Ҫ�޸ĵľ����ֶΣ�1.�ڿν�ʦ   2.������������";
			char command;
			cin >> command;
			if (command == '1') {
				cout << "�����޸�Ϊ��";
				char name[30];
				cin >> name;
				strcpy(courStudent[i].Teacher, name);
				cout << "�޸ĳɹ�������";
				CurrentCourseintotxt();
				Sleep(2000);
				system("cls");
				ShowAdminister();
			}
			else if (command == '2') {
				cout << "�����޸�Ϊ��";
				int num;
				cin >> num;
				if (num < courStudent[i].CurStudent)returnAdminister("�޸ĵ�����С�ڵ�ǰ�����������޸�ʧ�ܣ�");
				courStudent[i].MaxContent=num ;
				cout << "�޸ĳɹ�������";
				CurrentCourseintotxt();
				Sleep(2000);
				system("cls");
				ShowAdminister();
			}
			else {
				cout << "�����ڸò���";
				Sleep(2000);
				system("cls");
				ShowAdminister();

			}

		}
	}
	cout << "��Ǹ�������ڸÿγ̣�";
	Sleep(1500);
	system("cls");
	ShowAdminister();
	return;
}

void ScanSpecificCourse() {
	readinassistant();
	cout << "������Ҫ�鿴�Ŀγ̵�ID�����ƣ�";
	char Scan[5];
	cin >> Scan;
	int i = Match2(Scan);
	if (!courStudent[i].Exist)returnAdminister("�ÿγ��ѱ�ɾ����");
	cout << "============================================================================================\n\n";
	cout << "�γ�ID     �γ�����                 �ڿν�ʦ    ��������   Ŀǰ��ѡ   �γ�����\n";
	ShowCourse(i);
	cout << endl;
	cout << "============================================================================================\n\n";
	cout << "1.�鿴ѡ��ѧ������ 2.�鿴�γ̱����������� ���������������\n��������еĲ����У�";
	char c = getchar();
	c = getchar();
	if (c == '1') {
		cout<<"Ŀǰ���ſε�ѧ���У�\n";
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
		cout << "Ŀǰ���ſγ̵������У�";
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
	returnAdminister("��Ǹ�����ſγ̲����ڣ�����");
	return 0;
}


//�ѵ�ǰ�γ̵���Ϣ���µ��뵱ǰ�γ��ı�
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
			fprintf(pfile, "רҵ��");
		}
		else {
			fprintf(pfile, "��רҵ��");
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
		if (!strcmp(temp, "רҵ��"))courStudent[CourseCountStudent].Major = true;
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
	cout << "������������еĲ�����(1)����֪ͨ(2)ɾ��֪ͨ\n";
	char c;
	cin >> c;
	if (c == '1') {
		cout << "�����·��������빫����֪ͨ����\n";
		char* s = new char[200];
		cin >> s;
		FILE* pf = fopen("tongzhi.txt", "w+t");
		fprintf(pf, "%s", s);
		fclose(pf);
		returnAdminister("����֪ͨ�ɹ�������");
	}
	else if (c == '2') {
		FILE* pf = fopen("tongzhi.txt", "w");
		fprintf(pf, "%s", "c");
		fclose(pf);
		returnAdminister("ɾ���ɹ�!!!");
	}
	else returnAdminister("��Ǹ��û�д˲���");
	return;
}


