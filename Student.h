#ifndef _STUDENT_H
#define _STUDENT_H


#include<iostream>
#include"Administer.h"

using namespace std;
//�ҵĿγ̽ṹ�壬���øýṹ������洢�ҵĿγ�
struct MyCourses {
	char id[5];
	char AssistantName[30];
};


//��ѧ��������Ϣ¼�������Ϣ����
void WriteStudent(char* studentID);
//1.ע�ắ�� 2.ע��ɹ��������ݺ��� 3.���������ļ�����
void RegisterStudent();
void SucceedRegisterStudent(char* UserName,char* Password);
void Createfile(char* fname);
//ѧ���������溯��
void ShowStudent();
//�鿴ȫ���γ̺���
void ScanCourse();
//ѡ�κ���
void SelectCourse();
//�鿴�ҵĿγ̺���
void ScanMyCourse();
//�˿κ���
void QuitCourse();
//ȡ���������
void Dealquitassistant(int index);
//�������̺���
void BeAssistant();
//ͬ����Ա��Match2
int Match(char* s);
//����������Ϣ����
void readinassistant();
//��������Ϣд���ı�����
void writeassistant();
//��ѡ���̺���
void SelectAssistant();
//��������Ϣд������ı�����
void WritePersonal();
//ɾ���Լ���Ӧ�γ̺���
void DeletePersonal(int i);
//�ж�ѡ���Ƿ����Ҫ��
void IsEnough();
//չʾ�����γ�
void ShowCourse(int i);
//�ж��Լ��Ƿ���ĳ�γ���
int BeinCourse(char* courseID);
//�������������ʾ������ѧ����������
void returnStudent(const char* word);
//��������Ƿ��˿�
void checkassistant();
//���ĳ�ſ��Ƿ�������
bool checkhave(int i);

void changepwd();

void ScanAids();
void ScanAidd();


#endif // !_STUDENT_H