#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;
pthread_t *threads = NULL;
size_t *l1,
    *c1,
    *l2,
    *c2,
    *p;
vector<vector<float>> bufferLinha, bufferColuna;
void *thread_return;

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
// //essa função guarda no vector 'linha' a linha numero 'l'
// void pegaLinha(const size_t l, const size_t *c, vector<float> *linha)
// {

//     for (size_t j = 0; j < *c; j++)
//     {
//         //o valor l define qual linha será extraída
//         //o valor j percorre toda a linha extraindo cada valor
//         float auxiliar = bufferLinha[l][j];
//         linha->push_back(auxiliar);
//         //cout << "posi " << l << " " << j << endl;
//     }
// }
// //essa função guarda no vector 'coluna' a coluna numero 'c'
// void pegaColuna(const size_t *l, const size_t c, vector<float> *coluna)
// {

//     for (size_t j = 0; j < *l; j++)
//     {
//         //o valor c define qual coluna será estraída
//         //o valor j percorre toda a coluna extraindo cada valor
//         float auxiliar = bufferColuna[j][c];

//         coluna->push_back(auxiliar);
//     }
// }

//esse método controla todas as chamadas de multiplicação
void *multiplicacao(void *o)
{
    if ((int)(size_t)o > 0)
    {
        cout << (int)(size_t)o << endl;
        pthread_join(threads[((size_t)o) - 1], &thread_return);
    }

    ofstream matrizResul;
    string caminho = "arquivos/thread";
    caminho += to_string((size_t)o);
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
    i = int((*p * (int)(size_t)o) / *c2);
    j = (*p * (int)(size_t)o) % *c2;
    while (count < *p)
    {
        //Soma vai armazenar o valor da matriz resultado armazenado na posição ij
        float soma = 0;
        // pegaLinha(i, c1, &linha);
        // pegaColuna(l2, j, &coluna);
        for (size_t k = 0; k < *c1; k++)
        {
            soma += bufferLinha[i][k] * bufferColuna[k][j];
            //cout << linha[k] << " + " << coluna[k] << endl;
            //cout << soma << endl;
        }
        matrizResul << "c" << i + 1 << j + 1 << " " << soma << '\n';
        linha.clear();
        coluna.clear();

        j++;
        if (j >= *c2)
        {
            i++;
            j = int((*p * (int)(size_t)o) / *c2);
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
    cout << "fim do filho " << (size_t)o << endl;
    sleep(1);
    pthread_exit(NULL);
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
    //alocando o espaço das variáveis

    l1 = new size_t;
    c1 = new size_t;
    l2 = new size_t;
    c2 = new size_t;
    p = new size_t;
    *p = stoi(argv[3]);
    threads = new pthread_t[(*l1 * *c2) / (*p)];
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

    bufferLinha.resize(*l1);
    bufferColuna.resize(*l2);
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
    // for (auto e : bufferColuna)
    // {
    //     for (auto f : e)
    //     {
    //         cout << f << " : ";
    //     }
    //     cout << endl;
    // }

    //fechando arquivos
    matriz1.close();
    matriz2.close();

    for (size_t i = 0; i < (*l1 * *c2) / (*p); i++)
    {
        cout << "criando filho " << i << endl;
        int status = pthread_create(&threads[i], NULL, multiplicacao, (void *)(size_t)i);
        if (!!status)
        {
            cout << "Error: " << status << endl;
            return (-1);
        }
    }

    pthread_join(threads[(*l1 * *c2) / (*p) - 1], &thread_return);

    //liberando memória alocada
    delete l1;
    delete l2;
    delete c1;
    delete c2;
    delete p;
    delete threads;
    return 0;
}
