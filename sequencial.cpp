#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <vector>
//#include <utility>

using namespace std;

void separaDimencoes(size_t *n, size_t *m, std::ifstream *stream)
{
    string stringAuxiliar;

    *stream >> stringAuxiliar;
    *n = stoi(stringAuxiliar);
    *stream >> stringAuxiliar;
    *m = stoi(stringAuxiliar);

    /*stream->seekg(0, stream->end);
    size_t tamanho = stream->tellg();
    stream->seekg(0, stream->beg);

    (*stream).seekg(tamanho / 2);
    (*stream).ignore(256, 'c');
    *stream >> stringAuxiliar;
    cout << stringAuxiliar << endl;*/
}

void pegaLinha(const size_t n, const size_t *m, vector<float> *linha, const map<string, string> *buffer)
{

    for (size_t j = 0; j < *m; j++)
    {
        string auxiliar = "c";
        auxiliar += to_string(n);
        auxiliar += to_string(j);

        //cout << "erro aqui" << endl;
        linha->push_back(stof((buffer->at(auxiliar))));
    }
}

void pegaColuna(const size_t *n, const size_t m, vector<float> *coluna, const map<string, string> *buffer)
{

    for (size_t j = 0; j < *n; j++)
    {
        string auxiliar = "c";
        auxiliar += to_string(j);
        auxiliar += to_string(m);

        //cout << "erro aqui" << endl;
        coluna->push_back(stof((buffer->at(auxiliar))));
    }
}

void fazBuffer(size_t *n1, size_t *m1, size_t *n2, size_t *m2, std::ifstream *matrizColuna, std::ifstream *matrizLinha)
{
    map<string, string> buffer;
    vector<float> linha, coluna;
    while (!matrizLinha->eof())
    {
        string chave, valor;
        *matrizLinha >> chave;
        *matrizLinha >> valor;
        buffer.insert(pair<string, string>(chave, valor));
    }
    pegaLinha(1, m1, &linha, &buffer);
    pegaColuna(n1, 1, &coluna, &buffer);
    // cout << "linha" << endl;
    // for (auto &e : linha)
    // {
    //     cout << e << endl;
    // }
    // cout << '\n'
    //      << "Coluna" << endl;
    // for (auto &e : coluna)
    // {
    //     cout << e << endl;
    // }
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
    if (*m1 != *n2)
    {
        std::cerr << "O número de colunas da matriz1 deve ser igual ao número de linhas da matriz 2 " << std::endl;
        exit(3);
    }

    fazBuffer(n1, m1, n2, m2, &matriz1, &matriz2);
    //liberando memória alocada
    delete n1;
    delete n2;
    delete m1;
    delete m2;
    return 0;
}
