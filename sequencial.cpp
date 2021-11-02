#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void separaDimencoes(size_t *n, size_t *m, std::ifstream *stream)
{
    string stringAuxiliar;

    *stream >> stringAuxiliar;
    *n = stoi(stringAuxiliar);
    *stream >> stringAuxiliar;
    *m = stoi(stringAuxiliar);
}

int main(int argc, char const *argv[])
{
    //teste dos parâmetros de entrada
    if (argc != 3)
    {
        std::cerr << "erro na formatação dos parâmetros de entrada" << std::endl;
        exit(2);
    }
    ifstream matriz1, matriz2;
    ofstream multi;
    string arquivo = "arquivos/";
    arquivo = arquivo + argv[1];
    //abrindo arquivos
    matriz1.open(arquivo, std::ifstream::out);
    arquivo = "arquivos/";
    arquivo = arquivo + argv[2];
    matriz2.open(arquivo, std::ifstream::out);
    if (!matriz1 || !matriz2)
    {
        std::cerr << "Erro ao abrir arquivo de entrada" << std::endl;
        exit(1);
    }

    multi.open("arquivos/sequencial.txt", std::ofstream::out);
    if (!multi)
    {
        std::cerr << "Erro ao abrir arquivo de saida" << std::endl;
        exit(2);
    }
    //salvando as dimenções das matrizes
    size_t *n1 = new size_t,
           *m1 = new size_t,
           *n2 = new size_t,
           *m2 = new size_t;
    separaDimencoes(n1, m1, &matriz1);
    separaDimencoes(n2, m2, &matriz2);

    //liberando memória alocada
    delete n1;
    delete n2;
    delete m1;
    delete m2;
    return 0;
}
