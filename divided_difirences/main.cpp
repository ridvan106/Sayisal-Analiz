/**
 * Rıdvan Demirci 141044070
 * 2 çeşit çalışma yolu var ilk sadece tek boyutlu array gondermek budurumda indis degerleri
	arrayin indisi olarak kabul edilir.
	2.durum ise 2 boyutlu array gondermek bu durumda 0.indis fonksyon indiskeri 1.indis
	ise o indisklerin fonksyon degerleri olarak kabul edilir.
 Hesaplama işlemi bittikten sonra ekrana polinom yazılır ve hesaplanması istenilen deger sorulur
 girildikten sonra deger hesaplanır

 */
#include <iostream>
#define DIMENTION 2

using namespace std;

class values{
public:
    double * valu;
};
class divedDiff{
private:
    int size;
    double x;
    values *degerler;
    void setXindis(){
        for (int i = 0; i < size; ++i) {
            degerler[0].valu[i]=i;
        }
    }
    void printFx(){
        for (int i = 0; i < size; ++i) {
            cout << degerler[0].valu[i] << " " <<  degerler[1].valu[i] <<endl;

        }
    }
    // dived diffreance calculate
    void calculate(){
        /*
         * Bu hesaplama işlemi kitapta mevcuttur tablo yardımı ile oluşturulur
         * chapte 3.3 table 3.9
         */
        for (int i = 0; i <= size -2; ++i) {
            double indis = degerler[0].valu[i+1] - degerler[0].valu[0];
            for (int j = 0; j < (size - i -1); ++j) {
                degerler[i+2].valu[j] =(degerler[i+1].valu[j+1]-degerler[i+1].valu[j]) / indis;

            }

            
        }
        /**
         * Oluşan polinomun ekrana yazdırılması
         */
        print();


    }
    void print(){
        /**
         * Oluşan polinomun ekrana yazdırılması
         * FORMATI
         * P n (x) = f [x 0 ] + f [x 0 , x 1 ](x − x 0 ) + a 2 (x − x 0 )(x − x 1 ) ....
         */
        cout << "Olusan polinom\n";
        cout <<"P(X)= ";
        for (int i = 0; i < size; ++i) {
            double katSayi = degerler[i+1].valu[0];
            cout << katSayi;
            double temp =1;
            for (int j = 0; j < i; ++j) {
                cout <<"(x-"<<degerler[0].valu[j]<<")";
            }
            if(i != size-1)
            cout <<" + ";
        }


    }
    void result(){
        /*
         * alınan x degerini polinomda yerine yazar
         */

        double sum = 0;

        for (int i = 0; i < size; ++i) {
            double katSayi = degerler[i+1].valu[0];
            double temp =1;
            for (int j = 0; j < i; ++j) {
                temp *= (x - degerler[0].valu[j]);

            }
            sum += katSayi*temp;
        }
        cout << " = " <<sum <<endl;

    }
public:

    void setValues(double arr[],int size){
        cout << "Lütfen hesaplanacak degeri girin:";
        cin >> x;
        /**
         * sadece array alır kordinatlar 0-1-2 .. array kordinatları dır
         *
         * Value table'nin set işlemleri
         */

        this->size = size;
        degerler = new values[size+1];
        degerler[1].valu = new double[size];
        degerler[0].valu = new double[size];
        setXindis();
        for (int i = size; i >= 2; i--) {
            degerler[i].valu = new double[size-i];

        }
        for (int j = 0; j < size; ++j) {
            degerler[1].valu[j] = arr[j];
        }
    /*  *   *   *   *   *   *   *   *   *   */
        calculate();
        result();
    }
    void setValues(double *KordinateAray[],int size){
        // hesaplanacak deger set edilir
        cout << "Lütfen hesaplanacak degeri girin:";
        cin >> x;
        /*
         * Olustırulacak value kordinatlarının indis ve value degerlerinin set işlemi
         */


        this->size = size;
        degerler = new values[size+1];
        degerler[1].valu = new double[size];
        degerler[0].valu = new double[size];

        for (int i = 0; i < size; ++i) {
            degerler[0].valu[i]=KordinateAray[0][i];
        }
        for (int i = size; i >= 2; i--) {
            degerler[i].valu = new double[size-i];

        }
        for (int j = 0; j < size; ++j) {
            degerler[1].valu[j] = KordinateAray[1][j];
        }
        /*  *   *   *   *   *   *   *       **/
        calculate();
        //Hesaplanacak deger x'e atılır

        result();
    }




};

int main() {

    // dived diffirences classı
    divedDiff a;
    double k[] = {0.7651977,0.6200860,0.4554022,0.2818186,0.1103623};
    double indis[]={1,1.3,1.6,1.9,2.2};
    double *kordinateArray[DIMENTION];
    for (int i = 0; i < 2; ++i) {
        kordinateArray[i] = new double[5];
    }
    //3.3 example 1
    kordinateArray[0][0] = 1; kordinateArray[1][0] = 0.7651977;
    kordinateArray[0][1] = 1.3; kordinateArray[1][1] = 0.6200860;
    kordinateArray[0][2] = 1.6; kordinateArray[1][2] = 0.4554022;
    kordinateArray[0][3] = 1.9; kordinateArray[1][3] = 0.2818186;
    kordinateArray[0][4] = 2.2; kordinateArray[1][4] = 0.1103623;
    /**
     * fonksyon çalıştırılırken
     * setValue(ikiBoyutlu Kordinate arrayi,arraysize)
     * veya
     * setValue(tekboyutlu Array,arraysize);
     */
    cout << endl;
    // istenilen method
    a.setValues(kordinateArray,5);




    return 0;
}