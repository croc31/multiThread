#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

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

//esse método controla todas as chamadas de multiplicação
void multiplicacao(const size_t *l1, const size_t *c1, const size_t *l2, const size_t *c2, const float *p, const size_t o, vector<vector<float>> *matrizLinha, vector<vector<float>> *matrizColuna)
{

    ofstream matrizResul;
    string caminho = "arquivos/processos";
    caminho += to_string(o);
    caminho += ".txt";
    matrizResul.open(caminho, std::ofstream::out);
    if (!matrizResul)
    {
        std::cerr << "Erro ao abrir arquivo de saida" << std::endl;
        exit(2);
    }
    std::chrono::steady_clock::time_point inicio, final;

    inicio = std::chrono::steady_clock::now();
    vector<float> linha, coluna;

    //Adicionando as dimenções da matriz resultante
    matrizResul << *l1 << " " << *c2 << '\n';
    size_t i, j, count = 0;
    i = int((*p * o) / *c2);
    j = int((*p * o)) % *c2;
    while (count < *p)
    {
        //Soma vai armazenar o valor da matriz resultado armazenado na posição ij
        float soma = 0;
        // pegaLinha(i, c1, &linha, matrizLinha);
        // pegaColuna(l2, j, &coluna, matrizColuna);
        for (size_t k = 0; k < *c1; k++)
        {

            soma += (*matrizLinha)[i][k] * (*matrizColuna)[k][j];
        }
        matrizResul << "c" << i + 1 << j + 1 << " " << soma << '\n';
        linha.clear();
        coluna.clear();

        j++;
        if (j >= *c2)
        {
            i++;
            j = 0;
            if (i >= *l1)
            {
                break;
            }
        }
        count++;
    }
    final = std::chrono::steady_clock::now();
    std::chrono::duration<double> duracao = std::chrono::duration_cast<std::chrono::duration<double>>(final - inicio);
    matrizResul << duracao.count();
    cout << duracao.count();
}

int main(int argc, char const *argv[])
{
    //teste dos parâmetros de entrada
    if (argc != 4)
    {
        std::cerr << "erro na formatação dos parâmetros de entrada" << std::endl;
        exit(2);
    }
    ifstream matriz1, matriz2;
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
    size_t *l1 = new size_t,
           *c1 = new size_t,
           *l2 = new size_t,
           *c2 = new size_t;
    float *p = new float;
    *p = stoi(argv[3]);
    //salvando as dimenções das matrizes
    separaDimencoes(l1, c1, &matriz1);
    separaDimencoes(l2, c2, &matriz2);
    //caso o número de colunas da matriz 1 seja diferente do número de linhas
    //da matriz 2 a multiplicação não pode ser feita
    if (*c1 != *l2)
    {
        std::cerr << "O número de colunas da matriz1 deve ser igual ao número de linhas da matriz 2 " << std::endl;
        exit(3);
    }
    //transformando as matrizes em objetos vector<vector> para deixar a busca por
    //elementos mais eficiente

    vector<vector<float>> bufferLinha(*l1),
        bufferColuna(*l2);
    for (size_t i = 0; i < *l1; i++)
    {
        for (size_t j = 0; j < *c1; j++)
        {
            string numero;
            matriz1 >> numero;
            matriz1 >> numero;
            bufferLinha[i].push_back(stof(numero));
        }
    }
    for (size_t i = 0; i < *l2; i++)
    {
        for (size_t j = 0; j < *c2; j++)
        {
            string numero;
            matriz2 >> numero;
            matriz2 >> numero;
            bufferColuna[i].push_back(stof(numero));
        }
    }

    //fechando arquivos
    matriz1.close();
    matriz2.close();
    for (size_t i = 0; i < ceil((*l1 * *c2) / (*p)); i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            cerr << "Failed to fork" << endl;
        }
        else if (!pid)
        {
            multiplicacao(l1, c1, l2, c2, p, i, &bufferLinha, &bufferColuna);
            break;
        }
    }
    cout << endl;

    //cout << "o processo terminou a execução " << endl;
    //liberando memória alocada
    delete l1;
    delete l2;
    delete c1;
    delete c2;
    delete p;
    return 0;
}
