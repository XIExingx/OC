#include<iostream>
#include<Windows.h>
using namespace std;

int num = 0;
int min_n = 0;
int max_n = 0;
UINT StopFlag = 0;//运行终止标志，防止主线程的“请按任意键继续...”出现在输出中

DWORD WINAPI min_max(LPVOID arr)//线程函数1
{
    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < num; i++) 
    {
        if (min > ((int*)arr)[i]) 
        {
            min = ((int*)arr)[i];
            min_n = i + 1;
        }
    }
    Sleep(7);
    for (int i = 0; i < num; i++)
    {
        if (max < ((int*)arr)[i]) 
        {
            max = ((int*)arr)[i];
            max_n = i + 1;
        }
    }
    Sleep(7);
    cout << "Min" << endl;
    cout << min << endl;
    cout << "№" << min_n << endl;
    cout << endl;

    cout << "Max:" << endl;
    cout << max << endl;
    cout << "№" << max_n << endl;
    cout << endl;

    StopFlag++;
    return 0;
}

int a;
DWORD WINAPI average(LPVOID arr)//线程函数2
{
    int average = 0;

    for (int i = 0; i < num; i++) 
    {
        average += ((int*)arr)[i];
    }
    average /= num;
    a = average;
    cout << "Средний" << endl;
    cout << average << endl;
    Sleep(12);
    StopFlag++;


    return 0;
}
int main()
{
    cin >> num;

    int* arr = new int[num];
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i];
    }

    HANDLE hThread1, hThread2;
    DWORD  uID1, uID2;
    hThread1 = ::CreateThread(NULL, 0, min_max, arr, 0, NULL);
    hThread2 = ::CreateThread(NULL, 0, average, arr, 0, NULL);

    DWORD WaitDorSingleObject(
        HANDLE hHandle,
        DWORD dwMilliseconds
    );

    ::WaitForSingleObject(hThread1, INFINITY);
    ::WaitForSingleObject(hThread2, INFINITY);
    ::CloseHandle(hThread1);
    ::CloseHandle(hThread2);
    while (StopFlag < 2)//两个线程都结束后StopFlag的值会增加到2，此时主线程停止等待，输出“请按任意键继续...”字样提示用户程序即将终止
    {
        Sleep(2000);
    }

    arr[min_n - 1] = a;
    arr[max_n - 1] = a;
    for (int i = 0; i < num; i++) 
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}