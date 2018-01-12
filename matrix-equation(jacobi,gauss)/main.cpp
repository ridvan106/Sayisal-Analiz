#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;
class matrix{
private:
    //dosya pointer
    ifstream Filematrix;
    // matrix linelarını alır
    vector<string> Line;
    //matrix valuları alır
    //maximum 100 calumn
    double *valueOfmatrix[100];
    // matrixin kopyası jacobi hesabı için
    double *tempOfmatrix[100];
    //matrixin eşit
    double *b; // matrixin eşit olan değerleri
    // eski degeri
    double *oldValue;
    // row sayısı
    int row;
    //column sayısı
    int col;
    //secilecek olan pivot
    double *pivots;
    // dosya okuma
    void readFile(const char * fileName){
        Filematrix.open(fileName);
        if(!Filematrix.is_open()){
            cout << "bu Dosya açılamadı" <<endl;
            exit(1);
        }

    }
    // txt den matrixi okuyup vektore atar
    void fillmatrix(){
        while(!Filematrix.eof()){
            string temp;
            getline(Filematrix,temp);
            Line.push_back(temp);

        }

    }
    // line daki virgul sayısını alır
    int numOfCamma(string str){
        int count = 0;
        for (int i = 0; i < str.size(); ++i) {
            if(str[i] == ',')
                count++;
        }
    return count;
    }
    void fiilvalue(){
         row = Line.size()-1;
         //column sayısı virgulden bir fazladır
         col = numOfCamma(Line[0])+1;
        // column tempi
         int colTemp = Line[0].size();

        // matrixlere yer alma
        for (int k = 0; k < row; ++k) {
            valueOfmatrix[k] = new double[row];
            tempOfmatrix[k] = new double[row];
        }
        b= new double[row]; // sonuc matrixinin olusturulması
        oldValue = new double[row]; // temp b valueları
        pivots = new double[row];//pivat arrayin olusumu
        /*
         *  valueOf matrixi ve tempMatrixe degerlerşn atanması
         */
        for (int i = 0; i < row; ++i) {
            int point=0;
            string temp = Line[i];
            int p =0;
            for (int j = 0; j < temp.size()+1; ++j) {
                if(temp[j] == ','){
                    float num;
                    if(point==0)
                        num =atof(temp.substr(point,j-point).c_str());
                    else
                        num =atof(temp.substr(point+1,j-point).c_str());

                    valueOfmatrix[i][p] =num ;
                    tempOfmatrix[i][p] = num;
                    p++;
                    point = j;
                }

            }
            /*---------------------------------- */
        }
        // b matrixinin eşiti alınması
        for (int l = 0; l < row; ++l) {
            string num =Line[l].substr(Line[l].find_last_of(',')+1);

             b[l] = atof(num.c_str());
        }
    }
    // satırdaki buyuk orana sahip pivotu alır
    void setPivot(){

        for (int i = 0; i < row; ++i) {
                 pivots[i] = abs(valueOfmatrix[i][0]);
            for (int j = 0; j < col-1; ++j) {
                if(abs(valueOfmatrix[i][j])> pivots[i]){
                    pivots[i] = abs(valueOfmatrix[i][j]);

                }
                
            }
            
        }
        checkPivot();
    }
    // pivot sıfır olmamalı
    void checkPivot(){
        for (int i = 0; i < row; ++i) {
            if(pivots[i]==0){
                cout << "NO SOLUTİON" <<endl;
                exit(1);
             }
        }
    }
    // satır degişikliği sonrası oluşan yeni matrix
    void setNewMatrix(){


        for (int i = 0; i < row; ++i) {
            int whichrow=i;

            double max = abs(valueOfmatrix[0][0])/pivots[i];
            for (int j = i; j < row; ++j) {
                double temp = abs(valueOfmatrix[j][i])/pivots[j];
               // cout <<"oran:"<< temp ;
                if(temp > max){
                    whichrow = j;
                    max = temp;
                                  }
            }
                swap(b[whichrow],b[i]);
                swap(valueOfmatrix[whichrow],valueOfmatrix[i]);
                swap(pivots[i],pivots[whichrow]);
                gauss(i);
    }
    }
    // satır sutun degiştikten sonta matrixe gauss uygulanması
    void gauss(int line){
        int sline = line;
        for (int i = line+1; i < row; ++i) {
            double katsayi = valueOfmatrix[i][sline] / valueOfmatrix[sline][sline];  //E1(e2*e1

            for (int j = 0; j < col; ++j) {
                // matrix degerlerini duzenleme
                valueOfmatrix[i][j]= valueOfmatrix[i][j]- (valueOfmatrix[sline][j])*katsayi;

            }
            b[i] = b[i] - b[sline]*katsayi; // eşit çıktısının degerini hesaplama
           // cout << "katsayı " << katsayi << endl;
        }


    }
    // jacobide eşit degerleri bulur
    double resultNew(int whichRow){
        double sum = 0;
        for (int i = 0; i < row; ++i) {

            if(i != whichRow){
                sum += tempOfmatrix[whichRow][i]*oldValue[i];
            }
        }
    }
    
    // jacobide X1 i felan hesaplar
    double Calculate(int whichRow){
        double sum = 0;
        for (int i = 0; i < row; ++i) {

            if(i != whichRow){
                sum += valueOfmatrix[whichRow][i]*oldValue[i];
            }
        }
        
    }
    // yeni olusan jacobileri sıfırlar baslangıc için
    void setOld(double val){
        for (int i = 0; i < row; ++i) {
            oldValue[i] = val;
        }
    }
    // yeni olusan jacobileri onceki degerleri atar
    void setOld2(){
        for (int i = 0; i < row; ++i) {
            oldValue[i] = valueOfmatrix[i][i];
        }
    }
    // hata heasbını hesaplar
    bool Eror(){
        double eror = 0.001;
        double temp = 0;
        for (int i = 0; i < row; ++i) {
            temp = (abs(valueOfmatrix[i][i] - oldValue[i]))/abs(valueOfmatrix[i][i]);

            if((temp > eror))
                return false;
        }
        return true;
    }
    // yakınlaşıp yakınlaşmadıgına bakar Diagonal matrix ile
    bool isConvergent(){
        for (int i = 0; i < row; ++i) {
            double sum =0;
            for (int j = 0; j < col; ++j) {
                if(i != j)
                sum += abs(valueOfmatrix[i][j]);
            }
            if(!(valueOfmatrix[i][i] > sum))
                return false;
        }
        return true;
        
    }
    // gouss da hesaplanan sonucu ekrana yazar
    
    void calculate(){
        double temp=0;
        for (int i = row-1; i >=0 ; --i) {
            temp = (b[i] - Calculate(i))/valueOfmatrix[i][i];
            oldValue[i] = temp;
            cout <<"X" <<i<<" = "<< temp <<endl;
        }

    }
public:
    // constructure fileName i alıp matrixi oluşturur
    matrix(char * fileName){
        this->readFile(fileName);
        this->fillmatrix();
        this->fiilvalue();

    }
    // matrixi ekrana yazdırır
    void printMatrix(){
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col-1; ++j) {
                cout << valueOfmatrix[i][j] <<"\t ";

            }
            cout <<"\t= " <<b[i] << endl;
        }
    }
    // gauss hesabını çagırır
    void scaledPivot(){
        this->setPivot();
        this->setNewMatrix();
        this->printMatrix();
        calculate();
    }
    // jacobi hesabını yapar
    void jacobiMethod() {
        if (isConvergent()) {
            setOld(0);
            while (true) {
                for (int i = 0; i < row; ++i) {

                    valueOfmatrix[i][i] = (b[i] - resultNew(i)) / tempOfmatrix[i][i];

                }
                if (!Eror())
                    setOld2();
                else
                    break;
            }
            for (int j = 0; j < row; ++j) {
                cout <<" X"<<j<<" = " << valueOfmatrix[j][j] << endl;
            }


        } else {
            cout << "Bu matrix jacobi ile yakınsamaz" << endl;
        }

    }
};
int main(int argc ,char * argv[]) {

    if(argc != 5){
        cout << "usage :  ./solver -i system.txt -m -GESP"<< endl;
    }
    else {

        matrix matrix1(argv[2]);
        cout << argv[4]<< endl;

        if (strcmp(argv[4],"-GESP") == 0) {
            matrix1.scaledPivot();
        }
            else if(strcmp(argv[4],"-JCB") == 0)
        {
            matrix1.jacobiMethod();
        }
        else{
            cout << "Geçersiz Denklem Çözüm Tipi "<< endl;
        }
    }
    return 0;
}
