#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
void rules();
int main() {
    setlocale(0, "");
    string playerName;
int balance; // ваш баланс
int bettingAmount; // ставка на сумму
int guess; // угаданное вами число
int dice; // загаданное компьютером число
char choice; // для продолжения игры
srand(time(0));
cout << "Добро пожаловать в казино-чисел \n";
rules();
cout << "Как вас зовут: ";
getline(cin, playerName);
cout << "\nНапишите ваш стартовый баланс для начала игры: $";
cin >> balance;
do {
    system("cls");
    cout << "\nВаш баланс на данный момент составляет: " << balance << 
"$\n";
    do {
        cout << "Ну что," << playerName << ", введите вашу ставку: $";
        cin >> bettingAmount;
        if (bettingAmount > balance) {
            cout << "Ваш баланс меньше, чем ваша ставка!\n" << "\n";
        }
    } while (bettingAmount > balance);
    do {
        cout << "Какое число я загадал(от 1 до 10): ";
            cin >> guess;
        if (guess <= 0 || guess > 10)
            cout << "\nЧисло должно быть от 1 до 10\n" << "Введите еще 
раз: ";
    } while (guess <= 0 || guess > 10);
    dice = rand() % 10 + 1;
    if(dice == guess) {
        cout << "\nВы выйграли!!! Вы получили выйгрыш $" << bettingAmount 
* 10;
        balance = balance + bettingAmount * 10;
    }
    else {
        cout << "К сожалению вы проиграли. Ваш пройгрыш составил: $" << 
bettingAmount << "\n";
        balance = balance - bettingAmount;
    }
    cout << "Число которое было загадано это " << dice << "\n";
    cout << "\n" << playerName << ", ваш баланс составляет $" << balance 
<< "\n";
    if (balance == 0)
    {
        cout << "У вас нет денег, чтобы продолжить игру ";
        break;
    }
    cout << "\nХотите сыграть снова(y/n)? ";
    cin >> choice;
} while (choice == 'Y' || choice == 'y');
cout << "\nСпасибо за игру. Ваш баланс составляет: $ " << balance << "\n";
 
return 0;
}
void rules()
{
    system("cls");
    cout << "\nПравила казино таковы: \n";
    cout << "1. Угадываете  число от 1 до 10\n";
    cout << "2. Если угадали, то ваша ставка увеличивается в 10 раз\n";
    cout << "3. Если не угадали, то ваша ставка вычитается от вашего 
баланса\n";
    cout << "Удачной игры!)";
 
}
