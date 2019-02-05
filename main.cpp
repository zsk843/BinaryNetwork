#include <iostream>
#include <time.h>
#include <bitset>
#include <cstdlib>

using namespace std;

class layer {

private:
    float** w = new float*;
    float* b = new float;
    float** input = new float*;
    unsigned long long * w_b = new unsigned long long;

    int num_row;
    int hidden_num;
    int dim_num;
    bool is_binary;


public:
    layer(int dim, int hidden, bool if_binary){
        dim_num = dim;
        hidden_num = hidden;
        this->is_binary = if_binary;
        w = new float*[hidden];
        for (int i = 0; i < hidden; i++){
            w[i] = new float[dim];
            srand((unsigned)time(NULL));
            for (int j = 0; j < dim; j++)
                w[i][j] = float(rand()%1000)/1000;
        }

        w_b = new unsigned long long[hidden];
        srand((unsigned)time(NULL));
        for (int i = 0; i < hidden; i++){
            w_b[i] = (unsigned long long)rand();
        }

        b = new float[hidden];
        srand((unsigned)time(NULL));
        for (int i = 0; i < hidden; i++)
            b[i] = float(rand()%1000)/1000;

    }

    float** forward(float** input, int rows){
        float **res = new float *[hidden_num];
        if (is_binary){

            for (int i = 0; i < hidden_num; i++) {
                res[i] = new float[rows];
                for (int j = 0; j < rows; j++) {
                    bitset<200> tem;
                    for (int k = 0; k < 200; k++) {
                        tem[k] = !((w_b[i][k]>0) ^ (w_b[k][j]<=0));
                    }
                    res[i][j] = tem.count() + b[i];
                }
            }
        }
        else {

            for (int i = 0; i < hidden_num; i++) {
                res[i] = new float[rows];
                for (int j = 0; j < rows; j++) {
                    float tmp = 0;
                    for (int k = 0; k < dim_num; k++) {
                        tmp += w[i][k] * w[k][j];
                    }
                    res[i][j] = tmp + b[i];
                }
            }
        }
        return res;
    }

    float** forward(bool** input, int rows){

        float** res = new float*[hidden_num];
        for (int i = 0; i < hidden_num; i++) {
            res[i] = new float[rows];
            for (int j = 0; j < rows; j++) {
                int tem = 0;
                for (int k = 0; k < 200; k++) {
                    tem += !(w_b[i][k] ^ w_b[k][j]);
                }
                res[i][j] = tem + b[i];
            }
        }
        return res;
    }




};

void print_bin(unsigned char n)
{
    int i;
    for(i=sizeof(n)*4-1; i>=0; i --)
    {
        if(n&(1<<i))printf("1");
        else printf("0");
    }
    cout << endl;
}

int main() {
//    layer l = layer(200, 200, false);
//    layer l2 = layer(200, 200, false);
//
//
//
//    float** input = new float*[200];
//    for (int i = 0; i < 200; i++){
//        input[i] = new float[3000];
//        srand((unsigned)time(NULL));
//        for (int j = 0; j < 3000; j++)
//            input[i][j] = float(rand()%1000)/1000;
//    }
//
//    bool** input_b = new bool*[200];
//    for (int i = 0; i < 200; i++){
//        input_b[i] = new bool[3000];
//        srand((unsigned)time(NULL));
//        for (int j = 0; j < 3000; j++)
//            input_b[i][j] = (bool)(rand()%2-1);
//    }
//
//    long start = clock();
//    l2.forward(l.forward(input, 3000), 3000);
//    long stop = clock();
//    cout<< stop-start<<endl;
//
//    start = clock();
//    l2.forward(l.forward(input_b, 3000), 3000);
//    stop = clock();
//    cout<< stop-start<<endl;

    bool* d = new bool[8];
    for(int i = 0; i < 8; i++)
        d[i] = false;

    d[0] = true;
    unsigned  char* a =( unsigned char*) d;
    print_bin(*a);


    cout<<endl<<__built<<endl;

    return 0;
}