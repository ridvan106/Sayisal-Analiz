/**
 * Rıdvan Demirci 141044070
 * Least Square ile denklemi ekrana yazar
 * ve kullanıcıdan hesaplanması istenilen sayıyı alır ve hesaplar
	Kitaptaki genelleştirilmiş formul kullanıldı ve oluşan matrix sonucu Gauss ile çözüldü
	2 çeşit çalışma yolu var ilk sadece tek boyutlu array gondermek budurumda indis degerleri
	arrayin indisi olarak kabul edilir.
	2.durum ise 2 boyutlu array gondermek bu durumda 0.indis fonksyon indiskeri 1.indis
	ise o indisklerin fonksyon degerleri olarak kabul edilir.
	ekrana oluşan fonksyon yazılır ve hesaplanacak deger istenir.
 */
#include <iostream>
#include <cmath>
#define DIMENTION 2
using namespace std;
//olusturulacak olan matrix
class Matrix{
public:
    double *m;
    double result;
};

class leastSquare{
private:
    int size;
    double *array;
    double *indis;
    int m;
    int degree;
    double *kaysayilar;
    Matrix *matrix;
    void calculate(){
       //tim indisler için matrix olusturulur
        //genelleştirilmiş formul kullanılıt
        for (int n = 0; n <=m; ++n) {
            matrix[n].result = calculateResult(n);


        }
        /**
         * kitaptaki formul implementi
         */
        for (int i = 0; i <=m; ++i) {
            for (int j = 0; j <= m; ++j) {
                matrix[i].m[j] =sum(size,j+i);
            }
        }
        //olusan matrixe 2. ödevdeki gauss uygulanır

        for (int k = 0; k <=m; ++k) {
            gauss(k);
        }

        // Sonuc ekrana yazdırılır
        calculateofResult();

    }
    double Calculate(int whichRow){
        double sum = 0;
        for (int i = 0; i <=m; ++i) {

            if(i != whichRow){
              //  cout <<"katsayilar" << kaysayilar[i] << endl;
                sum += matrix[whichRow].m[i]*kaysayilar[i];
            }
        }

        return sum;

    }
    void calculateofResult(){
        double temp=0;
        cout << "\tLeast square denklemi\n";
        for (int i = m; i >=0 ; --i) {
            temp = (matrix[i].result - Calculate(i))/matrix[i].m[i];
            this->kaysayilar[i] = temp;
            cout << temp;
            if(i!= 0)
                cout  <<"X^" <<i <<" + ";
        }

        double val;
        cout << "\nHesaplamak istediğiniz deger: ";
        cin >> val;
        double sum =0;
        for (int j = 0; j <=m; ++j) {
            sum += this->kaysayilar[j] * pow(val,j);
        }
        cout << "sonuc : " << sum;

    }
    double sum(int to,int degree){
        double summ = 0;
        for (int i = 0; i < to; ++i) {
            summ += pow(indis[i],degree);
        }
        return summ;

    }
    double calculateResult(int degree){
        /**
         * kitaptaki formulun implementi
         */
        double summ = 0;
        for (int i = 0; i <size ; ++i) {
            summ += array[i]*pow(this->indis[i],degree);
        }
        return summ;
    }

public:
    /*
     * sadece tek boyutlu array hesabı
     */
    void setArray(double arr[],int size ,int m){
        if(!(m < size -1)){
            cout << "boyle kosul olmaz (n < m-1) olmalı" << endl;
            exit(1);
        }
        this->size = size;
        this->m = m;

        matrix = new Matrix[size+1];
        this->kaysayilar = new double[size+1];
                array = new double[size];
        indis = new double[size];

        for (int i = 0; i < size+1; ++i) {
            matrix[i].m = new double[size+1];

        }
        // olusturulacak fonksyon için yer alınır
        //ve indis arrayine normal 0-1-2 diye indisler atılır
        //cünki tek boyutlu
        //array listesine de kordinate degerleri atılır

        for (int j = 0; j < size; ++j) {
            array[j] = arr[j];
            indis[j] = j;
        }
        calculate();



    }
    void setArray(double *arr[],int size,int m){
        //exit kondition
        if(!(m < size -1)){
            cout << "boyle kosul olmaz (n < m-1) olmalı" << endl;
            exit(1);
        }
        /**
         * Matrixin boyut alımları ve indis degerleri ve kordinatların
         * set işlemleri
         */
        this->size = size;
        this->m = m;
        matrix = new Matrix[size+1];
        this->kaysayilar = new double[size+1];
        array = new double[size];
        this->indis = new double[size];
        for (int i = 0; i < size+1; ++i) {
            matrix[i].m = new double[size+1];

        }
        for (int j = 0; j < size; ++j) {
            array[j] = arr[1][j];
            this->indis[j] = arr[0][j];
        }
        /*  *   *   *   *   *   *   *   *   *   *   *   */
        //hesaplama kısmı
        calculate();
    }
    void gauss(int line){
        int sline = line;
        for (int i = line+1; i <=m; ++i) {
            double katsayi = matrix[i].m[sline] / matrix[sline].m[sline];  //E1(e2*e1

            for (int j = 0; j <=m; ++j) {
                // matrix degerlerini duzenleme
                matrix[i].m[j]= matrix[i].m[j]- (matrix[sline].m[j])*katsayi;

            }
            matrix[i].result = matrix[i].result - matrix[sline].result*katsayi; // eşit çıktısının degerini hesaplama
        }


    }

};

int main() {
    leastSquare square,kordinate ;
    double x[]={1.0000,1.2840,1.6487,2.117,2.7183};
    double x2[]={1.3,3.5,4.2,5,7,8.8,10.1,12.5,13,15.6};
    double *kordinateArray[DIMENTION];

    for (int i = 0; i < DIMENTION; ++i) {
        kordinateArray[i] = new double[5];
    }
    //Kitaptaki Array Kordinatları
    kordinateArray[0][0] =0;    kordinateArray[1][0]=1;
    kordinateArray[0][1] =0.25;    kordinateArray[1][1]=1.2840;
    kordinateArray[0][2] =0.5;    kordinateArray[1][2]=1.6487;
    kordinateArray[0][3] =0.75;    kordinateArray[1][3]=2.117;
    kordinateArray[0][4] =1;    kordinateArray[1][4]=2.7183;


    cout <<endl;
    //Hesaplama kısmı setArray ile yapılır
    //kordinate Array ,Array size ve m degeri lazım
    square.setArray(kordinateArray,5,2);
    cout <<endl;
    //square.setArray(x2,10,1);
    return 0;
}
