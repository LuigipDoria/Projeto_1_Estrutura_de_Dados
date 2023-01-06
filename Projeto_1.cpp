// Copyright [2022] Luigi Posca Doria

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <string>
#include "array_stack.h"
#include "ArrayQueue.h"

using namespace std;

string GettingName(string str) {
    string name;
    for (int i = 0; i < str.length(); i++) {
        if (i>5 && i<(str.length()-7)){
            name.push_back(str.at(i));
        }
    }
    return name;
}

int GettingLines(string str)
{
    // For atoi, the input string has to start with a digit, so lets search for the first digit
    size_t i = 0;
    for ( ; i < str.length(); i++ ){ if ( isdigit(str[i]) ) break; }

    // remove the first chars, which aren't digits
    str = str.substr(i, str.length() - i );

    // convert the remaining text to an integer
    int id = atoi(str.c_str());
    
    return id;
}

int GettingRows(string str)
{
    // For atoi, the input string has to start with a digit, so lets search for the first digit
    size_t i = 0;
    size_t j;
    size_t parameter_getting_second_dimension = 0;
    while (!(isdigit(str[i]))) {
        i++;
    }
    while(isdigit(str[i])) {
        i++;
    }
    for ( ; i < str.length(); i++ ){ if ( isdigit(str[i]) ) break; }
    // remove the first chars, which aren't digits
    str = str.substr(i, str.length() - i);

    // convert the remaining text to an integer
    int id = atoi(str.c_str());
    
    return id;
}

int GettingFigures(string matrix, int i_matrix, int j_matrix) {
    structures::ArrayQueue<int> fila(i_matrix*j_matrix);
    int Rotulo = 0;
    
    // criando as matrizes E e R
    int **R;
    int **E;
    R = new int *[i_matrix];
    E = new int *[i_matrix];
    for(int i = 0; i < i_matrix; i++) {
        R[i] = new int[j_matrix];
        E[i] = new int[j_matrix];
    }
    
    // Colocando os valores certos na matriz E e preenchendo a matriz R com 0
    int pos_matrix = 0;
    for (int i = 0; i < i_matrix; i++) {
        for (int j = 0; j < j_matrix; j++){
            R[i][j] = 0;
            if (matrix[pos_matrix] == '0') {
                E[i][j] = 0;
            } else {
                E[i][j] = 1;
            }
            pos_matrix ++;
        }
    }

    // fazendo a contagem de quantas figuras tem na imagem
    for (int i = 0; i < i_matrix; i++) {
        for (int j = 0; j < j_matrix; j++) {
            if (E[i][j] == 1 && R[i][j] == 0) {
                Rotulo++;
                R[i][j] = Rotulo;
                fila.enqueue(i);
                fila.enqueue(j);
                while (!fila.empty()) {
                    int i_aux;
                    int j_aux;
                    i_aux = fila.dequeue();
                    j_aux = fila.dequeue();
                    if (i_aux - 1 >= 0          && E[i_aux-1][j_aux] == 1 && R[i_aux-1][j_aux] == 0) {
                        R[i_aux-1][j_aux] = Rotulo;
                        fila.enqueue(i_aux-1);
                        fila.enqueue(j_aux);
                    }
                    if (i_aux + 1 < i_matrix    && E[i_aux+1][j_aux] == 1 && R[i_aux+1][j_aux] == 0) {
                        R[i_aux+1][j_aux] = Rotulo;
                        fila.enqueue(i_aux+1);
                        fila.enqueue(j_aux);
                    }
                    if (j_aux - 1 >= 0          && E[i_aux][j_aux-1] == 1 && R[i_aux][j_aux-1] == 0) {
                        R[i_aux][j_aux-1] = Rotulo;
                        fila.enqueue(i_aux);
                        fila.enqueue(j_aux-1);
                    }
                    if (j_aux + 1 < j_matrix    && E[i_aux][j_aux+1] == 1 && R[i_aux][j_aux+1] == 0) {
                        R[i_aux][j_aux+1] = Rotulo;
                        fila.enqueue(i_aux);
                        fila.enqueue(j_aux+1);
                    }
                }
            }
        }
    }
    return Rotulo;
}

int NumberOfLines(char name[])
{
    int count = 0;
    string line;
    ifstream file(name);
    while (getline(file, line)) count++;
    return count;
}

void TraverseString(string &str)
{ 
    string aux = "";
    for (int i = 0; i < str.length(); i++) {
        aux.push_back(str[i]);
    }
      
}

int main() {
    char xmlfilename[20];
    cin >> xmlfilename;  // entrada
    int number_of_lines = 0;
    int number_of_rows = 0;
    bool erro;
    ifstream archive (xmlfilename);
    
    // problema 1
    if (archive.is_open())
    {
        string linha;
        structures::ArrayStack<string> pilha_de_verificacao(10000);
        while (getline(archive,linha))
        {
            string tag = "";
            bool adicionar = false;
            for (int i = 0; i < linha.length(); i++)
            {
                if (linha[i] == '<')
                {
                    adicionar = true;
                }
                if (linha[i] == '>')
                {
                    adicionar = false;
                    tag.push_back(linha[i]);
                    if (tag == "<height>") {
                        number_of_lines = GettingLines(linha);
                    }
                    if (tag == "<width>") {
                        number_of_rows = GettingRows(linha);
                    }
                    if (tag[1] == '/') {
                        if (pilha_de_verificacao.empty()) {
                            cout << "error\n";
                            erro = true;
                        } else {
                            string aux = pilha_de_verificacao.pop();
                            tag.erase(remove(tag.begin(), tag.end(), '/'), 
                            tag.end());
                            if (aux != tag) {
                                cout << "error\n";
                                erro = true;
                            }
                        }
                    } else {
                        pilha_de_verificacao.push(tag);
                    }
                    tag = "";
                }
                if (adicionar) tag.push_back(linha[i]);
            }
        }
        archive.close();
        if (pilha_de_verificacao.size() != 0) {
            cout << "error\n";
            erro = true;
        }
    }
    // problema 2
    if (erro == false) {
        ifstream file (xmlfilename);
        string matrix;
        string name_figure;
        int number_of_figures;
        int i_matrix = 0;
        int j_matrix = 0;
        if (file.is_open()) {
            string linha;
            while (getline(file,linha)) {
                // Guardando o nome da imagem
                if (linha[1] == 'n') {
                    name_figure = GettingName(linha);
                }
                // Guardando a lagura e a altura da matriz
                if (linha[0] == '0' || linha[0] == '1') {
                    j_matrix = linha.length();
                    i_matrix++;
                    matrix.append(linha);
                }
                // Fazendo a contagem de quantas figuras tem em cada imagem
                if (linha.length() == 6 && linha[1] == '/') {
                    number_of_figures = GettingFigures(matrix, i_matrix, j_matrix);
                    i_matrix = 0;
                    matrix = "";
                    cout << name_figure << " " << number_of_figures << "\n";
                }
            }
        }
        file.close();
    }
    return 0;
}
