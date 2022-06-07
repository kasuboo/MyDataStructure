void ShellSort(int* array, int lengths) //希尔排序
{
    flag = 0;
    int gap = lengths / 2; //增量
    while (gap > 1) //当增量不为1时循环执行排序
    {
        show(length, array);
        gap = gap / 2; //每次增量折半
        for (int i = 0; i < lengths - gap; i++)
        {
            show(length, array);
            int min = i; //当前组内最小下标
            int max = min + gap;
            while (min >= 0) //当最小下标大于等于0时继续执行排序
            {
                if (array[max] < array[min]) //组内后一个比前一个小，交换
                {
                    int temp = array[min];
                    array[min] = array[max];
                    array[max] = temp;
                    show(length, array);
                }
                else //无需交换，执行下一次
                {
                    show(length, array);
                    break;
                }                  
            }
        }
        show(length, array);
    }
    flag = isOK(array, length);
    show(length, array);
}
