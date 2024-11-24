#include <iostream>
#include <ctype.h>
#include <iso646.h>
using namespace std;
int main(int argc, char *argv[]){
    unsigned long int ipaddress = 0;
    if(argc<3){
        cout<<"Too few parametrs"<<endl;
        return 1;
    }
    else if(strncmp(argv[1],"-p",2)and  strncmp(argv[1],"-u",2)){
        cout<<"Неверный формат параметров"<<endl;
        return 1;
    }
    //Если IP передан вычисляем число
    if(!strncmp(argv[1], "-p", 2)){
        char ip[4][4];
        int i,j,count;
        //Помещаем отдельные фрагменты ip-adresa v massiv IP
        //count - nomer fragmenta ip-adresa
        // i - nomer simvola v parametre
        // j - nomer simvola v fragmente
        for(i=0,j=0,count=0;i<strlen(argv[2]);i++){
            if(isdigit(argv[2][i])){
                ip[count][j++]=argv[2][i];
            }
            else if (argv[2][i]=='.'){
                ip[count++][j++]='\0';
                j=0;
            }
        }
        if(count<3){
            cout<<"Неверный формат Ip-адреса"<<endl;
            return 1;
        }
        ip[count++][j++]='\0';
        //Переводим ip адрес в бинанарную форму
        for(int i=3, mul=1;i>=0;i--,mul*=256){
            int fragment =0;
            for(int k=strlen(ip[i]),mult =1; k;k--, mult*=10){
                fragment +=(ip[i][k - 1] - 48)*mult;
            }
            ipaddress+=fragment*mul;
        }
        cout<<ipaddress<<endl;
    }
    int ip_fragment[]={0,0,0,0};
    //Если передано число - восстанавливаем ip - адрес
    //в формате xxx.yyy.zzz.www
    if(!strncmp(argv[1], "-u", 2)){
        int number=0;
        for(int k=strlen(argv[2]), mult=1;k;k--,mult*=10){
            number=argv[2][k-1] -48;
            if(number<0 or number>9){
                cout<<"Неверный формат переменной"<<endl;
                return 1;
            }
            ipaddress+=number*mult;
        }
        number=0;
        int j=0;
        do{
            if(ipaddress % 256) ip_fragment[j++]=(ipaddress % 256);
            else ip_fragment[j++]=0;
            ipaddress/=256;
        }while(ipaddress);
        //Vivod ip-adres
        cout<<ip_fragment[3]<<'.'
        <<ip_fragment[2]<<'.'
        <<ip_fragment[1]<<'.'
        <<ip_fragment[0]<<endl;
    }
    return 0;
}

