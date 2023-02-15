#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <WinSock2.h>
#include <mysql.h>
#include <Windows.h>
#include <time.h>
#include <stdio.h>

using namespace std;

//包含附加依赖项，也可以在工程--属性里面设置
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"libmysql.lib")

#include <QTime>
#include <QDateTime>


class Ticket
{
public:
    QString no, departure, destination;
    int day, price;
    QTime time_leave, time_arrive;
    Ticket *next;
};

class Order:public Ticket
{
public:
    QString order, name, id;
    QDate day_leave;
    QDateTime time;
    int num;
    Order *next;
};

class Customer
{
public:
    QString name, id, username, password, telephone;
    int discount_type;
    Order* orders;
    Customer *next;
};


MYSQL mysql; //mysql连接
MYSQL_FIELD* fd;  //字段列数组
char field[32][32];  //存字段名二维数组
MYSQL_RES* res; //这个结构代表返回行的一个查询结果集
MYSQL_ROW column, row; //一个行数据的类型安全(type-safe)的表示，表示数据行的列
char query[150]; //查询语句
char abc[] = "'";
char def[] = ":";
char table[10];//需要的表
char t[40];//存放获取的本地时间
int field_number = 0;//初始化表的字段数
char* test[10];//测试select语句提取的数据是否能顺利存入常规字符数组并显示，因为之前使用的column数据类型并不确定（应该保留表中）
//如果可以找到c++中对应mysql中的date 等类型便可使用存储后的链表操作，但如若不行便只好直接在mysql存储下（即column）进行比较
//显示问题是可以解决的


bool ConnectDatabase();     //函数声明
void FreeConnect();
bool read();  //查询1
bool search();  //查询2
bool input();
bool dlt();
bool piao();
void mainmenu();
int main(int argc, char** argv)
{
    int m;
    int k = 1;
    ConnectDatabase();
    mysql_query(&mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
    mainmenu();
    while (k == 1)
    {
        printf("\n");
        printf(" 请选择功能：");
        cin >> m;
        switch (m)
        {
        case  1:input(); break;//录入信息
        case  2:read(); break;//浏览信息
        case  3:search(); break;// 查询信息
        case  4:dlt(); break;//删除信息
        case  5:piao(); break;//售票和退票(此功能固定，与进入哪个表无关)
        case  6: k = 0; break;//退出系统
        }
    }
    FreeConnect();
    system("pause");
    return 0;
}
//连接数据库
bool ConnectDatabase()
{
    //初始化mysql
    mysql_init(&mysql);  //连接mysql，数据库

    //返回false则连接失败，返回true则连接成功
    if (!(mysql_real_connect(&mysql, "localhost", "root", "hclz", "db1", 3306, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号，可以先写成参数再传进去
    {
        printf("Error connecting to database:%s\n", mysql_error(&mysql));
        return false;
    }
    else
    {
        printf("Connected  success\n");
        return true;
    }
}
void mainmenu()
{
    printf("需要进入的表:");
    cin >> table;
    if (strcmp(table, "用户") == 0)field_number = 6;
    else field_number = 7;//由于表只有三个，直接手动设更方便,也可用num_field接口获取;
    cout << "字段数："<<field_number << endl;
    cout << "Welcome" << endl;
    cout << "||            1.录入信息              ||" << endl;
    cout << "||            2.浏览信息              ||" << endl;
    cout << "||            3.查询信息              ||" << endl;
    cout << "||            4.删除信息              ||" << endl;
    cout << "||            5.售票和退票            ||" << endl;
    cout << "||            6.退出系统              ||" << endl;
}

//释放资源
void FreeConnect()
{
    mysql_free_result(res);
    mysql_close(&mysql);
}
//数据库操作
//录入数据
bool input()
{
    mysql_query(&mysql, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
    sprintf(query, "insert into t1 values ('G7753','同江','辉县','2:14:27','0:17:22',0,187)");  //可以想办法实现手动在控制台手动输入指令//,3,20,10,'NULL'
    mysql_query(&mysql, query);      //执行SQL语句
    if (mysql_query == 0)  printf("Insert is failure ,error is :\n%s\n", mysql_error(&mysql));
    else printf(" Insert success\n");
    return true;
}
//浏览数据
bool read()
{
    sprintf(query, "select * from ");
    strcat(query, table);
    mysql_query(&mysql, query);

    //获取结果集
    if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集
    {
        printf("Couldn't get result from %s\n", mysql_error(&mysql));
        return false;
    }
    char* str_field[32];  //定义一个字符串数组存储字段信息
    for (int i = 0; i < field_number; i++)   //在已知字段数量的情况下获取字段名
    {
        str_field[i] = mysql_fetch_field(res)->name;
    }
    for (int i = 0; i < field_number; i++)   //打印字段名
        printf("%10s\t", str_field[i]);
    printf("\n");

    while (column = mysql_fetch_row(res))   //在已知字段数量情况下，获取并打印下一行（重中之重）
    {
        for (int i = 0; i < field_number; i++)
            printf("%10s\t", column[i]);//这一步可以不用打印出来，
        printf("\n");
    }
    return true;
}
//查询数据
bool search()
{
        char key[10];
        char info[30];
        int y;
        printf(" 请输入查询关键字：\n");
        cin >> key;
        printf("请输入对应信息：\n");
        cin >> info;
        sprintf(query, "select * from ");
        strcat(query, table);
        strcat(query, " where ");
        strcat(query, key);
        strcat(query, "=");
        strcat(query, abc);
        strcat(query, info);
        strcat(query, abc);
        //cout << query;
        mysql_query(&mysql, query);    //执行SQL语句

        //获取结果集
       if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集
        {
            printf("Couldn't get result from %s\n", mysql_error(&mysql));
            return false;
        }

        for (int i = 0; fd = mysql_fetch_field(res); i++)  //获取字段名
            strcpy(field[i], fd->name);
        for (int i = 0; i < field_number; i++)  //打印字段
            printf("%10s\t", field[i]);
        printf("\n");
        column = mysql_fetch_row(res); //在已知字段数量情况下，获取并打印下一行(先打一行测试test能否存储,之后记得补回while)
        for (int i = 0; i < field_number; i++)
        {
            test[i] = column[i];
            printf("%10s\t", test[i]);
        }
            printf("success!");//已成功。只需新建一个临时用于显示的链表，每次循环将指针后移一位，最后按需要的格式输出即可
    printf("\n");
    printf("  1 继续查询；2 返回主界面\n");
    printf(" 请输入您的操作： ");
    cin >> y;
    if (y == 1)
    {
        search();
    }
    else if (y == 2)
    {
        mainmenu();
    }
    return true;
}
//删除信息
bool dlt()
{
    char key[10];
    char info[30];
    cout << "请输入主键名称:" << endl;
    cin >> key;
    cout << "请输入需要删除记录的主键信息" << endl;
    cin >> info;
    sprintf(query, "delete from ");
    strcat(query, table);
    strcat(query, " where ");
    strcat(query, key);
    strcat(query, "=");
    strcat(query, abc);
    strcat(query, info);
    strcat(query, abc);
    mysql_query(&mysql, query);
    return true;
}
//售票和退票
bool piao()
{
    struct tm* local;
    time_t t;
    t = time(NULL);
    local = localtime(&t);//获取当前系统时间
    char s[1000];
    int num = local->tm_hour;
    int num1 = local->tm_min;
    int num2 = local->tm_sec;
    char str1[25], str2[25],str3[25];
    sprintf(str1, "%d", num);
    sprintf(str2, "%d", num1);
    sprintf(str3, "%d", num2);


    strcpy(s, str1);
    strcat(s, def);
    strcat(s, str2);
    strcat(s, def);
    strcat(s, str3);
    cout << endl;
    printf(" 当前系统时间为：%10s\t\n", s);//将当前时间存入s便于之后对比
    cout << endl;

    int y;
    int m, a, b;
    char n[5];
    char k[5];
    char cc[100] = " where 班次='";
    printf(" 请选择操作：1 售票；2 退票");
    cout << endl;
    printf(" 请输入： ");
    cin >> m;

    if (m == 1)//售票
    {
        printf(" 请输入您要购买的车票班次：  ");
        cin >> k;
        sprintf(query, "select * from 车票 where 车次='");
        strcat(query, k);
        strcat(query, abc);
        mysql_query(&mysql, query);

        //获取结果集
        if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集
        {
            printf("Couldn't get result from %s\n", mysql_error(&mysql));
            return false;
        }

        for (int i = 0; fd = mysql_fetch_field(res); i++)  //获取字段名
            strcpy(field[i], fd->name);
        column = mysql_fetch_row(res);
        if (s < column[3])//检测是否到达始发时间
        {
            printf("\n");
            printf("购票成功\n");
            printf("\n");
            for (int i = 0; i < field_number; i++)  //打印字段
                printf("%10s\t", field[i]);
            printf("\n");
            sprintf(query, "insert into 订单 values()"); //不知道这里订单编号如何生成,暂留空
            //strcat(query, abc);
            //strcat(query, cc);
           // strcat(query, k);
            //strcat(query, abc);
            mysql_query(&mysql, query);
        }
        else printf("该车已发出，购票失败");
    }
    else if (m == 2)//退票
    {
        printf(" 请输入您要退订的车票班次：  ");
        cin >> n;

        //获取结果集
        if (!(res = mysql_store_result(&mysql)))
        {
            printf("Couldn't get result from %s\n", mysql_error(&mysql));
            return false;
        }

        for (int i = 0; fd = mysql_fetch_field(res); i++)  //获取字段名
            strcpy(field[i], fd->name);
        int j = mysql_num_fields(res);  // 获取列数


        column = mysql_fetch_row(res);
        if (s < column[3])
        {
            printf("\n");
            printf("退票成功\n");
            printf("\n");
            sprintf(query, "delete from 订单 where 车次='");
            strcat(query, n);
            strcat(query, abc);
            mysql_query(&mysql, query);
        }
        else printf("该车已发出，退票失败");
    }
    printf("\n");
    printf("  1 继续售票/退票；2 返回主界面\n");
    printf(" 请输入您的操作： ");
    cin >> y;
    if (y == 1)
    {
        piao();
    }
    else if (y == 2)
    {
        mainmenu();
    }
}
