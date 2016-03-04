#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define getch() _getch()

typedef int status;
#define OK 1
#define ERROR 0

#define HASHSIZE 10007          //哈希表长度
#define MAXFEE (2147483647)     //无穷大
#define NAMESIZE 80             //名称长度

#define NOSTATION -1    //无此站点
#define NOROUTE -1      //无此路线

//存储路线信息的结构体
typedef struct {
    int id;
    char name[NAMESIZE];
    char startTime[10];     //起始时间
    char endTime[10];       //结束时间
    float price;
    int stationNum;         //站点总数
    int *stations;          //站点序列
} rInfo;

//路线信息的hash结构体
typedef struct _rHash{
    char name[NAMESIZE];
    int id;
    _rHash * next;
} rHash;

//存储站点信息的结构体
typedef struct {
    char name[NAMESIZE];
    int routeNum;
    int routes[60];     //路线序列
    int index[60];      //在路线的第几站
} sInfo;

//站点信息的hash结构体
typedef struct _sHash{
    char name[NAMESIZE];
    int id;
    _sHash * next;
} sHash;

//两种排序的结构体
struct sortStruct
{
    bool sorted;    //记录是否已排序
    int *arr;       //记录排序后的站点序列
} sortRoute, sortStation;

bool modified = false;  //是否修改了数据，若修改过，则退出时询问是否保存

int routeTotal;     //路线总数
int stationTotal;   //站点总数

int *distMat;       //该邻接矩阵保存站点距离

rInfo *routeInfo;                   //存储路线信息
rHash routeNameId[HASHSIZE];      //存储路线名称与序号对应信息的哈希表
sInfo *stationInfo;                 //存储站点信息
sHash stationNameId[HASHSIZE];    //存储站点名称与序号对应信息的哈希表

unsigned hash(char *str);
int getRouteIdbyName(char *name);
int getStationIdbyName(char *name);

status loadStationData(char *filename);
status loadRouteData(char *filename);
status initDistMat(char *filename);

status modifyRoute(void);

status sortResult(int type);
void quickSort(int *arr, int low, int high, int type);
int partitionbyRoute(int *arr, int low, int high);
int partitionbyStation(int *arr, int low, int high);

status inquireSpecificRoute(void);
status inquireSpecificStation(void);

status shortestDist(void);
int distSPFA(int start, int end, int *stations, int &stationNum);
float showResultbyStations(int *stations, int stationNum);

status leastTransfer(void);
int transDijkstra(int start, int end, int *stations, int *routes, int &routeNum);
float showResultbyRoutes(int *stations, int *routes, int routeNum);
bool emptyQ(bool *Q, int num);
int searchMin(int *arr, bool *Q, int num, int &index);

status saveRoute(char *filename);