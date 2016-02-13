#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define getch() _getch()

#define OK 1
#define ERROR 0
typedef int status;

#define HASHSIZE 10007
#define MAXFEE (2147483647)
#define NAMESIZE 80

#define NOSTATION -1
#define NOROUTE -1

bool modified = false;

int routeTotal;
int stationTotal;

//存储路线信息的结构体
typedef struct {
    int id;
    char name[NAMESIZE];
    char startTime[10];
    char endTime[10];
    float price;
    int stationNum;
    int *stations;
} rInfo;

typedef struct _rHash{
    char name[NAMESIZE];
    int id;
    _rHash * next;
} rHash;

//存储站点信息的结构体
typedef struct {
    char name[NAMESIZE];
    int routeNum;
    int routes[60];
    int index[60];
} sInfo;

typedef struct _sHash{
    char name[NAMESIZE];
    int id;
    _sHash * next;
} sHash;

int *distMat;       //该邻接矩阵保存站点距离

unsigned hash(char *str);

status loadStationData(char *filename);
status loadRouteData(char *filename);
status initDistMat(char *filename);

status modifyRoute(void);
status saveRoute(char *filename);

rInfo *routeInfo;                   //存储路线信息
rHash routeNameId[HASHSIZE];      //存储路线名称与序号对应信息的哈希表
sInfo *stationInfo;                 //存储站点信息
sHash stationNameId[HASHSIZE];    //存储站点名称与序号对应信息的哈希表

struct sortStruct
{
    bool sorted;
    int *arr;
} sortRoute, sortStation;

int getRouteIdbyName(char *name);
int getStationIdbyName(char *name);

int findCrossStation(int route1, int route2);

status sortResult(int type);
status inquireSpecificRoute(void);      //查询指定线路详情
status inquireSpecificStation(void);    //查询途经某一位置的所有公交线路
status shortestDist(void);              //指定起点与终点，推荐最短路程乘车方案
status leastTransfer(void);             //指定起点与终点，推荐最少换乘乘车方案

void quickSort(int *arr, int low, int high, int type);
int partitionbyRoute(int *arr, int low, int high);
int partitionbyStation(int *arr, int low, int high);

int distSPFA(int start, int end, int *stations, int &stationNum);
float showResultbyStations(int *stations, int stationNum);

int transDijkstra(int start, int end, int *stations, int *routes, int &routeNum);
float showResultbyRoutes(int *stations, int *routes, int routeNum);
bool emptyQ(bool *Q, int num);
int searchMin(int *arr, bool *Q, int num, int &index);