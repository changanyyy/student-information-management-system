#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

//存储学生ID和密码，登录时用
struct student {
	char StudentID[30];
	char StudentPassword[30];
};
//展示主窗口
void ShowMainWindow();
//学生登陆界面
void GoStudentLogin();
//管理员登陆界面
void GoAdminiserLogin();
//移动光标函数，把光标移到(x,y)处
void GoToxy(int x, int y);
//把学生的ID和密码导入数组
int StudentPassword();
//判断学生是否成功登录
bool Succeedlogin(char* ID,char* password,int num);
//错误时给予提示，并返回主窗口
void returnMainWindow(const char* word);
//加密输入密码
char* getpwd();
//“关于”函数，显示一些信息
void about();
//设置颜色
void setcolor(int a);

void showtongzhi();


#endif // !_MAINWINDOW_H


