#include<stdio.h>
#include<math.h>
#include <iostream>
using namespace std;
double product(int x1, int y1,int x2, int y2,int x3,int y3) {
    //首先根据坐标计算p1p2和p1p3的向量，然后再计算叉乘
    //p1p2 向量表示为 (p2.x-p1.x,p2.y-p1.y)
    //p1p3 向量表示为 (p3.x-p1.x,p3.y-p1.y)
    return (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
}
bool isInTriangle(int x1, int y1,int x2, int y2,int x3, int y3,int xo, int yo) {
    //保证p1，p2，p3是逆时针顺序
    if(product(x1, y1, x2, y2, x3, y3)<0) return isInTriangle(x1, y1, x3, y3, x2, y2, xo, yo);
    if(product(x1, y1, x2, y2, x3, y3)>0 && product(x2, y2, x3, y3, xo, yo)>0 && product(x3, y3, x1, y1, xo, yo)>0)
        return true;
    return false;
}
int main(){
    double x[3],y[3],v[3];
    int i;
 
    for( i = 0; i < 3; i++ ){
        printf("please input point%d: ", i+1);
        scanf("%lf%lf", &x[i], &y[i]);
    }
    // 求两点之间距离
    v[0] = sqrt(pow(x[1]-x[0],2)+pow(y[1]-y[0],2));
    v[1] = sqrt(pow(x[2]-x[1],2)+pow(y[2]-y[1],2));
    v[2] = sqrt(pow(x[2]-x[0],2)+pow(y[2]-y[0],2));
//    printf("%.lf %.lf %.lf", v[0],v[1],v[2]);
    if( v[0]+v[1]>v[2] && v[0]+v[2]>v[1] && v[1]+v[2]>v[0]){
        printf("yes");
    }else{
        printf("Impossible");
    }

    int xo, yo;

    cout << "input your p" << endl;
    cin >> xo >> yo;

    bool flag = isInTriangle(x[0], y[0], x[1], y[1], x[2], y[2], xo, yo);
    cout << flag << endl;
 
    return 0;
}


