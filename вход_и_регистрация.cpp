#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
 
using namespace std;
 
 
bool check(string, string);
bool check_1(string, string);
void read(string, string );
void admin();
void vhod();
void login();
void register_1();
struct Users
{
    string login_new;
    string password_new;
}
users[100];
 
int main()
{
    setlocale(LC_ALL, "rus");
    cout << "1 - Вход от имени пользователя" << endl;
    cout << "2 - Вход от имени администратора" << endl;
    int a;
    cin >> a;
    switch (a)
    {
 
    case 1: vhod();
    case 2: admin();
 
 
    }
 
}
void vhod()
{
    
    bool flag = false;
 
    string login, password;
    cout << "Введите логин: " << endl;
    cin >> login;
    cout << "Введите пароль: " << endl;
    cin >> password;
    flag = check(login, password);
    if (flag == true)
    {
        cout << "Вы вошли в систему!" << endl;
    }
    else
    {
        system("cls");
        cout << "Неверный пароль. Попробуйте еще раз." << endl;
        main();
        
    }
    
    
    system("pause");
 
 
 
}
 
 
bool check(string login, string password)
 
{
    
    if  (login == "LEO" && password == "Messi_10")
    {
        return true;
    }
    else
    {
        return false;
    }
}
////////////////////////////////////////////////////////////////////////////////////
 
void admin()
{
    bool flag_1 = false;
 
    string login_admin, password_admin;
    cout << "Введите логин: " << endl;
    cin >> login_admin;
    cout << "Введите пароль: " << endl;
    cin >> password_admin;
 
    flag_1 = check_1(login_admin, password_admin);
    if (flag_1 == true)
    {
        cout << "Вы вошли в систему от имени администратора!" << endl;
    }
    else
    {
        system("cls");
        cout << "Неверный пароль. Попробуйте еще раз." << endl;
        main();
    }
 
    /////////////////////////////////////////////////////////////////////////////////////
    cout << "1 - Зарегестрировать нового пользователя: " << endl;
    cout << "2 - Выйти: " << endl;
    int a1;
    cin >> a1;
    switch (a1)
    {
    case 1: register_1();
    case 2: main();
    }
 
    }
    bool check_1(string login_admin, string password_admin)
    {
        if (login_admin == "Neyamr_11" && password_admin == "Travma_always")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
 
    ////////////////////////////////////////////////////////////////////////////////////////////
    void register_1()
    {
        string login_new, password_new;
        cout << "Введите логин нового пользователя: " << endl;
        cin >> login_new;
        cout << "Введите пароль нового пользователя: " << endl;
        cin >> password_new;
        ofstream fout("users.txt", ios::app);
        fout << login_new << "" << password_new << endl;
        cout << "Поздравляем! Регистрация прошла успешно! " << endl;
        main();
    }
 
    void read(string login_new, string password_new)
    {
        ifstream fin("users.txt");
        for (int i = 0; i < 100; i++)
        {
            fin >> users[1].login_new >> users[1].password_new;
        }
    }
 
    void login()
    {
        string login_new, password_new;
        cout << "Введите логин: " << endl;
        cin >> login_new;
        cout << "Введите пароль: " << endl;
        cin >> password_new;
        read(login_new, password_new);
        for (int i = 0; i < 100; i++)
        {
            if (login_new == users[1].login_new && password_new == users[1].password_new)
            {
                cout << "Вход успешен!" << endl;
            }
        }
    }

