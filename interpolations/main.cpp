/***    *   *   *   *   *   *   *   *   *   *   *   *   *       *   *
 *      Rıdvan Demirci 14104407                                  *
 *
 * Hocam eklenecek olan matrix matrix.txt dosyasına eklenmeli
methodlar hazır command Line şeklinde
 makeFile ile direk sonucları gorebilirsiniz
*   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
 */
#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

class Matrix{
public:
    double  *val;

};
class Interpolasyon{
public:
    Interpolasyon(const char* FileName){
        //Dosyayı açmak için istenilen fileName
        readFile(FileName);
        //orjinal matrix
        cout << "Ojinal Matrix" << endl;
        printMatrix(this->matrix,row);
    }
    void nearest(int zoom){
        //oluşturulan temp matrix
        Matrix *matrix1;
        //temp Kare matricin boyutları
        int size = zoom *row;
        /** temp Matrix için yer alma işlemi ve sıfıra set etme */
        matrix1 = new Matrix[size];
        for (int i = 0; i <size ; ++i) {
            matrix1[i].val = new double[size];
        }

        for (int k = 0; k < size; ++k) {
            for (int i = 0; i < size; ++i) {
                matrix1[k].val[i] = 0;
            }

        }
        /** *   *   *   *   *   *   *   *   *   *   *   */

        /** Nearest InterPolation   */
        for (int m = 0; m < size; ++m) {

            for (int l = 0; l < size; l+=zoom) {

                //genişletilecek olan indisin degerini alır
                double write = matrix[m/zoom].val[l/zoom];

                for (int j = l; j < l+zoom; ++j) {

                    //genişletilmiş matrixin komşularına yazılır
                    matrix1[m].val[j] = write;


                }
            }
        }
    /** *   *   *   *   *   *   *   *       *   **/
        cout <<"Nearest Interpolation ZOOM: "<<zoom <<"\n";
        printMatrix(matrix1,size);
    }
    void bilinear(int zoom){
        //genişletilecek matrix
        Matrix *matrix1;
        /** yeni matrixin size degeri ve genişletilmiş hallerine yer alınması */

        int size = zoom *row;
        matrix1 = new Matrix[size];
        for (int i = 0; i <size ; ++i) {
            matrix1[i].val = new double[size];
        }
        for (int k = 0; k < size; ++k) {
            for (int i = 0; i < size; ++i) {
                matrix1[k].val[i] = 0;
            }

        }
        /** *   *   *   -*  *   *   *   *   *   */
        /**
         * Bu kısımda matrixin orjinel degerleri farkı zoom degerine bolunur
         * ve yeni oluşturulacak matrixe yazılır
         */
        for (int m = 0; m < size; ++m) {


            for (int l = 0; l < size; l+=zoom) {

                /**
                 * yeni matrixin orta ve uç kısımları
                 */
                double write1 = matrix[m/zoom].val[l/zoom];

                for (int j = l; j < l+zoom; ++j) {

                    /**
                     * eger gelen deger uçlara eklenecekse
                     */
                    if( j==size-1 || j==l){
                        matrix1[m].val[j] = write1;
                    }
                    else{
                        // yeni degere eklenecek olan interpolsayon degeri
                        double write2 = (matrix[m/zoom].val[(l+zoom)/zoom]-matrix[m/zoom].val[l/zoom])/zoom;

                        matrix1[m].val[j] =matrix1[m].val[j-1] + write2;
                    }



                }
            }
        }
        cout <<"Bilineer interpolasyon ZOOM : "<<zoom <<"\n" ;
        printMatrix(matrix1,size);




    }

private:
    Matrix *matrix;
    vector<string> Line;
    ifstream file;
    int row;
    //Dosyadan veri okuma
    void readFile(const char * fileName){
        file.open(fileName);
        if(!file.is_open()){
            cout << "bu Dosya açılamadı" <<endl;
            exit(1);
        }
        while(!file.eof()) {
            string temp;
            getline(file,temp);
            Line.push_back(temp);
        }
        row = Line.size()-1;
        matrix = new Matrix[row];
        for (int k = 0; k < row; ++k) {
            matrix[k].val = new double[row];
        }
        for (int i = 0; i < row; ++i) {
            int point=0;
            string temp = Line[i];
            int p =0;
            for (int j = 0; j < temp.size()+1; ++j) {
                if(temp[j] == ' '){
                    float num;
                    if(point==0)
                        num =atof(temp.substr(point,j-point).c_str());
                    else
                        num =atof(temp.substr(point+1,j-point).c_str());

                    matrix[i].val[p] =num ;
                    p++;
                    point = j;
                }
                            }
            /*---------------------------------- */
            for (int l = 0; l < row; ++l) {
                string num =Line[l].substr(Line[l].find_last_of(' ')+1);

                matrix[l].val[row-1] = atof(num.c_str());
            }
        }



    }
    // matrixi ekrana yazdırır
    void printMatrix(Matrix matrix[],int row){
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < row; ++j) {
                cout << matrix[i].val[j] <<"\t ";

            }
            cout << endl;
        }
    }


};
int main() {
    Interpolasyon i("matrix.txt");
    /**
     * 2 tane fonksyon var nearest ve bilinear
     * çağırıp zoom paramatresi eklenir
     * matrix ise matrix.txt ye verilebilir
     * bicubic kısım yok
     */
    //i.nearest(2);
    //i.nearest(3);
    //i.bilinear(2);
    i.bilinear(3);

    return 0;
}