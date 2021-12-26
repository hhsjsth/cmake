#include <time.h>
#include <random>
#include <iostream>
using namespace std;

int *generateRandomArray(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 999999);
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

void Sort1(int *Arr, int n) //选择排序
{
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) //找到未排序部分的最大值
            if (Arr[k] < Arr[j])
                k = j;
        if (k != i) {
            int temp = Arr[i];
            Arr[i] = Arr[k];
            Arr[k] = temp;
        }
    }
}

void Sort2(int *Arr, int n) //冒泡排序
{
    //int time;                 //用于测试排序的交换次数比例探讨为什么冒泡排序的理论曲线和实际曲线为什么不重合
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (Arr[j] < Arr[j + 1]) //遇到大小关系不符合的就交换
            {
                int temp = Arr[j];
                Arr[j] = Arr[j + 1];
                Arr[j + 1] = temp;
                //int ++time;               //每一次交换则次数加一
            }
}

void Merge(int Arr[], int TempArray[], int start, int mid, int end) //合并排序的合并代价
{
    int i = start, j = mid + 1, k = start;
    while (i != mid + 1 && j != end + 1) {
        if (Arr[i] >= Arr[j]) //比较i和j的相应元素大小，小的先并入临时数组
            TempArray[k++] = Arr[i++];
        else
            TempArray[k++] = Arr[j++];
    }
    for (; i != mid + 1;) //将剩余的为合并入TempArray的序列合并进去
        TempArray[k++] = Arr[i++];
    for (; j != end + 1;)
        TempArray[k++] = Arr[j++];
    for (i = start; i <= end; i++)
        Arr[i] = TempArray[i];
}

void MSort(int Arr[], int TempArray[], int start, int end, int n) //采用递归的方式进行合并排序
{
    if (start < end) {
        int mid;
        mid = (end + start) / 2;
        MSort(Arr, TempArray, start, mid, n);   //用递归的方式对左边进行排序
        MSort(Arr, TempArray, mid + 1, end, n); //用递归的方式对右边进行排序
        Merge(Arr, TempArray, start, mid, end); //合并代价
    }
}

void Sort3(int *Arr, int n) //归并排序进口
{
    int *Arr1 = new int[n]; //设置一个用于暂时存储数据的数组
    MSort(Arr, Arr1, 0, n - 1, n);
}

void quickSort(int *Arr, int i, int j, int n) {
    if (i < j) {
        int ii = i, jj = j, num = Arr[i];
        while (ii < jj) {
            while (ii < jj && Arr[jj] > num) //从右边扫描，如果大小关系不符合则交换位置
                --jj;
            if (ii < jj)
                Arr[ii++] = Arr[jj];
            while (ii < jj && Arr[ii] <= num) //从左边扫描，如果大小关系不符合则交换位置
                ++ii;
            if (ii < jj)
                Arr[jj--] = Arr[ii];
        }

        Arr[ii] = num;
        quickSort(Arr, i, ii - 1, n);
        quickSort(Arr, ii + 1, j, n);
    }
}

void Sort4(int *Arr, int n) //快速排序进口
{
    quickSort(Arr, 0, n - 1, n);
}

void Sort5(int *Arr, int n) //插入排序
{
    int i, j;
    for (i = 1; i < n; i++) {
        if (Arr[i] < Arr[i - 1]) //需将Arr[i]插入有序子表 */
        {
            int k = Arr[i]; //设置哨兵
            for (j = i - 1; Arr[j] > k && j >= 0; j--)
                Arr[j + 1] = Arr[j];
            Arr[j + 1] = k;
        }
    }
}

int main() {
    // system("chcp 65001");
    while (1) {
        cout << "1.选择排序 2.冒泡排序 3.合并排序 4.快速排序 5.插入排序算法" << endl;
        cout << "通过输入数字后回车选择你想要的使用的排序算法：" << endl;
        int type;
        cin >> type;
        int time;
        time = 0;
        switch (type) {
        case (1):
            for (int i = 1; i <= 5; ++i) {
                int n = i * 10000;
                cout << "数据量为" << n << "时选择排序的时间是";
                double time;
                time = 0;
                for (int j = 1; j <= 20; ++j) {
                    int *Arr = generateRandomArray(n);
                    double start_time = clock();
                    Sort1(Arr, n);
                    double end_time = clock();
                    cout << (end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << ' ';
                    time += (end_time - start_time) / CLOCKS_PER_SEC * 1000;
                }
                cout << endl;
                cout << "平均时间为" << time / 20 << "ms" << endl;
            }
            break;
        case (2):
            for (int i = 1; i <= 5; ++i) {
                int n = i * 10000;
                cout << "数据量为" << n << "时冒泡排序的时间是";
                double time;
                time = 0;
                for (int j = 1; j <= 20; ++j) {
                    int *Arr = generateRandomArray(n);
                    double start_time = clock();
                    Sort2(Arr, n);
                    double end_time = clock();
                    cout << (end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << ' ';
                    time += (end_time - start_time) / CLOCKS_PER_SEC * 1000;
                }
                cout << endl;
                cout << "平均时间为" << time / 20 << "ms" << endl;
            }
            break;
        case (3):
            for (int i = 1; i <= 5; ++i) {
                int n = i * 10000;
                cout << "数据量为" << n << "时归并排序的时间是";
                double time;
                time = 0;
                for (int j = 1; j <= 20; ++j) {
                    int *Arr = generateRandomArray(n);
                    double start_time = clock();
                    Sort3(Arr, n);
                    double end_time = clock();
                    cout << (end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << ' ';
                    time += (end_time - start_time) / CLOCKS_PER_SEC * 1000;
                    delete Arr;
                }
                cout << endl;
                cout << "平均时间为" << time / 20 << "ms" << endl;
            }
            break;
        case (4):
            for (int i = 1; i <= 5; ++i) {
                int n = i * 10000;
                cout << "数据量为" << n << "时快速排序的时间是";
                double time;
                time = 0;
                for (int j = 1; j <= 20; ++j) {
                    int *Arr = generateRandomArray(n);
                    double start_time = clock();
                    Sort4(Arr, n);
                    double end_time = clock();
                    cout << (end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << ' ';
                    time += (end_time - start_time) / CLOCKS_PER_SEC * 1000;
                }
                cout << endl;
                cout << "平均时间为" << time / 20 << "ms" << endl;
            }
            break;
        case (5):
            for (int i = 1; i <= 5; ++i) {
                int n = i * 10000;
                cout << "数据量为" << n << "时插入排序的时间是";
                double time;
                time = 0;
                for (int j = 1; j <= 20; ++j) {
                    int *Arr = generateRandomArray(n);
                    double start_time = clock();
                    Sort5(Arr, n);
                    double end_time = clock();
                    cout << (end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << ' ';
                    time += (end_time - start_time) / CLOCKS_PER_SEC * 1000;
                }
                cout << endl;
                cout << "平均时间为" << time / 20 << "ms" << endl;
            }
            break;
        default:
            break;
        }
    }
}
//clock_t start_time = clock();
//clock_t end_time = clock();
//cout << "Runing time is:" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
