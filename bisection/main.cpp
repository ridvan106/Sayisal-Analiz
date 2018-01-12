#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <cstring>

#define iterationSize 100
using namespace std;
double bisection(double a,double b,char *criterion,double epsilon,double (*fonktion)(double));
double f1(double x);
double  f2(double x);
double f3(double x);
double f4(double x);
int main(int argc ,char * argv[]) {
    cout << argc <<endl;
    if(argc != 5){
        cout << "usage ./exe start end criterion epsilon\n";
        return 0;

    }
    else{
        cout << "4.Fonksyon x+1 - (2*sin(180*x)) "<< endl;
        double a =atof(argv[1]);
        double b = atof(argv[2]);
        char * criterion = argv[3];

        double epsilon = atof(argv[4]);
        bisection(a,b,criterion,epsilon,f4);

    }

    return 0;
}
double bisection(double a,double b,char *criterion,double epsilon,double (*fonktion)(double)){
    vector <double> mid;
    int i=0;
    while(i < iterationSize){

        mid.push_back( (a + b )/2); // hesaplanacak deger vektore eklenir
        double result = fonktion(mid[i]); // distence root

        double absoulteEror = abs(mid[i] - mid[i-1]); // absolute eror hesaplama
        double relativeEror = abs((mid[i] - mid[i-1])/mid[i]); // relative eror hesabi
        cout <<i<< ". Iteration : Absolute Eror :" << absoulteEror
                <<" Relative Eror:" << relativeEror << endl;
        //ekrana yazdırma
        if( result == 0 ) { // eger sonuca erisildi ise
            cout << "nice " << endl;
            return 0;
        }// secim gore epsilon degeri DISTANCE_TO_ROOT altında ise
            // program sonlandırılır
        else if(strcmp(criterion,"DISTANCE_TO_ROOT") == 0) {
            if(abs(result) < epsilon){
                cout << "distance root altına dustu yaklasık deger  :"
                     <<mid[i]<<" olarak kabul edilir"<< endl;
                return 0;
            }

        }// secim gore epsilon degeri ABSOLUTE_ERROR altında ise
            // program sonlandırılır
        else if(strcmp(criterion,"ABSOLUTE_ERROR") == 0){
            if(absoulteEror < epsilon){
                cout << "ABSOLUTE_ERROR altına dustu yaklasık deger  :"
                     <<mid[i]<<" olarak kabul edilir"<< endl;
                return 0;
            }
        }// secim gore epsilon degeri RELATIVE_ERROR altında ise
            // program sonlandırılır
        else if(strcmp(criterion,"RELATIVE_ERROR") == 0){
            cout << criterion <<endl;
            if(relativeEror < epsilon){
                cout << "RELATIVE_ERROR altına dustu yaklasık deger  :"
                     <<mid[i]<<" olarak kabul edilir"<< endl;
                return 0;
            }
        }
        if(result < 0){
            a = mid[i];
        }
        else if(result > 0){
            b = mid[i];
        }
    i++;
    }
    if(i >= 100){
        cout << "Yanklasma hatası "<< endl;
        return 0;
    }
}
double f1(double x){

    return (3*x)- exp(x); //1<= x <=2

}
double  f2(double x){

    return (2*x)+(3*cos(x))-exp(x); // 0<= x <=1
}
double f3(double x){
    return x*x - (4*x) +4 -log(x);//1<= x <=2 adnd 2<= x <=4

}
double f4(double x){
    return x+1 - (2*sin(180*x)); // 0 <= x <= 0.5  and 0.5 <= x <=1
}