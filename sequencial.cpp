#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <vector>
#include <chrono>
//#include <utility>

using namespace std;

//essa função extrai as dimençõesda matriz 'stream' e as armazena
// nas variáveis 'l' e 'c'
void separaDimencoes(size_t *l, size_t *c, std::ifstream *stream)
{
    string stringAuxiliar;

    *stream >> stringAuxiliar;
    *l = stoi(stringAuxiliar);
    *stream >> stringAuxiliar;
    *c = stoi(stringAuxiliar);
}
//essa função guarda no vector 'linha' a linha numero 'l'
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
//essa função guarda no vector 'coluna' a coluna numero 'c'
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

void multiplicacao(std::ifstream *matrizLinha, std::ifstream *matrizColuna, std::ofstream *matrizResul)
{
    map<string, string> bufferLinha, bufferColuna;
    vector<float> linha, coluna;
    size_t *l1 = new size_t,
           *c1 = new size_t,
           *l2 = new size_t,
           *c2 = new size_t;

    //salvando as dimenções das matrizes
    separaDimencoes(l1, c1, matrizLinha);
    separaDimencoes(l2, c2, matrizColuna);
    //caso o número de colunas da matriz 1 seja diferente do número de linhas
    //da matriz 2 a multiplicação não pode ser feita
    if (*c1 != *l2)
    {
        std::cerr << "O número de colunas da matriz1 deve ser igual ao número de linhas da matriz 2 " << std::endl;
        exit(3);
    }

    //transformando as matrizes em objetos map para deixar a busca por
    //elementos mais eficiente
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

    //Adicionando as dimenções da matriz resultante
    *matrizResul << *l1 << " " << *c2 << '\n';
    for (size_t i = 0; i < *l1; i++)
    {
        for (size_t j = 0; j < *c2; j++)
        {
            //Soma vai armazenar o valor da matriz resultado armazenado na posição ij
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
    //liberando memória alocada
    delete l1;
    delete l2;
    delete c1;
    delete c2;
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
    std::chrono::steady_clock::time_point inicio, final;

    inicio = std::chrono::steady_clock::now();
    multiplicacao(&matriz1, &matriz2, &resul);
    final = std::chrono::steady_clock::now();
    std::chrono::duration<double> duracao = std::chrono::duration_cast<std::chrono::duration<double>>(final - inicio);
    resul << duracao.count();
    matriz1.close();
    matriz2.close();
    resul.close();
    return 0;
}
