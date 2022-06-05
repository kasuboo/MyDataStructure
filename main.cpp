#include<stdio.h>
#include<stdlib.h>
#include <graphics.h> 
#include <conio.h>
#include<string.h>
#include<time.h>
#define width 800 //窗口大小
#define height 600 
int rec1[] = { 20, 100,480,580 }; //绘制矩形框显示排序
int rec2[] = { 200,20,780,80 }; //显示数组
int rec3[] = { 650,100,750,150 }; //开始按钮
int array[100]; //要排序的数组
char tempArray[100]; //用于实时显示排序
char s[100];
int length; //数组长度
int num = 0; //选择的排序的下标
void  ShellSort(int* array, int length) //希尔排序
{
    int gap = length / 2; //增量
    while (gap > 1) //当增量不为1时循环执行排序
    {
        gap = gap / 2; //每次增量折半
        for (int i = 0; i < length - gap; i++)
        {
            int min = i; //当前组内最小下标
            int max = min + gap;
            while (min >= 0) //当最小下标大于等于0时继续执行排序
            {
                if (array[max] < array[min]) //组内后一个比前一个小，交换
                {
                    int temp = array[min];
                    array[min] = array[max];
                    array[max] = temp;
                }
                else //无需交换，执行下一次
                    break;
            }
        }
    }
}
void InSertSort(int* array, int length) //直接插入排序
{
    for (int i = 1; i < length; i++) //从第二个数开始排
    {
        int temp = array[i];
        int j = i - 1; //前i-1个数都是有序序列，记录下标
        while (j >= 0 && array[j] > temp)
        {
            array[j + 1] = array[j]; //数据后移
            j--;
        }
        array[j + 1] = temp; //移到正确的位置
    }
}
void HalfInsertSort(int* array, int length) //折半插入排序
{
    int low, high, mid;
    int key;
    for (int i = 1; i < length; i++)
    {
        key = array[i]; //要查找的值
        low = 0;
        high = i - 1;
        while (low <= high) //折半查找
        {
            mid = (low + high) / 2;
            if (array[mid] >= key)
                high = mid - 1; //查找范围缩小到左序列
            else if (array[mid] < key)
                low = mid + 1; //查找范围在右序列
        }
        for (int j = i - 1; j >= high + 1; j--)
        {
            array[j + 1] = array[j]; //high之后的数据整体后移一位
        }
        array[high + 1] = key;
    }
}
void QuickSort(int* array, int low, int high) //快速排序
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = array[low];
        while (i < j)
        {
            while (i < j && array[j] >= k)
            {
                j--;
            }
            if (i < j)
            {
                array[i++] = array[j];
            }
            while (i < j && array[i] < k)
            {
                i++;
            }
            if (i < j)
            {
                array[j--] = array[i];
            }
        }
        array[i] = k;
        QuickSort(array, low, i - 1);//递归
        QuickSort(array, i + 1, high);
    }
}
void BubbleSort(int* array, int length) //冒泡排序
{
    int i, j, temp;
    for (i = 0; i < length - 1; i++)
        for (j = 0; j < length - 1 - i; j++)
            if (array[j] > array[j + 1]) 
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }

}
void number(char* s) //显示数组
{
    setbkmode(TRANSPARENT);//设置透明文字
    settextcolor(BLACK);//设置字体颜色
    outtextxy(180, 45, _T(s));
    outtextxy(180, 65, _T(tempArray));
}
void show(int length,int array[]) //绘制页面
{
    cleardevice();
    setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1.5);
    setlinecolor(BLACK);
    rectangle(rec1[0], rec1[1], rec1[2], rec1[3]); //绘制排序框
    setbkmode(TRANSPARENT);//设置透明文字
    settextcolor(BLACK);//设置字体颜色
    settextstyle(20, 0, _T("宋体"));//设置字体大小、样式
    outtextxy(20, 45, "需要排序的数组:");
    //outtextxy(20, 65, "正在排序:");
    //显示当前排序情况
    if (num == 1) //num是程序开始时输入的序号
        outtextxy(20,20, "当前的选择是希尔排序");
    else if (num == 2)
        outtextxy(20, 20, "当前的选择是直接插入排序");
    else if (num == 3)
        outtextxy(20, 20, "当前的选择是折半插入排序");
    else if (num == 4)
        outtextxy(20, 20, "当前的选择是快速排序");
    else if (num == 5)
        outtextxy(20, 20, "当前的选择是冒泡排序");    

    number(s); //显示数组
    //绘制矩形
    for (int i = 0; i < length; i++)
    {
        setfillcolor(LIGHTBLUE);
        setlinecolor(BLACK);
        fillrectangle(40 + 40 * i, 600 - array[i] * 10, 80 + 40 * i, 580);
    }
    FlushBatchDraw();//开始批量绘制
    Sleep(50);   
}
void startup() //初始函数
{
    initgraph(width, height);
    setbkcolor(RGB(250, 250, 250));//背景色
    cleardevice(); //用背景色清空屏幕
    BeginBatchDraw();//开始批量绘制
}
int toInt(char* ss) //将输入的字符串转为整形数组
{
    char* p = NULL, * p1 = NULL;
    int i = 0;
    p = strtok_s(ss, " ", &p1); //按照空格分隔字符串,返回分隔后第一个字符串指针
    while (p)
    {
        array[i] = atoi(p); //转换为整形存到整数数组
        p = strtok_s(NULL, " ", &p1); //第二次调用起参数要设置为NULL
        i++;
    }
    return i;
}
void updata(int length,int num) 
{
    char input = _getch();//获得摁键
    if (kbhit())
    {
        if (input == 'a') //摁下a键开始排序
        {
            if (num == 1)
                ShellSort(array, length);
            else if (num == 2)
                InSertSort(array, length);
            else if (num == 3)
                HalfInsertSort(array, length);
            else if (num == 5)
                BubbleSort(array, length);
            else if (num == 4)
                QuickSort(array, 0, length-1); //?参数我没搞懂
        }
    }
}
int main(void)
{
    printf("请输入要排序的数组:");
    gets_s(s);
    printf("根据输入的数组，推荐的排序方法为：****\n");
    printf("请选择排序方法:\n1、希尔排序   2、直接插入排序   3、折半插入排序\n4、快速排序   5、冒泡排序\n0、重新输入\n");
    scanf_s("%d", &num);
        
   char ss[50] = "";
   strcat(ss, s); //复制s字符串到ss
   length = toInt(ss); //将字符串转为整形数组,并获得数组长度
   startup();
   while (1)
   {
       show(length, array);
       updata(length,num); //摁键事件
   }
  
    _getch();
    closegraph();//关闭绘图界面
    return 0;
}
