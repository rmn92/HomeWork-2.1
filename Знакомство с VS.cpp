#include <iostream>
#include <fstream>

using namespace std;

void shiftArr(int** arr, int* arrSizes, int count, char trend);
void reverseArr(int** arr, int* arrSizes, int count);
void printArr(int** arr, int* arrSizes, int count, ofstream& fout);

int main()
{
    setlocale(LC_ALL, "rus");

    int count = 0; //переменная в которой будет храниться общее количество массивов из файла 
    int value = 0;
    int size = 0;
    char trend = 'L'; //начальное направление сдвига элементов в массиве. L - влево, R - вправо 

    // считаем количество массивов в файле
    {
        ifstream fin("in.txt");

        if (fin.is_open())
        {
            while (!fin.eof())
            {
                fin >> size;
                for (int i = 0; i < size; i++)
                {
                    fin >> value;
                }
                count = count + 1;
            }
            fin.close();
        }
        else
        {
            cout << "Не удалось открыть файл";
        }
    }

    int** arr = new int* [count]; //создаём двумерный массив

    for (int i = 0; i < count; i++)
    {
        arr[i] = new int[2];
    }

    ifstream fin("in.txt");
    ofstream fout("out.txt");

    int* arrSizes = new int[count]; //массив в котором будет храниться информация о размерах

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            for (int i = 0; i < count; i++)
            {
                fin >> size;
                arrSizes[i] = size;
                for (int j = 0; j < size; j++)
                {
                    fin >> value;
                    arr[i][j] = value;
                }
            }

            shiftArr(arr, arrSizes, count, trend);
            reverseArr(arr, arrSizes, count);
            printArr(arr, arrSizes, count, fout);
        }
        delete[] arr;
        delete[] arrSizes;
        fin.close();
    }
    else
    {
        cout << "Не удалось открыть файл";
    }
}

void shiftArr(int** arr, int* arrSizes, int count, char trend)
{
    int size = 0;
    int tmp = 0;

    for (int i = 0; i < count; i++)
    {
        size = arrSizes[i];

        if (trend == 'L')
        {
            tmp = arr[i][0];
            for (int j = 0; j < size - 1; j++)
            {
                arr[i][j] = arr[i][j + 1];
            }
            arr[i][size - 1] = tmp;
            trend = 'R';

        }
        else if (trend == 'R')
        {
            tmp = arr[i][size - 1];
            for (int j = size - 1; j > 0; j--)
            {
                arr[i][j] = arr[i][j - 1];
            }
            arr[i][0] = tmp;
            trend = 'L';
        }
    }
}

void reverseArr(int** arr, int* arrSizes, int count)
{
    int temp = 0;
    int size = 0;

    for (int i = 0; i < count / 2; i++)
    {
        temp = arrSizes[i];
        arrSizes[i] = arrSizes[count - i - 1];
        arrSizes[count - i - 1] = temp;
    }
}

void printArr(int** arr, int* arrSizes, int count, ofstream& fout)
{
    int size = 0;
    int idx = 0;

    for (int i = count - 1; i >= 0; i--)
    {
        size = arrSizes[idx];
        fout << size;
        fout << endl;
        cout << size << endl;

        for (int j = 0; j < size; j++)
        {
            cout << arr[i][j] << " ";
            fout << arr[i][j] << " ";
        }
        idx = idx + 1;
        cout << endl;
        fout << endl;
    }
}
