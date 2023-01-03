// Q2 - Given radius of a circle. Write a function to print the area and circumference of the circle.(Easy)
//     Sample Input: r=3
//     Sample Output: Area : 28.26
//             Circumference : 18.84
#include<iostream>
using namespace std;
float circumference(float radius){
    float circum;
    circum=2*3.14*radius;
    return circum;
}
float area(float radius){
    float area=3.14*radius*radius;
    return area;
}
int main(){
    float radius;
    cout<<"enter radius: ";
    cin>>radius;
    cout<<"Area : "<<area(radius)<<endl<<"Circumference : "<<circumference(radius);
    return 0;
}