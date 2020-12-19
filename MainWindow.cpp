#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include <conio.h>
#include"MainWindow.h"
#include"Administer.h"
#include"Student.h"

using namespace std;

//�洢ѧ�����˻����룬����ѧ����¼
student Stu[40];
//һ��Ҫ������û�������ȷ��������룬��֤ѧ����ʹ�ô�ID������
char* StudentID;

int studentnum;

//����Ա��Ψһ�û��������룬���ڹ���Ա��¼
const char AdministerCorrectID[10] = "Admin";
const char AdministerCorrectPassword[10] = "admin";

extern Course courStudent[30];
extern int CourseCountStudent;

void ShowMainWindow() {
    showtongzhi();
    readcurrent();
    //��Ϊ�����ļ�����ȫ�ֵģ������ڳ����ִ��ʱ�ͽ��ж�ȡ
    readinassistant();
    //������ѧ����Ϣ
    studentnum = StudentPassword();
    dealstudent();
    cout << "============================================================================\n\n";
    cout << "        1.ѧ����½         2.ѧ��ע��        3.����Ա��½        4.����    \n\n";
    cout << "============================================================================\n\n\n";
    cout << "�������������";
    char bottom;
    cin >> bottom;
    switch (bottom){
    case '1': GoStudentLogin(); break;
    case '2':system("cls"); RegisterStudent(); break;
    case '3':GoAdminiserLogin(); break;
    case '4':about(); break;
    default: returnMainWindow("��Ǹ�޴˲���,�����²���\n"); break;
    }
    return;
 }

/**************************************************************
���������������ã���������ѧ����½����
***************************************************************/
//����1 ��ʾ����
void GoStudentLogin(){
    //�ȴ��ļ��е���ѧ��ID������
    studentnum=StudentPassword();
    cout << "��������ѧ��ID��\n";
    cout << "��������ѧ�����룺";
    char StudentPassword[20];
    GoToxy(8, 8);
    StudentID = new char[30];
    cin >> StudentID;
    GoToxy(9, 9);
    strcpy(StudentPassword,getpwd());
    if (Succeedlogin(StudentID, StudentPassword, studentnum)) {
        //�ڴ˵���ѧ����Ϣ
        WriteStudent(StudentID);
        returnStudent("�ɹ���¼������\n");
    }
    return;
}
//����2 �ļ���ȡ����
//��student.txt��ѧ����ID�����붼�����
int StudentPassword() {
    int count = 0;
    FILE* pfile = fopen("student.txt", "r+t");
    if (pfile == NULL) {
        return count=0;
    }
    pfile = fopen("student.txt", "r+t");
    while (!feof(pfile)) {
        fscanf(pfile, "%[^','],%s", &Stu[count].StudentID, &Stu[count].StudentPassword);
        fscanf(pfile, "\n");
        count++;
    }
    fclose(pfile);
    return count;
}
//����3 ������
//������ĺ��������õģ������ж��Ƿ�ɹ���¼���������ִ
bool Succeedlogin(char* ID, char* password, int num) {
    int countID = 0;
    for (int i = 0; i < num; i++) {
        if (!(strcmp(ID, Stu[i].StudentID) || strcmp(password, Stu[i].StudentPassword))) {
            return true;
        }
        if (!strcmp(ID, Stu[i].StudentID))countID++;
    }
    if (countID > 0)returnMainWindow("***********************������������µ�¼������***********************");
    else returnMainWindow("***********************��ѧ��δע�ᣬ��ע������µ�¼������***********************");
}

/*****************************************
����һ�������������������Ա��½����
******************************************/
//��Ϊ����Ա���˻������붼��Ψһ��
//����ֻ��Ҫ����һ������
//����Ա��½
void GoAdminiserLogin() {
    cout << "�����������ԱID��\n";
    cout << "�����������Ա���룺";
    char AdministerID[20];
    char AdministerPassword[20];
    GoToxy(9, 8);
    cin >> AdministerID;
    GoToxy(10, 9);
    strcpy(AdministerPassword,getpwd());
    //�жϹ���Ա�Ƿ�ɹ���¼
    if (!(strcmp(AdministerID, AdministerCorrectID) || strcmp(AdministerPassword, AdministerCorrectPassword)))
        returnAdminister("***********************����Ա��ݵ�½�ɹ�������***********************");
    //�����
    //�ж�������������û�������
    else {
        if (!strcmp(AdministerID, AdministerCorrectID))
            returnMainWindow("***********************������������µ�¼������***********************");
        else
            returnMainWindow("***********************�û������������µ�¼������***********************");
    }
    return;
}

/*************************************
���������������ڴ���һЩ��ʾ����
**************************************/
//������Ƶ���x,y�����ĺ���
//�������˺�����ʱ���ȽϺÿ�
void GoToxy(int x, int y){
    COORD pos;
    pos.X = 2 * x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//��������������Ǹ�����ʾ��������������
void returnMainWindow(const char* word) {
    if (word != NULL)cout << word;
    Sleep(1000);
    system("cls");
    ShowMainWindow();
}

char* getpwd() {
    char* pwd=new char[50] ;
    int i = 0;
    do{
        pwd[i] = _getch();
        if (pwd[i] == '\r')
            break;
        if (pwd[i] == '\b')
        {
            if (i == 0)
            {
                printf("\a");
                continue;
            }
            i = i - 1;
            printf("\b");
        }
        else
        {
            i = i + 1;
            printf("*");
        }
    } while (pwd[i] != '\n' && i < 40);
    pwd[i] = '\0';
    printf("\n");
    return pwd;
}

void about() {
    setcolor(FOREGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED );
    cout << "********************************���ڱ�����********************************\n";
    cout << "==========================================================================\n";
    cout << "               ��ӭʹ���Ͼ���ѧ�����ϵѧ��ѡ�ι���ϵͳ������             \n";
    cout << "==========================================================================\n";
    cout << "                 �ڱ������У�������ģ���ѧ��ѡ��ϵͳ                     \n";
    cout << "                  �������Ϊ����Ա�˺�ѧ������������                      \n";
    cout << "�ڹ���Ա�ˣ������Կ��ƿγ̵���ɾ���޸ģ��Լ��鿴ȫ���γ���Ϣ������ȫ���γ�\n";
    cout << "��ѧ���ˣ�������ע�����Լ����˺ţ���Ϊ�Լ�ѡ����ʵĿγ̣���֧�ֶ��˺ŵ�¼\n";
    cout << "       �����ǵ�һ�γ��ԣ��кܶ಻�㣬���������Ҳ����ָ��������       \n";
    cout << "                               лл������                                 \n";
    cout << "**************************************************************************\n";
    char c = getchar();
    c = getchar();
    if (c != '~') {
        setcolor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        system("cls");
        ShowMainWindow();
    }
    return;
}

void setcolor(int a)//��ɫ����
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void showtongzhi() {
    FILE* pf = fopen("tongzhi.txt", "r");
    if (pf == NULL)return;
    char s[200];
    fscanf(pf, "%s", s);
    if (!strcmp(s, "c"))return;
    GoToxy(0, 14);
    setcolor( BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    cout << s;
    setcolor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    GoToxy(0, 0);
    return;
}