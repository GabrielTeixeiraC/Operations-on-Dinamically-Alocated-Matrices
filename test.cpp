#include <iostream>

using namespace std;

int main(){
    int linhas = 7;
    int colunas = 11;
    double** matriz = new double*[linhas];
    for (int i = 0; i < linhas; i++){
        matriz[i] = new double[colunas];
    }
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matriz[i][j] = i*colunas + j;
        } 
    }
    double** matriz2 = new double*[colunas];
    for (int i = 0; i < colunas; i++){
        matriz2[i] = new double[linhas];
    }
    for (int i = 0; i < colunas; i++)
    {
        for (int j = 0; j < linhas; j++)
        {
            matriz2[i][j] = 0;
        } 
    }



    cout << "\t";
    for (int i = 0; i < colunas; i++) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < linhas; i++) {
        cout << i;
        for (int j = 0; j < colunas; j++) {
            cout << "\t" << matriz[i][j];
        }
        cout << endl;
    }   
    cout << endl;


    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matriz2[j][i] = matriz[i][j];
        }
    }

    cout << "\t";
    for (int i = 0; i < linhas; i++) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < colunas; i++) {
        cout << i;
        for (int j = 0; j < linhas; j++) {
            cout << "\t" << matriz2[i][j];
        }
        cout << endl;
    }       
    int t = 2;

    for (int i = 0; i < linhas; i++){
        delete[] matriz[i];
    }
    delete[] matriz;
    matriz = NULL;
}