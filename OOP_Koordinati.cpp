#include <iostream>
using namespace std;
class Line;
class Dot{
  friend class Line;
  friend istream &operator>>(istream&, Dot&);
  friend ostream &operator<<(ostream&, Dot&);
private:
  int x;
  int y;
public:
  Dot(int xx=0, int yy=0) : x(xx), y(yy) {};};
class Line{
private:
  Dot p1;
  Dot p2;
public:
  Line(Dot &p, Dot &q) : p1(p), p2(q) {};
  void intxy();};
void Line::intxy(){
  float dx = p2.x - p1.x;
  int dy = p2.y - p1.y;
  int i;
  float y_;
  if (p1.x == p2.x)
    for(i=min(p1.y, p2.y); i <= max(p1.y, p2.y); i++){
      Dot A(p1.x, i);
      cout << A << " ";}
  else
    for(i=min(p1.x, p2.x); i <= max(p1.x, p2.x); i++){
      y_ = dy*(i - p1.x)/dx + p1.y;
      if (y_ == int(y_)){
        Dot A(i, int(y_));
        cout << A << " ";}}
  cout << end;}
istream &operator>>(istream &input, Dot &p){
  char semicolon=';';
  input >> p.x >> semicolon >> p.y;
  return input;}
ostream &operator<<(ostream &output, Dot &p){
  char semicolon=';';
  output << p.x << semicolon << p.y;
  return output;}
int main(){
  Dot A, B;
  cout << "Input xa;ya xb;yb or exit" << endl;
  while(cin >> A >> B){
    Line lx(A, B);
    lx.intxy();
    cout << "Input xa;ya xb;yb or exit" << endl;}
  return (0);}

