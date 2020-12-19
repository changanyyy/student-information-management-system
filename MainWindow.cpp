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

//存储学生的账户密码，用于学生登录
student Stu[40];
//一会要输入的用户名，正确才允许进入，保证学生端使用此ID不出错
char* StudentID;

int studentnum;

//管理员的唯一用户名和密码，用于管理员登录
const char AdministerCorrectID[10] = "Admin";
const char AdministerCorrectPassword[10] = "admin";

extern Course courStudent[30];
extern int CourseCountStudent;

void ShowMainWindow() {
    showtongzhi();
    readcurrent();
    //因为助教文件属于全局的，所以在程序刚执行时就进行读取
    readinassistant();
    //读进来学生信息
    studentnum = StudentPassword();
    dealstudent();
    cout << "============================================================================\n\n";
    cout << "        1.学生登陆         2.学生注册        3.管理员登陆        4.关于    \n\n";
    cout << "============================================================================\n\n\n";
    cout << "请您输入操作：";
    char bottom;
    cin >> bottom;
    switch (bottom){
    case '1': GoStudentLogin(); break;
    case '2':system("cls"); RegisterStudent(); break;
    case '3':GoAdminiserLogin(); break;
    case '4':about(); break;
    default: returnMainWindow("抱歉无此操作,请重新操作\n"); break;
    }
    return;
 }

/**************************************************************
以下三个函数连用，用来处理学生登陆环节
***************************************************************/
//函数1 显示函数
void GoStudentLogin(){
    //先从文件中导入学生ID和密码
    studentnum=StudentPassword();
    cout << "请您输入学生ID：\n";
    cout << "请您输入学生密码：";
    char StudentPassword[20];
    GoToxy(8, 8);
    StudentID = new char[30];
    cin >> StudentID;
    GoToxy(9, 9);
    strcpy(StudentPassword,getpwd());
    if (Succeedlogin(StudentID, StudentPassword, studentnum)) {
        //在此导入学生信息
        WriteStudent(StudentID);
        returnStudent("成功登录！！！\n");
    }
    return;
}
//函数2 文件读取函数
//把student.txt的学生的ID和密码都存进来
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
//函数3 处理函数
//和上面的函数是连用的，用来判断是否成功登录，并给予回执
bool Succeedlogin(char* ID, char* password, int num) {
    int countID = 0;
    for (int i = 0; i < num; i++) {
        if (!(strcmp(ID, Stu[i].StudentID) || strcmp(password, Stu[i].StudentPassword))) {
            return true;
        }
        if (!strcmp(ID, Stu[i].StudentID))countID++;
    }
    if (countID > 0)returnMainWindow("***********************密码错误，请重新登录！！！***********************");
    else returnMainWindow("***********************该学生未注册，请注册或重新登录！！！***********************");
}

/*****************************************
以下一个函数，用来处理管理员登陆环节
******************************************/
//因为管理员的账户和密码都是唯一的
//所以只需要设置一个函数
//管理员登陆
void GoAdminiserLogin() {
    cout << "请您输入管理员ID：\n";
    cout << "请您输入管理员密码：";
    char AdministerID[20];
    char AdministerPassword[20];
    GoToxy(9, 8);
    cin >> AdministerID;
    GoToxy(10, 9);
    strcpy(AdministerPassword,getpwd());
    //判断管理员是否成功登录
    if (!(strcmp(AdministerID, AdministerCorrectID) || strcmp(AdministerPassword, AdministerCorrectPassword)))
        returnAdminister("***********************管理员身份登陆成功！！！***********************");
    //检错功能
    //判断是密码错误还是用户名错误
    else {
        if (!strcmp(AdministerID, AdministerCorrectID))
            returnMainWindow("***********************密码错误，请重新登录！！！***********************");
        else
            returnMainWindow("***********************用户名错误，请重新登录！！！***********************");
    }
    return;
}

/*************************************
下面两个函数用于处理一些显示问题
**************************************/
//将光标移到（x,y）处的函数
//在输入账号密码时候会比较好看
void GoToxy(int x, int y){
    COORD pos;
    pos.X = 2 * x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//在遇到特殊情况是给予提示，并返回主窗口
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
    cout << "********************************关于本程序********************************\n";
    cout << "==========================================================================\n";
    cout << "               欢迎使用南京大学计算机系学生选课管理系统！！！             \n";
    cout << "==========================================================================\n";
    cout << "                 在本程序中，您可以模拟大学的选课系统                     \n";
    cout << "                  本程序分为管理员端和学生端两个部分                      \n";
    cout << "在管理员端，您可以控制课程的增删和修改，以及查看全部课程信息，管理全部课程\n";
    cout << "在学生端，您可以注册您自己的账号，并为自己选择合适的课程，并支持多账号登录\n";
    cout << "       由于是第一次尝试，有很多不足，请多多包涵，也请多多指正！！！       \n";
    cout << "                               谢谢！！！                                 \n";
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

void setcolor(int a)//颜色函数
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