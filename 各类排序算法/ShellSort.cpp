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
