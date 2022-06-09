#include<stdio.h>
#include<stdlib.h>
#include <graphics.h> 
#include <conio.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<assert.h>
#include<Windows.h>
#pragma comment(lib,"Winmm.lib")
#include<mmsystem.h>
#define width 800 //窗口大小
#define height 600 
int rec1[] = { 20, 100,480,580 }; //绘制矩形框显示排序
int array[100]; //要排序的数组
char s[100]; //保存并显示要排序的数组
char printStr[100]; //排序过程中打印出来的数组
char nums[100];
int num; //选择的排序序号
int length; //要排序的数组长度
int flag; //检查排序是否完成
int done = 0;//排序是否选择完成
int sortsNums[8] = { 1,2,3,4,5,6,7,8 };//各种排序的编号
void show(int length, int array[]);
void toChar(int* array);
int isOK(int* array, int length);
//微秒级程序运行
double run_time;
_LARGE_INTEGER TIME_start;
_LARGE_INTEGER TIME_end;
double dqFreq;
LARGE_INTEGER f;

void MergeSort(int arr[], int len)
{
    flag = 0;
    int* a = arr;
    int* b = (int*)malloc(len * sizeof(int));
    int seg, start;
    for (seg = 1; seg < len; seg += seg)
    {
        for (start = 0; start < len; start += 2 * seg)
        {
            int low = start, mid = min(start + seg, len), high = min(start + 2 * seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
            {
                if (a[start1] < a[start2])
                {
                    b[k] = a[start1];
                    start1++;
                    k++;
                }
                else
                {
                    b[k] = a[start2];
                    start2++;
                    k++;
                }
            }
            while (start1 < end1)  //将剩下的start到end复制到b
            {
                b[k] = a[start1];
                start1++;
                k++;
            }
            while (start2 < end2)
            {
                b[k] = a[start2];
                start2++;
                k++;
            }
            show(len, a);
        }
        int* temp = a;
        a = b;
        b = temp;
    }
    if (a != arr)
    {
        int i;
        for (i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
    flag = isOK(array, length);
}
void ShellSort(int* a, int len)
{
    flag = 0;
    int i, j, k, tmp, gap;  // gap 为步长
    for (gap = len / 2; gap > 0; gap /= 2)
    {  
        // 步长初始化为数组长度的一半，每次遍历后步长减半
        for (i = 0; i < gap; ++i)
        { 
            // 变量 i 为每次分组的第一个元素下标 
            for (j = i + gap; j < len; j += gap)
            { 
                //对步长为gap的元素进行直插排序，当gap为1时，就是直插排序
                tmp = a[j];  //储存a[j]的值
                k = j - gap;  //储存i的值
                while (k >= 0 && a[k] > tmp)
                {
                    show(length, array);
                    a[k + gap] = a[k]; //组内交换
                    k -= gap;
                }
                a[k + gap] = tmp;
                show(length, array);
            }
        }
    }
    flag = isOK(array, length);
}
void selectSort(int* array, int length) //选择排序
{
    flag = 0; //排序未完成标志
    int i, j;
    int min = 0;
    for (i = 0; i < length - 1; i++)
    {
        min = i; //先假设第一个元素最小
        for (j = i + 1; j < length; j++)
        {
            if (array[j] < array[min])
                min = j; //如果有更小的，更新最小值下标
        }
        int temp = array[min]; //每次都将最小值移到未排序序列的最前面，下一次从下一个元素开始
        array[min] = array[i];
        array[i] = temp;
        flag = isOK(array, length);
        show(length, array);
    }
}
void InSertSort(int* array, int length) //直接插入排序
{
    flag = 0; //排序未完成
    for (int i = 1; i < length; i++) //从第二个数开始排
    {
        int temp = array[i]; //哨兵,保存哨兵数据
        int j = i - 1; //前i-1个数都是有序序列，记录下标
        while (j >= 0 && array[j] > temp)
        {
            array[j + 1] = array[j]; //数据后移
            j--;
        }
        array[j + 1] = temp; //移到正确的位置
        flag = isOK(array, length);
        show(length, array);
    }
}
void HalfInsertSort(int* array, int length) //折半插入排序
{
    int low, high, mid;
    int key;
    flag = 0;
    for (int i = 1; i < length; i++)
    {
        key = array[i]; //要插入的值
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
        flag = isOK(array, length);
        show(length, array);
    }
}
void QuickSort(int* array, int low, int lengths) //快速排序
{
    flag = 0;
    int high = lengths;
    if (low < high) //左右哨兵还没相遇
    {
        int i = low;
        int j = high; //每次都必须j先向左移动,寻找比key小的数
        int key = array[low]; //当前要处理的元素，每次都设置为第一个
        while (i < j) //当low和high未相遇时
        {
            while (i < j && array[j] >= key) //j从右往左寻找比key小的数
            {
                j--;
            }
            if (i < j)
            {
                array[i++] = array[j]; //比6小的值赋到low+1位置
            }
            while (i < j && array[i] < key) //i从左往右寻找比key大的数
            {
                i++;
            }
            if (i < j)
            {
                array[j--] = array[i];
            }
        }
        //至此，左边的值都比key小，右边的值都比key大
        array[i] = key;
        show(length, array);
        QuickSort(array, low, i - 1); //处理左边序列
        QuickSort(array, i + 1, high); //处理右边序列
    }
    flag = isOK(array, length);
    show(length, array);
}
void BubbleSort(int* arrar, int length) //冒泡排序
{
    flag = 0;
    int i, j, temp;
    for (i = 0; i < length - 1; i++) //每次从第一个开始，从左往右比较，大的就交换，直到遇到比当前元素更大的
        for (j = 0; j < length - 1 - i; j++)
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = arrar[j + 1];
                array[j + 1] = temp;
                flag = isOK(array, length);
                show(length, array);
            }

}
void Swap(int* x, int* y)
{
    int d = 0;
    d = *x;
    *x = *y;
    *y = d;
}
void Make(int* data, int numb, int root)
{
    assert(data); //如果找不到该数组，发生错误,函数终止运行
    int parent = root;
    int child = (parent * 2) + 1;//默认左孩子
    while (child < numb)
    {
        if (child + 1 < numb && data[child] < data[child + 1])//两孩子选大值
        {
            child += 1;
        }
        if (data[child] > data[parent])//交换及继续往下
        {
            Swap(&data[child], &data[parent]); //父结点的值和孩子的值交换
            parent = child;
            child = (parent * 2) + 1;
        }
        else
            break;
    }
}
void HeapSort(int* data, int numb) //堆排序
{
    flag = 0;
    for (int i = (numb - 1 - 1) / 2; i >= 0; --i)//从最后一个孩子父亲开始线性减少(下标)，范围线性增大
    {
        Make(data, numb, i);
    }
    int end = numb - 1;//数据最后一个值的下标
    while (end > 0)
    {
        Swap(&data[0], &data[end]); //父结点的值和最后一个值交换
        Make(data, end, 0);//每次执行都将把最后一个值排外(都将有序)
        end--;
        show(numb, data);
    }
    flag = isOK(array, length);
}
void show(int length, int array[]) //绘制页面
{
    IMAGE background;
    cleardevice();
    loadimage(&background, "月亮.png", 800, 600);
    putimage(0, 0, &background);
    setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1.5);
    setlinecolor(BLACK);
    rectangle(rec1[0], rec1[1], rec1[2], rec1[3]); //绘制排序框
    setbkmode(TRANSPARENT);//设置透明文字
    settextcolor(BLUE);//设置字体颜色

    settextstyle(20, 0, _T("楷体"));//设置字体大小、样式
    outtextxy(20, 45, "需要排序的数组:");
    outtextxy(180, 45, _T(s));
    outtextxy(20, 70, "正在排序的数组:");
    toChar(array); //数组转字符串，用于输出
    outtextxy(180, 70, _T(printStr));
    char t[100] = { '\0' };
    if (flag == 1) //排序完成
    {
        IMAGE picture;
        settextstyle(20, 0, _T("楷体"));//设置字体大小、样式
        loadimage(&picture, "玉桂狗.jpg", 300, 480);
        putimage(490, 100, &picture);
    }
    //显示当前排序情况
    if (num == 1) //num是程序开始时输入的序号
    {
        int space = 1;
        int time = length * length;
        run_time = 1000 * (TIME_end.QuadPart - TIME_start.QuadPart) / dqFreq; //获得程序运行时间
        outtextxy(20, 20, "当前的选择是选择排序");
        outtextxy(400, 30, "实际运行时间：");
        if (flag == 1) {
            sprintf_s(t, "%lf", run_time);
            outtextxy(535, 30, t);
            outtextxy(650, 30, "ms");
        }
        outtextxy(400, 50, "时间复杂度为：O(");
        sprintf_s(t, "%d", time);
        outtextxy(610, 50, t);
        outtextxy(650, 50, ")");

        outtextxy(400, 70, "空间复杂度为：O(");
        sprintf_s(t, "%d", space);
        outtextxy(610, 70, t);
        outtextxy(650, 70, ")");
    }
    else if (num == 2)
    {
        int space = 1;
        int time = length * length;
        run_time = 1000 * (TIME_end.QuadPart - TIME_start.QuadPart) / dqFreq; //获得程序运行时间
        outtextxy(20, 20, "当前的选择是直接插入排序");
        outtextxy(400, 30, "实际运行时间：");
        if (flag == 1) {
            sprintf_s(t, "%lf", run_time);
            outtextxy(535, 30, t);
            outtextxy(650, 30, "ms");
        }
        outtextxy(400, 50, "时间复杂度为：O(");
        sprintf_s(t, "%d", time);
        outtextxy(610, 50, t);
        outtextxy(650, 50, ")");
        outtextxy(400, 70, "空间复杂度为：O(");
        sprintf_s(t, "%d", space);
        outtextxy(610, 70, t);
        outtextxy(650, 70, ")");
    }
    else if (num == 3)
    {
        int space = 1;
        int time = length * length;
        run_time = 1000 * (TIME_end.QuadPart - TIME_start.QuadPart) / dqFreq; //获得程序运行时间
        outtextxy(20, 20, "当前的选择是折半插入排序");
        outtextxy(400, 30, "实际运行时间：");
        if (flag == 1) {
            sprintf_s(t, "%lf", run_time);
            outtextxy(535, 30, t);
            outtextxy(650, 30, "ms");
        }
        outtextxy(400, 50, "时间复杂度为：O(");
        sprintf_s(t, "%d", time);
        outtextxy(610, 50, t);
        outtextxy(650, 50, ")");
        outtextxy(400, 70, "空间复杂度为：O(");
        sprintf_s(t, "%d", space);
        outtextxy(610, 70, t);
        outtextxy(650, 70, ")");
    }
    else if (num == 4)
    {
        float space = log2(length);
        float time = length * log2(length);
        run_time = 1000 * (TIME_end.QuadPart - TIME_start.QuadPart) / dqFreq; //获得程序运行时间
        outtextxy(20, 20, "当前的选择是快速排序");
        outtextxy(400, 30, "实际运行时间：");
        if (flag == 1) {
            sprintf_s(t, "%lf", run_time);
            outtextxy(535, 30, t);
            outtextxy(700, 30, "ms");
        }
        outtextxy(400, 50, "时间复杂度为：O(");
        sprintf_s(t, "%f", time);
        outtextxy(610, 50, t);
        outtextxy(700, 50, ")");
        outtextxy(400, 70, "空间复杂度为：O(");
        sprintf_s(t, "%f", space);
        outtextxy(610, 70, t);
        outtextxy(700, 70, ")");
    }
    else if (num == 5)
    {
        int space = 1;
        int time = length * length;
        run_time = 1000 * (TIME_end.QuadPart - TIME_start.QuadPart) / dqFreq; //获得程序运行时间
        outtextxy(20, 20, "当前的选择是冒泡排序");
        outtextxy(400, 30, "实际运行时间：");
        if (flag == 1) {
            sprintf_s(t, "%lf", run_time);
            outtextxy(535, 30, t);
            outtextxy(650, 30, "ms");
        }
        outtextxy(400, 50, "时间复杂度为：O(");
        sprintf_s(t, "%d", time);
        outtextxy(610, 50, t);
        outtextxy(650, 50, ")");
        outtextxy(400, 70, "空间复杂度为：O(");
        sprintf_s(t, "%d", space);
        outtextxy(610, 70, t);
        outtextxy(650, 70, ")");
    }
    else if (num == 6)
    {
        int space = length;
        float time = length * log2(length);
        run_time = 1000 * (TIME_end.QuadPart - TIME_start.QuadPart) / dqFreq; //获得程序运行时间
        outtextxy(20, 20, "当前的选择是归并排序");
        outtextxy(400, 30, "实际运行时间：");
        if (flag == 1) {
            sprintf_s(t, "%lf", run_time);
            outtextxy(535, 30, t);
            outtextxy(700, 30, "ms");
        }
        outtextxy(400, 50, "时间复杂度为：O(");
        sprintf_s(t, "%f", time);
        outtextxy(610, 50, t);
        outtextxy(700, 50, ")");

        outtextxy(400, 70, "空间复杂度为：O(");
        sprintf_s(t, "%d", space);
        outtextxy(610, 70, t);
        outtextxy(700, 70, ")");
    }
    else if (num == 7)
    {
        int space = 1;
        float time = pow(length, 1.3);
        run_time = 1000 * (TIME_end.QuadPart - TIME_start.QuadPart) / dqFreq; //获得程序运行时间
        outtextxy(20, 20, "当前的选择是希尔排序");
        outtextxy(400, 30, "实际运行时间：");
        if (flag == 1) {
            sprintf_s(t, "%lf", run_time);
            outtextxy(535, 30, t);
            outtextxy(700, 30, "ms");
        }
        outtextxy(400, 50, "时间复杂度为：O(");
        sprintf_s(t, "%f", time);
        outtextxy(610, 50, t);
        outtextxy(700, 50, ")");
        outtextxy(400, 70, "空间复杂度为：O(");
        sprintf_s(t, "%d", space);
        outtextxy(610, 70, t);
        outtextxy(700, 70, ")");
    }
    else if (num == 8)
    {
        int space = 1;
        float time = length * log2(length);
        run_time = 1000 * (TIME_end.QuadPart - TIME_start.QuadPart) / dqFreq; //获得程序运行时间
        outtextxy(20, 20, "当前的选择是堆排序"); 
        outtextxy(400, 30, "实际运行时间：");
        if (flag == 1) {
            sprintf_s(t, "%lf", run_time);
            outtextxy(535, 30, t);
            outtextxy(700, 30, "ms");
        }
        outtextxy(400, 50, "时间复杂度为：O(");
        sprintf_s(t, "%f", time);
        outtextxy(610, 50, t);
        outtextxy(700, 50, ")");
        outtextxy(400, 70, "空间复杂度为：O(");
        sprintf_s(t, "%d", space);
        outtextxy(610, 70, t);
        outtextxy(700, 70, ")");
    }
    //绘制矩形
    for (int i = 0; i < length; i++)
    {
        setfillcolor(RGB(215, 236, 241));
        setlinecolor(BLACK);
        fillrectangle(40 + 40 * i, 580 - array[i] * 10, 80 + 40 * i, 580);
    }
    FlushBatchDraw();//开始批量绘制
    Sleep(1200);
}
void startup() //初始函数
{
    //时间计时准备
    QueryPerformanceFrequency(&f); //精确获取时间
    dqFreq = (double)f.QuadPart; //获得机器内部计时器的时钟频率，和运行时间差运算获得精确时间
    initgraph(width, height);
    setbkcolor(RGB(250, 250, 250)); //背景色
    cleardevice(); //用背景色清空屏幕
    BeginBatchDraw(); //开始批量绘制
}
int isOK(int* array, int length) //检查排序是否完成
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (array[i] > array[j]) //数组不是有序的，排序未完成
                return 0;
        }
    }
    return 1; //排序完成
}
void toChar(int* array) //将数组转化为字符串，用于输出
{
    char t[100] = { '\0' };
    strcpy_s(printStr, ""); //清空字符串
    for (int i = 0; i < length; i++)
    {
        sprintf_s(t, "%d", array[i]); //数字转为字符，暂存到t
        strcat_s(printStr, t); //t的内容复制到输出字符串
        strcat_s(printStr, " "); //字符串拼接
    }
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
int test(int nums[], int mode) { //检查排序方法选择是否结束，即排序数组是否全部置0，留下被选择的最佳方式
    int d = 0;
    if (mode == 1) { //mode为1，选择排序方法阶段
        int count = 0;
        for (int i = 0; i < 8; i++) {
            if (nums[i] != 0)
                count++;
        }
        if (count == 1) //当只剩下一种排序的时候，比较结束
            d = 1;
    }
    if (mode == 2) { //mode为2，确定比较结果最后选择的排序方法
        for (int i = 0; i < 8; i++) {
            if (sortsNums[i] != 0)
                d = sortsNums[i];
        }
    }
    return d;
}
int ATimeComplex(int a) { //时间复杂度计算
    int d = 10000;
    if (a == 1) //选择排序
        d = length * length; //n^2
    else if (a == 2) //直接插入排序
        d = (length + 2) * (length - 1) / 4 + (length + 4) * (length - 1) / 4; //(n+2)*(n-1)/4 + (n+4)*(n-1)/4
    else if (a == 3) //折半插入排序
        d = (length + 4) * (length - 1) / 4 + length * log2(length) / 2; 
    else if (a == 4) //快速排序
        d = length * log2(length);
    else if (a == 5) //冒泡排序
        d = length * length / 4 + length * length * 3 / 4;
    else if (a == 6) //归并排序
        d = length + length * log2(length);
    else if (a == 7) //希尔排序
        d = pow(length, 1.3);
    else if (a == 8) //堆排序
        d = 2 * length * log2(length);
    return d;
}
int SpatialComplex(int a) {
    int d = 10000;
    if (a == 1)
        d = 1;
    else if (a == 2)
        d = 1;
    else if (a == 3)
        d = 1;
    else if (a == 4)
        d = length;
    else if (a == 5)
        d = 1;
    else if (a == 6)
        d = length;
    else if (a == 7)
        d = 1;
    else if (a == 8)
        d = 1;
    return d;
}
void ATimeCompare() { //时间复杂性
    int min = ATimeComplex(sortsNums[0]); //返回时间复杂性最小的一个，先假设第一个最小
    int* p = &sortsNums[0];
    if (done == 0) {
        for (int i = 1; i < 8; i++) {
            if (ATimeComplex(sortsNums[i]) < min && sortsNums[i] != 0) { //若出现时间复杂度更小的排序方法，且没有淘汰，交换
                *p = 0;
                min = ATimeComplex(sortsNums[i]);
                p = &sortsNums[i];
            }
            else if (ATimeComplex(nums[i]) > min && sortsNums[i] != 0) { //如果出现时间复杂度更大的排序方法，淘汰该方法
                sortsNums[i] = 0;  //已经比较过，淘汰
            }
        }
        done = test(sortsNums, 1); //检查比较是否完成
    }
}
void SpatialCompare() { //空间复杂性
    int min = SpatialComplex(sortsNums[0]); //先假设第一个排序方法的空间复杂度最小
    int* p = &sortsNums[0];
    if (done == 0) {
        for (int i = 1; i < 8; i++) {
            if (SpatialComplex(sortsNums[i]) < min && sortsNums[i] != 0) { //若出现空间复杂度更小的排序方法，且没有淘汰，交换
                *p = 0;
                min = SpatialComplex(sortsNums[i]);
                p = &sortsNums[i];
            }
            else if (SpatialComplex(sortsNums[i]) > min && sortsNums[i] != 0) { //如果出现空间复杂度更大的排序方法，淘汰该方法
                sortsNums[i] = 0;
            }
        }
        done = test(sortsNums, 1); //检查比较是否完成
    }
}
void Stability(int whether) { //稳定性
    if (whether == 0) {
        for (int i = 0; i < 8; i++) {
            if (i == 0 || i == 3 || i == 6) //序号为1、4、7的排序不稳定，直接淘汰
                sortsNums[i] = 0;
        }
    }
    whether = test(sortsNums, 1); //检查比较是否完成,whether即为done
}
void JudgingBestSort(int arr[], int len, int* num) { //判断最好的算法，根据三种性能的先后顺序挨个淘汰
    if (*num == 123) {
        SpatialCompare();
        ATimeCompare();
        Stability(done);
        *num = test(arr, 2); //得到最后选择的排序方法的序号
    }
    else if (*num == 132) {
        SpatialCompare();
        Stability(done);
        ATimeCompare();
        *num = test(arr, 2);
    }
    else if (*num == 213) {
        ATimeCompare();
        SpatialCompare();
        Stability(done);
        *num = test(arr, 2);
    }
    else if (*num == 231) {
        ATimeCompare();
        Stability(done);
        SpatialCompare();
        *num = test(arr, 2);
    }
    else if (*num == 312) {
        Stability(done);
        SpatialCompare();
        ATimeCompare();
        *num = test(arr, 2);
    }
    else if (*num == 321) {
        Stability(done);
        ATimeCompare();
        SpatialCompare();
        *num = test(arr, 2);
    }
}
int main(void)
{
    startup();
    InputBox(s, 100, "请输入要排序的数组:", NULL, NULL, 500, 40, false); //接受输入的字符串，字符串长度，对话框信息，标题，输入框默认值，width，height，是否有取消键
    InputBox(nums, 100, "请选择排序需求（无需空格，输入三个数字顺序）:\n1、空间复杂度优先 2、平均时间复杂度优先 3、稳定性优先\n", "排序模式选择", NULL, 500, 40, false);
    mciSendString("open music.mp3 alias bkmusic", NULL, 0, NULL); //打开音乐文件
    mciSendString("play bkmusic repeat", NULL, 0, NULL);

    char ss[50] = "";
    strcat_s(ss, s); //复制s字符串到ss
    length = toInt(ss); //将字符串转为整形数组,并获得数组长度
    sscanf_s(nums, "%d", &num);//输入转化成数字
    JudgingBestSort(array, length, &num);
    startup();
    show(length, array);
    //判断选择的排序
    if (num == 1) { //选择排序
        QueryPerformanceCounter(&TIME_start); //计时开始
        selectSort(array, length);
        QueryPerformanceCounter(&TIME_end); //计时结束
    }
    else if (num == 2) { //直接插入排序
        QueryPerformanceCounter(&TIME_start); //计时开始
        InSertSort(array, length);
        QueryPerformanceCounter(&TIME_end); //计时结束
    }
    else if (num == 3) { //折半插入排序
        QueryPerformanceCounter(&TIME_start); //计时开始
        HalfInsertSort(array, length);
        QueryPerformanceCounter(&TIME_end); //计时结束
    }
    else if (num == 4) { //快速排序
        QueryPerformanceCounter(&TIME_start); //计时开始
        QuickSort(array, 0, length - 1);
        QueryPerformanceCounter(&TIME_end); //计时结束
    }
    else if (num == 5) { //冒泡排序
        QueryPerformanceCounter(&TIME_start); //计时开始
        BubbleSort(array, length);
        QueryPerformanceCounter(&TIME_end); //计时结束
    }
    else if (num == 6) { //归并排序
        QueryPerformanceCounter(&TIME_start); //计时开始
        MergeSort(array, length);
        QueryPerformanceCounter(&TIME_end); //计时结束
    }
    else if (num == 7) { //希尔排序
        QueryPerformanceCounter(&TIME_start); //计时开始
        ShellSort(array, length);
        QueryPerformanceCounter(&TIME_end); //计时结束
    }
    else if (num == 8) { //堆排序
        QueryPerformanceCounter(&TIME_start); //计时开始
        HeapSort(array, length);
        QueryPerformanceCounter(&TIME_end); //计时结束
    }
    while (1)
    {
        show(length, array);
    }

    mciSendString("stop bkmusic", NULL, 0, NULL);	//停止播放音乐
    mciSendString("close bkmusic", NULL, 0, NULL);	//关闭音乐
    closegraph();//关闭绘图界面
    return 0;
}
