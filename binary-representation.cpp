#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <string>
#include <math.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    char a;
    long double b;

    char c_mask = 1;
    unsigned char c_ld_mask = 1;

    string str_a = "";
    string str_b = "";

    int c, d;

    cout << "Введите cимвол (тип char): ";
    cin >> a;

    cout << "Введите число (тип long double): ";
    cin >> b;

    for (size_t i = 0; i < sizeof(a) * 8; i++) {
        if ((a & c_mask) != 0) {
            str_a += "1";
        }
        else str_a += "0";
        c_mask *= 2;
    }

    union ld_to_c {
        long double ld;
        char arr[sizeof(long double)];
    };

    union ld_to_c un;
    un.ld = b;

    for (int j = 0; j < sizeof(b); j++) {
        for (size_t i = 0; i < 8; i++) {
            if ((un.arr[j] & c_ld_mask) != 0) {
                str_b += '1';
            }
            else str_b += '0';
            c_ld_mask *= 2;
        }
        c_ld_mask = 1;
    }
    reverse(str_a.begin(), str_a.end());
    reverse(str_b.begin(), str_b.end());

    cout << "Представление переменной типа char: " << str_a << endl;
    cout << "Представление переменной типа long double: " << str_b << endl;
    cout << endl;

    cout << "Введите старший разряд: ";
    cin >> c;

    cout << "Введите количество разрядов (должно быть не больше старшего разряда): ";
    cin >> d;

    char a_str_b[64];
    int k = 0;

    for (int j = 0; j < sizeof(long double); j++) {
        for (size_t i = 0; i < 8; i++) {
            if ((un.arr[j] & c_ld_mask) != 0) {
                a_str_b[k] = '1';
            }
            else a_str_b[k] = '0';
            c_ld_mask *= 2;
            k++;
        }
        c_ld_mask = 1;
    }

    for (size_t i = 0; i < d / 2; ++i) swap(a_str_b[c - d + i], a_str_b[c - i - 1]);

    for (size_t i = 0; i < (sizeof(long double) * 8) / 2; ++i) {
        swap(a_str_b[i], a_str_b[63 - i]);
    }

    cout << endl;
    cout << "Зеркально отражены " << d << " бит, старший из которых " << c << "-й: ";
    for (size_t i = 0; i < 64; ++i) {
        cout << a_str_b[i];
    }

    cout << endl;
    k = 0;

    for (int i = 0; i < 8; i++) {
        un.arr[i] = 0x0;
    }

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (a_str_b[k] == '1') {
                un.arr[i] += 1;
            }
            k++;
            if (j != 7) un.arr[i] = un.arr[i] << 1;
        }
    }

    cout << endl << "Полученное число: " << un.ld << endl;

    return 0;
}