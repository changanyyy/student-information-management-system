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

//��ǰѧУ���пγ̵������ͨ��showstudent����
Course courStudent[30];
int CourseCountStudent = 0;


//���Լ��Ŀγ�
MyCourses MyCourse[30];
//���Լ��γ̵�������ͨ���ս���ʱ��student1����
//�����������ڽ���
int coursenum;

extern student Stu[40];
extern int studentnum;

extern char* StudentID;



//�������ҵĿγ������������ѡ�γ�ID������
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

//չʾѧ���˵���Ҫ����
void ShowStudent() {
	checkassistant();
	GoToxy(0, 0);
	cout << "=======================================================================================================\n\n";
	cout << " 1.ע����¼  2.�鿴�γ���Ϣ  3.ѡ��  4.�鿴���˿α�  5.�˿�  6.���ֱ�������  7.ѡ���������  8.�޸�����\n\n";
	cout << "=======================================================================================================\n\n";
	cout << "��ѡ����Ҫ�Ĺ��ܣ�" ;
	char function;
	cin >> function;
	//�ṩ�����������ܵĽӿڣ�����switch����
	switch (function) {
	case '1': strcpy(MyCourse[0].id,""); Logout(); break;
	case '2': ScanCourse(); break;
	case '3': SelectCourse(); break;
	case '4': ScanMyCourse(); break;
	case '5': QuitCourse(); break;
	case '6': BeAssistant(); break;
	case '7': SelectAssistant(); break;
	case '8': changepwd(); break;
	default : returnStudent("��Ǹ�޴˲�����������ѡ��"); break;
	}
	return;
}

//ѧ��ע����ʾ����
void RegisterStudent() {
	cout << "============================================================================================\n\n";
	cout << "                              ��ӭ�����Ͼ���ѧ�����ϵ��������                               \n";
	cout << "============================================================================================\n\n";
	cout << "�������û�����\n";
	cout << "���������룺\n";
	cout << "���ٴ�ȷ�����룺\n";
	//����ȷ������ѡ��������
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
		//���ܺ��������ע���һϵ�й����Բ���
		SucceedRegisterStudent(UserName, Password);
	else returnMainWindow("������������벻һ�£�������ע�ᣡ����");
	return;
}

//ѧ��ע�Ṧ�ܺ���
void SucceedRegisterStudent(char* UserName, char* Password) {
	student All[30];
	int count = 0;
	//�Ƚ�student��ID�����뵼��All
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
	//����һ����ע����û�
	L: strcpy(All[count].StudentID, UserName);
	strcpy(All[count].StudentPassword, Password);
	count++;
	//�ٰ������������鵼��ȥ
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
	//�������û���ؿγ��ļ�
	Createfile(UserName);
	cout << "ע��ɹ�������";
	Sleep(1500);
	system("cls");
	ShowMainWindow();
	return ;
}
//�����ļ����������ڴ���һ���ļ�
void Createfile(char* fname)
{
	strcat(fname, ".txt");
	FILE *fp = fopen(fname, "a");
	fclose(fp);
	return ;
}

//�鿴ȫ���γ̺���
void ScanCourse() {
	cout << "============================================================================================\n\n";
	cout << "�γ�ID     �γ�����                 �ڿν�ʦ    ��������   Ŀǰ��ѡ   �γ�����\n";
	for (int i = 0; i < CourseCountStudent; i++) 
		if (courStudent[i].Exist) {ShowCourse(i);cout << endl;}
	cout << "============================================================================================\n\n";
	//���ð��������������
	char c = getchar();
	c = getchar();
	if (c != '~') {
		system("cls");
		ShowStudent();
	}
	return;
}
//ѡ�κ���
void SelectCourse() {
	ScanAids();
	GoToxy(0, 7);
	cout << "������γ�ID:";
	char ID[5];
	cin >> ID;
	for (int i = 0; i < CourseCountStudent; i++) {
		if (!strcmp(ID, courStudent[i].CourseID)) {
			//���ſγ̴��ڵĻ�
			if (courStudent[i].Exist) {
				//���ڿγ����������������������
				if (courStudent[i].MaxContent == courStudent[i].CurStudent) {
					//�������õĻ��ԣ���ʾ���пγ�
					cout << "============================================================================================\n\n";
					cout << "�γ�ID     �γ�����                 �ڿν�ʦ    ��������   Ŀǰ��ѡ   �γ�����\n";
					ShowCourse(i);
					cout << "\n============================================================================================\n\n";
					returnStudent("�ÿγ����������������޷�ѡ�񣡣���");
				}
				//����ѡ�˿ε������������
				for (int j = 0; j < coursenum; j++) {
					if (!strcmp(ID, MyCourse[j].id)) {
						returnStudent("��ѡ�ÿΣ��޷��ظ�ѡ��");
					}
				}
				//¼�뵽������Ϣ������
				strcpy(MyCourse[coursenum].id, ID);
				strcpy(MyCourse[coursenum++].AssistantName, "NULL");
				//������Ϣ���鵼�������Ϣ�ı�
				WritePersonal();
				//¼�뵽ȫ���γ������ѡ������+1
				int x = Match(ID);
				courStudent[x].CurStudent++;
				courStudent[x].s.push_back(StudentID);
				//�γ���Ϣ����ȫ���γ��ı�
				CurrentCourseintotxt();
				returnStudent("============================================================================================\n\n					��ϲ�㣡����ѡ�γɹ�������                              \n\n============================================================================================\n\n");
			}
		}
	}
	//���������ſε����⴦��
	returnStudent("��ѡ�����ſβ����ڣ�������ѡ�񣡣���");
	return;
}
//�鿴�ҵĿγ̺���
void ScanMyCourse() {
	cout << "============================================================================================\n\n";
	cout << "�γ�ID     �γ�����                 �ڿν�ʦ    ��������   Ŀǰ��ѡ   �γ�����     ��������\n";
	if (CourseCountStudent > 0) {
		for (int i = 0; i < coursenum; i++) {
			//�����������
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
	else cout << "���޿γ̣�������\n";
	cout << "============================================================================================\n\n";
	char c = getchar();
	c = getchar();
	if (c != '~') {
		system("cls");
		ShowStudent();
	}
	return;
}
//�˿κ���
void QuitCourse() {
	ScanAidd();
	GoToxy(0, 6);
	cout << "����������Ҫ��ѡ�Ŀγ�ID��";
	char ID[5];
	cin >> ID;
	for (int i = 0; i < coursenum; i++) {
		if (!strcmp(ID, MyCourse[i].id)) {
			for (int j = 0; j < CourseCountStudent; j++) {
				if (!strcmp(ID, courStudent[j].CourseID)) {
					//��ȫ���γ��������
					courStudent[j].CurStudent--;
					//ȡ���������
					Dealquitassistant(j);
					//���̽���Ϣ����ȫ���γ��ı�
					CurrentCourseintotxt();
					//���������ú����Ը�����Ϣ�������
					DeletePersonal(i);
					//���������Ϣ�ı�
					WritePersonal();
					//���������ı�
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
			//��ʾ�Ƿ����Ҫ��
			IsEnough();
			cout << "\n��ϲ�㣬�˿γɹ�������\n��ǰ��ѡ�γ��У�\n";
			//������ԣ����û������Լ�ѡ��ʲô
			ScanMyCourse();
		}
	}
	returnStudent("��Ǹ����δѡ�����ſγ̣�����");
	return;
}

//����˿εĻ����γ�����������ҲӦ��ȡ��
void Dealquitassistant(int index) {
	for (int i = 0; i < courStudent[index].assistant.num; i++) {
		if (!strcmp(courStudent[index].assistant.a[i], StudentID)) strcpy(courStudent[index].assistant.a[i], "NULL");
	}
}

void BeAssistant() {
	readinassistant();
	cout << "�������Ӧ�γ�ID�����ƣ�";
	char tem[20];
	cin >> tem;
	if (BeinCourse(tem) < 0) {
		returnStudent("����δѡ���ſΣ�����");
	}
	int index = Match(tem);
	for (int i = 0; i < courStudent[index].assistant.num; i++) {
		if (!strcmp(courStudent[index].assistant.a[i], StudentID)) returnStudent("�����Ǹÿγ����̣������ظ�����������");
	}
	//�޸�ȫ���γ�����
	//��ȫ���γ������������Ϣд���ļ�
	strcpy(courStudent[index].assistant.a[courStudent[index].assistant.num], StudentID);
	courStudent[index].assistant.num++;
	writeassistant();
	returnStudent("�����ɹ�������");
	return;
}

//�鿴���ſε�λ��
int Match(char* s) {
	int i;
	for (i = 0; i < CourseCountStudent; i++) {
		if (!strcmp(s,courStudent[i].CourseID)||!strcmp(s,courStudent[i].CourseName)) {
			return i;
		}
	}
	if(CourseCountStudent!=0&&coursenum!=0)returnStudent("��Ǹ�����ſγ̲����ڣ�����");
	return 0;
}



//��������Ϣ�������ı�����ȫ���γ�����
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
//��������Ϣд�������ļ�
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
	cout << "������γ�ID�����ƣ�";
	char ID[30];
	cin >> ID;
	int x = Match(ID);
	//�����������
	if (!courStudent[x].Exist) returnStudent("��Ǹ���ſγ̲�����");
	for (int i = 0; i < coursenum; i++) {
		if (!strcmp(courStudent[x].CourseID, MyCourse[i].id)) goto K;
	}
	cout << "��Ǹ����δѡ����ſγ̣�����\n����ѡ��Ŀγ��У�\n";
	ScanMyCourse();
	K:	if (courStudent[x].assistant.num == 0) returnStudent("��Ǹ���ſγ���ʱû������");
	cout << "Ŀǰ���ſγ̵������У�";
	for (int i = 0; i < courStudent[x].assistant.num; i++) {
		if (strcmp(courStudent[x].assistant.a[i], "NULL"))printf("%s  ", courStudent[x].assistant.a[i]);
	}
	cout << "\n��������������ѡ��������̣�";
	char a[30];
	cin >> a;
	if (!strcmp(a, StudentID))returnStudent("��Ǹ������ѡ���Լ�Ϊ���̣�");
	for (int i = 0; i < courStudent[x].assistant.num; i++) {
		if (!strcmp(courStudent[x].assistant.a[i], a))goto L;
	}
	returnStudent("�ÿγ�û�д�����");
	L:
	for (int i = 0; i < coursenum; i++) {
		if (!strcmp(ID, MyCourse[i].id)) {
			strcpy(MyCourse[i].AssistantName,a);
			WritePersonal(); 
			returnStudent("��ϲ�㣡�����ɹ�ѡ�����̣�����");
		}
	}
	return;
}


//��������Ϣ����д�������Ϣ�ı�
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
//��ɾ���Ŀγ̴Ӹ�����Ϣ������ɾ��
void DeletePersonal(int i) {
	for (int j = i; j < coursenum-1; j++) {
		MyCourse[j] = MyCourse[j + 1];
	}
	coursenum--;
	return;
}
//�жϿγ������Ƿ��꣬������ʾ
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
	if (isnum >= 4 && notnum >= 2)cout << "��ѡ�Ŀγ������Ѿ���꣡����";
	else if (isnum < 4 && notnum >= 2) {
		cout << "����ѧԺҪ����ѡ�Ŀγ���Ŀ����꣡����";
		cout << "�Բ�" << 4 - isnum << "��רҵ��";
	}
	else if (isnum >= 4 && notnum < 2) {
		cout << "����ѧԺҪ����ѡ�Ŀγ���Ŀ����꣡����";
		cout << "�Բ�" << 2 - notnum << "��רҵ��";
	}
	else {
		cout << "����ѧԺҪ����ѡ�Ŀγ���Ŀ����꣡����";
		cout << "�Բ�" << 4 - isnum << "��רҵ�κ�"<<2-notnum<<"�ŷ�רҵ��";
	}
	return;
}
//������Ϊi�Ŀγ���Ϣ
void ShowCourse(int i) {
	printf("%-10s", courStudent[i].CourseID);
	printf("%-30s", courStudent[i].CourseName);
	printf("%-10s", courStudent[i].Teacher);
	printf("\t%d\t", courStudent[i].MaxContent);
	printf("%d\t\t", courStudent[i].CurStudent);
	if (courStudent[i].Major)printf("%-10s", "רҵ��");
	else printf("%-10s", "��רҵ��");
	return;
}

//�ж�ѧ���Ƿ��Ѿ������ſ���
int BeinCourse(char* courseID) {
	for (int i = 0; i < coursenum; i++) {
		if (!strcmp(courseID, MyCourse[i].id)) {
			return i;
		}
	}
	return -10;
}

//�쳣����֮�󷵻�ѧ��������
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
		cout << "����" << courStudent[x].CourseName << "�γ̵�����" << MyCourse[i].AssistantName << "�Ѿ��˿Σ�����"<<endl;
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
	cout << "��ǰȫ���γ�Ϊ��";
	cout << "����ǰδѡ�γ��У�\n";
	cout << "============================================================================================\n\n";
	cout << "�γ�ID     �γ�����			 �ڿν�ʦ    ��������   Ŀǰ��ѡ   �γ�����\n";
	for (int i = 0; i < CourseCountStudent; i++)
		//������ſγ̴��ڵĻ�
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
	cout << "��ǰȫ���γ�Ϊ��";
	cout << "����ǰ��ѡ�γ��У�\n";
	cout << "============================================================================================\n\n";
	cout << "�γ�ID     �γ�����			 �ڿν�ʦ    ��������   Ŀǰ��ѡ   �γ�����\n";
	for (int i = 0; i < coursenum; i++) {
		//�����������
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
	cout<< "��������ԭ�������룺\n";
	cout << "�����������룺\n";
	cout << "��ȷ�������룺\n";
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
					returnStudent("�����޸ĳɹ�������");
				}
				else returnStudent("��Ǹ�������������벻һ�£�����");
			}
			else returnStudent("��Ǹ��ԭ�����������");
		}
	}
	return;
}