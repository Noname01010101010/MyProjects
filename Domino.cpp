#include <iostream>
#include <cmath>
using namespace std;
class Domino{
  protected: 
    int x1;
    int y1;
    int x2;
    int y2;
  public:
    Domino(int X1, int Y1, int X2, int Y2) : x1(X1), y1(1), x2(X2), y2(Y2){};
    
    virtual int change(int x1, int y1, int x2, int y2, int n[10][10])=0;
    
    void fill(int n[10][10]);
};
void Domino::fill(int n[10][10]){
  n[x1][y1] = 1;
  n[x2][y2] = 1;
}
class Man:public Domino{ 
  public:
  Man(int x1,int y1, int x2,int y2) : Domino(x1, y1, x2, y2) {};
  virtual int change(int x1, int y1, int x2, int y2, int n[10][10]);
};
int Man::change(int X1, int Y1, int X2, int Y2, int n[10][10]){
  if (Y1<='j' && Y1>='a') Y1 = Y1 - 'a';
  else Y1 = Y1 - 'A';
  if (Y2<='j' && Y2>='a') Y2 = Y2 - 'a';
  else Y2 = Y2 - 'A';
  if (X1<0 || X1>9 || Y1<0 || Y1>9 || X2<0 || X2>9 || Y2<0 || Y2>9){
    cout<<"Координаты вне шахматного поля"<<endl;
    return -1;
  }
  if ((abs(X1 - X2) + abs(Y1 - Y2))!=1){
    cout<<"Не соседние клетки" << endl;
    return -3;
  }
  if (n[X1][Y1]==1||n[X2][Y2]==1){
    cout<<"Хотя бы одна клетка занята"<<endl;
    return -2;
  }
  x1 = X1;
  y1 = Y1;
  x2 = X2;
  y2 = Y2;
  return 0;
}
class PC : public Domino{ 
  public:
  PC(int x1,int y1, int x2, int y2) : Domino(x1, y1, x2, y2) {};
  virtual int change(int x1, int y1, int x2, int y2, int n[10][10]);
};
int PC::change(int X1, int Y1, int X2, int Y2, int n[10][10]){
  if (Y1<='j' && Y1>='a') Y1 = 9 - (Y1 - 'a');
  else Y1 = 9 - (Y1 - 'A');
  if (Y2<='j' && Y2>='a') Y2 = 9 - (Y2 - 'a');
  else Y2 = 9 - (Y2 - 'A');
  x1 = 9 - X1;
  y1 = Y1;
  x2 = 9 - X2;
  y2 = Y2;
  return 0;
}

void print(int m[10][10]){
  cout << "\n   a b c d e f g h i j\n";
  int a = 1;
  for (int i=0; i<10; i++)
  {
    cout << a;
    if(a != 10) cout<< ' ';
    a++;
    for (int j=0; j<10; j++){
      if(m[i][j] == 0) cout << ' ' << ".";
      else cout << ' ' << "+";
      }  
    cout<< '\n';
  }  
}

int main() {
  int massiv[10][10]={0};
  int flag=0, x1 = 0, x2 = 0;
  char y1 = '\0', y2 = '\0';
  Man man(0, 0, 0, 0);
  PC pc(0, 0, 0, 0);
  print(&massiv[0]);
  while(true){
    cin>>y1>>x1>>y2>>x2;
    x1--;
    x2--;
    flag = man.change(x1,y1,x2,y2,&massiv[0]);
    if (flag == -1 || flag == -3){
      cout<<"Аварийное прерывание игры";
      break;
      }
    if (flag == -2){
      cout<<"Компьютер выиграл";
      break;
    }
    man.fill(&massiv[0]);
    print(&massiv[0]);
    pc.change(x1,y1,x2,y2,&massiv[0]);
    pc.fill(&massiv[0]);
    print(&massiv[0]);
  }
  return 0; 
}
