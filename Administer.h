#ifndef _ADMINISTER_H
#define _ADMINISTER_H
#include"Student.h"
#include<vector>

//���̽ṹ��
struct Assistant {
	char** a;
	int num;
};

//�γ̽ṹ��
struct Course {
	char CourseID[5];//�γ�ID
	char CourseName[30];//�γ�����
	char Teacher[20];//�ον�ʦ����
	int MaxContent;//�����������
	int CurStudent;//��ǰѧ����Ŀ
	bool Major;//�Ƿ���רҵ��
	bool Exist;//�ÿγ̴���״̬���Ƿ񱻹���Աɾ����
	Assistant assistant;//���е�����
	vector<char*> s;//��ѡ�γ�ѧ��
};



//չʾ����Ա�˵�������
void ShowAdminister();
//ע������
void Logout();
//�ѿγ���Ϣ����γ�����
void PutinCourseInformation();
//�鿴ȫ���γ���Ϣ
void ScanAllCourseInformation();

void ScanAid();

//��ӿγ�
void AddCourse();
//ɾ���γ�
void DeleteCourse();
//�޸Ŀγ�
void ChangeCourse();
//�鿴�ض��γ�
void ScanSpecificCourse();
//���γ̴����鵼�뵽�ı�
void CurrentCourseintotxt();
//��ȡ��ǰ�γ��ı�
void readcurrent();
//����ʱ������ʾ�����ع���Ա��������
void returnAdminister(const char* word);
//�ж�ĳ�ſ���������λ��
int Match2(char* s);
//��ÿ�ε�¼ʱ����ȡÿ���γ̵�ѧ������֤��Ϣһ��
void dealstudent();


void tongzhi();

#endif // !_ADMINISTER_H
