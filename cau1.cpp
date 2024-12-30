#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct KhachHang
{
    char makh[10];
    char hoten[100];
    char gioitinh[20];
};

struct NgayLap
{
    int ngay;
    int thang;
    int nam;
};

struct HoaDon
{
    char mahd[10];
    NgayLap ngaylap;
    char hinhThucThanhToan[50];
    double tongTien;
    KhachHang khachHang;
};

void infoBill(HoaDon hoaDon);
void listBill(HoaDon hoaDon[], int n);
double sumBill(HoaDon hoaDon[], int n, int day, int month, int year);
int countBill(HoaDon hoaDon[], int n, char makh[]);
double sumBillOfCustomer(HoaDon hoaDon[], int n, char makh[]);
bool checkBill(HoaDon hoaDon[], int n, int year, char makh[]);
bool checkCustomer(HoaDon hoaDon[], int n, char makh[]);
bool checkdate(int day, int month, int year);
bool checkDateInBill(HoaDon hoaDon[], int n, int day, int month, int year);
void exportBillToFile(HoaDon hoaDon[], int n, char hinhThucThanhToan[]);
int main()
{
    int n = 5;
    HoaDon hoaDon[n] = {
        {"HD001", {1, 1, 2021}, "Tien mat", 100000, {"KH001", "Nguyen Van A", "Nam"}},
        {"HD002", {1, 1, 2021}, "Chuyen khoan", 200000, {"KH002", "Nguyen Thi B", "Nu"}},
        {"HD003", {3, 1, 2021}, "Tien mat", 300000, {"KH001", "Nguyen Van A", "Nam"}},
        {"HD004", {1, 1, 2021}, "Chuyen khoan", 400000, {"KH003", "Tran Thi D", "Nu"}},
        {"HD005", {5, 1, 2021}, "Tien mat", 500000, {"KH004", "Le Van E", "Nam"}}};
    int choice;
    do
    {
        system("cls");
        printf("Menu: \n");
        printf("1. Liet ke danh sach hoa don\n");
        printf("2. Tinh tong tien duoc lap theo ngay, thang, nam.\n");
        printf("3. Dem va tinh tong tien hoa don theo 1 ma khach hang.\n");
        printf("4. Kiem tra co mua hoa don nao theo 1 nam va 1 ma khach hang.\n");
        printf("5. Ghi danh sach hoa don vao file theo hinh thuc thanh toan.\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("cls");
            listBill(hoaDon, n);
            system("pause");
            break;
        case 2:
            system("cls");
            int day, month, year;
            printf("Nhap ngay, thang, nam: ");
            scanf("%d %d %d", &day, &month, &year);
            if (!checkdate(day, month, year))
            {
                printf("Ngay thang nam khong hop le!\n");
            }
            else if (!checkDateInBill(hoaDon, n, day, month, year))
            {
                printf("Khong co hoa don vao ngay %d/%d/%d\n", day, month, year);
            }
            else
            {
                printf("Tong tien hoa don vao %d/%d/%d la: %.2lf\n", day, month, year, sumBill(hoaDon, n, day, month, year));
            }
            system("pause");
            break;
        case 3:
            system("cls");
            char key[10];
            printf("Nhap ma khach hang: ");
            fflush(stdin);
            scanf("%s", key);
            if (!checkCustomer(hoaDon, n, key))
            {
                printf("Khong co khach hang %s\n", key);
            }
            else
            {
                printf("So hoa don cua khach hang %s la: %d\n", key, countBill(hoaDon, n, key));
                printf("Tong tien cua khach hang %s la: %.2lf\n", key, sumBillOfCustomer(hoaDon, n, key));
            }
            system("pause");
            break;
        case 4:
            system("cls");
            int year1;
            char key1[10];
            printf("Nhap nam: ");
            scanf("%d", &year1);
            printf("Nhap ma khach hang: ");
            fflush(stdin);
            scanf("%s", key1);
            if (!checkCustomer(hoaDon, n, key1))
            {
                printf("Khong co khach hang %s\n", key1);
                system("pause");
                break;
            }
            else if (checkBill(hoaDon, n, year1, key1))
            {
                printf("Co hoa don cua khach hang %s trong nam %d\n", key1, year1);
            }
            else
            {
                printf("Khong co hoa don cua khach hang %s trong nam %d\n", key1, year1);
            }
            system("pause");
            break;
        case 5:
            system("cls");
            char hinhThucThanhToan[50];
            printf("Nhap hinh thuc thanh toan: ");
            fflush(stdin);
            gets(hinhThucThanhToan);
            exportBillToFile(hoaDon, n, hinhThucThanhToan);
            printf("Ghi file thanh cong!\n");
            system("pause");
            break;
        case 0:
            system("cls");
            printf("Cam on ban da su dung dich vu!\n");
            break;
        default:
            printf("Lua chon khong hop le! Hay chon lai\n");
            system("pause");
            break;
        }

    } while (choice != 0);
}

void infoBill(HoaDon hoaDon)
{
    printf("Ma hoa don: %s\n", hoaDon.mahd);
    printf("Ngay lap: %d/%d/%d\n", hoaDon.ngaylap.ngay, hoaDon.ngaylap.thang, hoaDon.ngaylap.nam);
    printf("Hinh thuc thanh toan: %s\n", hoaDon.hinhThucThanhToan);
    printf("Tong tien: %.2lf\n", hoaDon.tongTien);
    printf("Ma khach hang: %s\n", hoaDon.khachHang.makh);
    printf("Ho ten khach hang: %s\n", hoaDon.khachHang.hoten);
    printf("Gioi tinh: %s\n", hoaDon.khachHang.gioitinh);
}

void listBill(HoaDon hoaDon[], int n)
{
    printf("Danh sach hoa don: \n");
    for (int i = 0; i < n; i++)
    {
        printf("Hoa don %d:\n", i + 1);
        infoBill(hoaDon[i]);
        printf("--------------------------\n");
    }
}

double sumBill(HoaDon hoaDon[], int n, int day, int month, int year)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (hoaDon[i].ngaylap.ngay == day && hoaDon[i].ngaylap.thang == month && hoaDon[i].ngaylap.nam == year)
        {
            sum += hoaDon[i].tongTien;
        }
    }
    return sum;
}

int countBill(HoaDon hoaDon[], int n, char makh[])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(hoaDon[i].khachHang.makh, makh) == 0)
        {
            count++;
        }
    }
    return count;
}

double sumBillOfCustomer(HoaDon hoaDon[], int n, char makh[])
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(hoaDon[i].khachHang.makh, makh) == 0)
        {
            sum += hoaDon[i].tongTien;
        }
    }
    return sum;
}

bool checkBill(HoaDon hoaDon[], int n, int year, char makh[])
{
    for (int i = 0; i < n; i++)
    {
        if (hoaDon[i].ngaylap.nam == year && strcmp(hoaDon[i].khachHang.makh, makh) == 0)
        {
            return true;
        }
    }
    return false;
}

bool checkCustomer(HoaDon hoaDon[], int n, char makh[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(hoaDon[i].khachHang.makh, makh) == 0)
        {
            return true;
        }
    }
    return false;
}

bool checkdate(int day, int month, int year)
{
    if (year < 0)
    {
        return false;
    }
    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1 || day > 31)
    {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        return false;
    }
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            if (day > 29)
            {
                return false;
            }
        }
        else
        {
            if (day > 28)
            {
                return false;
            }
        }
    }
    return true;
}

bool checkDateInBill(HoaDon hoaDon[], int n, int day, int month, int year)
{
    for (int i = 0; i < n; i++)
    {
        if (hoaDon[i].ngaylap.ngay == day && hoaDon[i].ngaylap.thang == month && hoaDon[i].ngaylap.nam == year)
        {
            return true;
        }
    }
    return false;
}

void exportBillToFile(HoaDon hoaDon[], int n, char hinhThucThanhToan[])
{
    ofstream output("ketqua.txt", ios::trunc);
    bool flag = false;
    if (!output)
    {
        printf("Khong the mo file de ghi\n");
        return;
    }
    output << "Danh sach hoa don thanh toan bang hinh thuc " << hinhThucThanhToan << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(hoaDon[i].hinhThucThanhToan, hinhThucThanhToan) == 0)
        {
            flag = true;
            output << "Hoa don " << i + 1 << ":" << endl;
            output << "Ma hoa don: " << hoaDon[i].mahd << endl;
            output << "Ngay lap: " << hoaDon[i].ngaylap.ngay << "/" << hoaDon[i].ngaylap.thang << "/" << hoaDon[i].ngaylap.nam << endl;
            output << "Hinh thuc thanh toan: " << hoaDon[i].hinhThucThanhToan << endl;
            output << "Tong tien: " << hoaDon[i].tongTien << endl;
            output << "Ma khach hang: " << hoaDon[i].khachHang.makh << endl;
            output << "Ho ten khach hang: " << hoaDon[i].khachHang.hoten << endl;
            output << "Gioi tinh: " << hoaDon[i].khachHang.gioitinh << endl;
            output << "--------------------------" << endl;
        }
    }
    if(!flag){
        output << "Khong co hoa don thanh toan " << hinhThucThanhToan << endl;
    }
    output.close();
}
