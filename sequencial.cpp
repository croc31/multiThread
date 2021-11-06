#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <vector>
//#include <utility>

using namespace std;

void separaDimencoes(size_t *l, size_t *c, std::ifstream *stream)
{
    string stringAuxiliar;

    *stream >> stringAuxiliar;
    *l = stoi(stringAuxiliar);
    *stream >> stringAuxiliar;
    *c = stoi(stringAuxiliar);

    /*stream->seekg(0, stream->end);
    size_t tamanho = stream->tellg();
    stream->seekg(0, stream->beg);

    (*stream).seekg(tamanho / 2);
    (*stream).ignore(256, 'c');
    *stream >> stringAuxiliar;
    cout << stringAuxiliar << endl;*/
}

void pegaLinha(const size_t l, const size_t *c, vector<float> *linha, const map<string, string> *buffer)
{

    for (size_t j = 0; j < *c; j++)
    {
        //o valor l define qual linha será extraída
        //o valor j percorre toda a linha extraindo cada valor
        string auxiliar = "c";
        auxiliar += to_string(l);
        auxiliar += to_string(j);

        linha->push_back(stof((buffer->at(auxiliar))));
    }
}

void pegaColuna(const size_t *l, const size_t c, vector<float> *coluna, const map<string, string> *buffer)
{

    for (size_t j = 0; j < *l; j++)
    {
        //o valor c define qual coluna será estraída
        //o valor j percorre toda a coluna extraindo cada valor
        string auxiliar = "c";
        auxiliar += to_string(j);
        auxiliar += to_string(c);

        coluna->push_back(stof((buffer->at(auxiliar))));
    }
}

void multiplicacao(size_t *l1, size_t *c1, size_t *l2, size_t *c2, std::ifstream *matrizLinha, std::ifstream *matrizColuna, std::ofstream *matrizResul)
{
    map<string, string> bufferLinha, bufferColuna;
    vector<float> linha, coluna;
    while (!matrizLinha->eof())
    {
        string chave, valor;
        *matrizLinha >> chave;
        *matrizLinha >> valor;
        bufferLinha.insert(pair<string, string>(chave, valor));
    }
    while (!matrizColuna->eof())
    {
        string chave, valor;
        *matrizColuna >> chave;
        *matrizColuna >> valor;
        bufferColuna.insert(pair<string, string>(chave, valor));
    }
    //Adicionando as dimenções da matriz
    *matrizResul << *l1 << " " << *c2 << '\n';
    for (size_t i = 0; i < *l1; i++)
    {
        for (size_t j = 0; j < *c2; j++)
        {
            //soma vai armazenar o valor da matriz resultado armazenado em ij
            float soma = 0;
            pegaLinha(i, c1, &linha, &bufferLinha);
            pegaColuna(l2, j, &coluna, &bufferColuna);
            for (size_t k = 0; k < *c2; k++)
            {
                soma += linha[k] * coluna[k];
            }
            *matrizResul << "c" << i + 1 << j + 1 << " " << soma << '\n';
            linha.clear();
            coluna.clear();
        }
    }

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
    ofstream resul;
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

    resul.open("arquivos/sequencial.txt", std::ofstream::out);
    if (!resul)
    {
        std::cerr << "Erro ao abrir arquivo de saida" << std::endl;
        exit(2);
    }
    //salvando as dimenções das matrizes
    size_t *l1 = new size_t,
           *c1 = new size_t,
           *l2 = new size_t,
           *c2 = new size_t;
    separaDimencoes(l1, c1, &matriz1);
    separaDimencoes(l2, c2, &matriz2);
    if (*c1 != *l2)
    {
        std::cerr << "O número de colunas da matriz1 deve ser igual ao número de linhas da matriz 2 " << std::endl;
        exit(3);
    }

    multiplicacao(l1, c1, l2, c2, &matriz1, &matriz2, &resul);
    //liberando memória alocada
    delete l1;
    delete l2;
    delete c1;
    delete c2;
    return 0;
}
