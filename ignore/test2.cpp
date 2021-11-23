#include <iostream>

using namespace std;

int main(){
    FILE * arquivo;
    FILE * gpdat;
    arquivo = fopen("valores.txt", "rt");
    gpdat = fopen("perf.gpdat", "at");
    double valor;
    double total = 0;
    fscanf(arquivo, "%lf ", &valor);
    for (int i = 0; i < 4; i++){
        total += valor;
        fscanf(arquivo, "%lf ", &valor);
    }
    total = total/4;
    fprintf(gpdat, " %lf", total);
}