void  ShellSort(int *array,int length) //希尔排序
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
    int low,high,mid;
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
void QuickSort(int* arr, int low, int high) //快速排序
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j)
        {
            while (i < j && arr[j] >= k)
            {
                j--;
            }
            if (i < j)
            {
                arr[i++] = arr[j];
            }
            while (i < j && arr[i] < k)
            {
                i++;
            }
            if (i < j)
            {
                arr[j--] = arr[i];
            }
        }
        arr[i] = k;
        QuickSort(arr, low, i - 1);//递归
        QuickSort(arr, i + 1, high);
    }
}
void BubbleSort(int* arr, int length) //冒泡排序
{
    int i, j, temp;
    for (i = 0; i < length - 1; i++)
        for (j = 0; j < length - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }

}
void view(int array[]) //打印数组
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }
}
