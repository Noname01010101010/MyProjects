
#include <cctype>
#include <iostream>
using namespace std;
 
class Alpha
{
    unsigned bin;
public:
    Alpha() {bin=0;}; //Создание подмножества = пустой строке (Все 32 бита заполняются 0)
    Alpha(char*); //Конструктор заполнения строки
    Alpha operator* (Alpha&);//Перегрузка оператора*
    operator char*();//Перегрузка оператора преобразования типа данных
    friend ostream& operator<< (ostream&, Alpha&);//Перегрузка оператора вывода
};
//Ф-ция заполнения подмножества
Alpha::Alpha(char* s)
{
    bin=0;//обнуление переменной (32 бит этой переменной)
    while(*s)//Пока наша строка существует
    {
        bin |= (1 << (tolower(*s) - 'a'));//Идет заполнение строки путем смещения 1 на ASCI-код введенной буквы
        s++;
    }
}
//Перегрузка оператора*
Alpha Alpha::operator* (Alpha& y)
{
    Alpha z;//Создаем дополнительную переменную для записи объединения
    z.bin = bin & y.bin;//Поиск пересечения двух строк
    return(z);//Возврат этой строки
}
//Перегрузка оператора вывода
ostream& operator<< (ostream& out, Alpha& z)
{
    unsigned bit=1;
    int i;
    for(i=0; i<26; i++)//Проход по алфавиту латинских букв
    {
        if((z.bin & bit)>0)
            out<<(char)('a'+i);//Вывод символа
        bit=bit<<1;//Смещение на единицу влево
    }
    return out;
}
//Перегрузка оператора преобразования типа данных
Alpha::operator char*()
{
    static char s[32];//Строка для хранения результатов
    unsigned w=bin;//Дополнительная переменная для хранения bin
    int i=0, j=0;
    while(w > 0)//Проход по строке
    {
        if(w & 1)
            s[j++]='a'+i;//Запись буквы в строку, если она существует
        i++;
        w = w >> 1;
    }
    s[j]='\0';
    return (s);
}
 
int main (int argc, char* argv[])
{
    if(argc !=3)
    {
        cout<<"Invalid input, try again!"<<endl<<"Correct input is 2 strings!"<<endl;
        return -1;
    }
    Alpha x(argv[1]);
    Alpha y(argv[2]);
    Alpha z;
    z=x*y;
    cout<<z<<endl; // или cout<<(char*)z;
    return (0);
}
