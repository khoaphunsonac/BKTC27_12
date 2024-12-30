#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>
using namespace std;

int sumNegative(int array[], int n);
bool isPrime(int n);
int countPrime(int array[], int n);
void printPrime(int array[], int n);
void exportResult(int array[], int n,int choice);

int main()
{
    ifstream infile("cau2.txt");
    int array[5];
    for (int i = 0; i < 5; i++)
    {
        infile >> array[i];
    }
    int choice;
    do
    {
        system("cls");
        printf("MENU\n");
        printf("1. Tinh tong cac so am trong mang\n");
        printf("2. Liet ke va dem so nguyen to trong mang\n");
        printf("3. Xuat ket qua ra file\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Tong cac so am trong mang la: %d\n", sumNegative(array, 5));
            system("pause");
            break;
        case 2:
            printPrime(array, 5);
            system("pause");
            break;
        case 3:
            printf("Hay chon 1 hoac 2 de xuat ket qua: \n");
            int temp;
            scanf("%d", &temp);
            exportResult(array, 5, temp);
            system("pause");
            break;
        case 0:
            printf("Cam on ban da su dung chuong trinh!\n");
            break;
        default:
            printf("Lua chon khong hop le!\n");
            system("pause");
            break;
        }
    } while (choice != 0);
    return 0;
}

int sumNegative(int array[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] < 0)
            sum += array[i];
    }
    return sum;
}

bool isPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int countPrime(int array[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (isPrime(array[i]))
        {
            count++;
        }
    }
    return count;
}

void printPrime(int array[], int n)
{
    printf("Cac so nguyen to trong mang la: ");
    for (int i = 0; i < n; i++)
    {
        if (isPrime(array[i]))
        {
            printf("%d ", array[i]);
        }
    }
    printf("\nSo luong so nguyen to trong mang la: %d\n", countPrime(array, n));
}

void exportResult(int array[], int n, int choice)
{
    if (choice == 1)
    {
        ofstream outfile("ketqua.txt",ios::trunc);
        if (!outfile.is_open())
        {
            printf("Khong the mo file de ghi ket qua!\n");
            return;
        }
        outfile << "Tong cac so am trong mang la: " << sumNegative(array, n) << endl;
        outfile.close();
        printf("Ghi ket qua thanh cong!\n");
    }
    else if (choice == 2)
    {
        ofstream outfile("ketqua.txt",ios::trunc);
        if (!outfile.is_open())
        {
            printf("Khong the mo file de ghi ket qua!\n");
            return;
        }
        outfile << "Cac so nguyen to trong mang la: ";
        for (int i = 0; i < n; i++)
        {
            if (isPrime(array[i]))
            {
                outfile << array[i] << " ";
            }
        }
        outfile << endl;
        outfile << "So luong so nguyen to trong mang la: " << countPrime(array, n) << endl;
    }
    else
    {
        printf("Khong co lua chon nay! Hay chon lai! \n");
    }
}
