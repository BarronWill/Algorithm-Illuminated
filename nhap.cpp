#include <bits/stdc++.h>
using namespace std;

void nhap (pair<int,int>& temp){
    cin>>temp.first>>temp.second;
}

float DienTich(int x1, int y1, int x2, int y2, int x3, int y3){
    return abs((float)(x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2);
}

bool Kiemtra(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y){
    float S = DienTich (x1, y1, x2, y2, x3, y3);
    float S1 = DienTich (x, y, x2, y2, x3, y3);
    float S2 = DienTich (x1, y1, x, y, x3, y3);
    float S3 = DienTich (x1, y1, x2, y2, x, y);
return (S == S1 + S2 + S3) ? true : false;
}

int main(){
    pair<int,int> a,b,c,d;
    nhap(a);nhap(b);nhap(c);nhap(d);
    if (Kiemtra(a.first, a.second, b.first, b.second, c.first, c.second, d.first, d.second))
        cout <<"Trong";
    else
        cout <<"Ngoai";
    return 0;
}

