#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

//�洢ѧ��ID�����룬��¼ʱ��
struct student {
	char StudentID[30];
	char StudentPassword[30];
};
//չʾ������
void ShowMainWindow();
//ѧ����½����
void GoStudentLogin();
//����Ա��½����
void GoAdminiserLogin();
//�ƶ���꺯�����ѹ���Ƶ�(x,y)��
void GoToxy(int x, int y);
//��ѧ����ID�����뵼������
int StudentPassword();
//�ж�ѧ���Ƿ�ɹ���¼
bool Succeedlogin(char* ID,char* password,int num);
//����ʱ������ʾ��������������
void returnMainWindow(const char* word);
//������������
char* getpwd();
//�����ڡ���������ʾһЩ��Ϣ
void about();
//������ɫ
void setcolor(int a);

void showtongzhi();


#endif // !_MAINWINDOW_H


