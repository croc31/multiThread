#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>

void formacaoDaMatriz(size_t n, size_t m, std::string arquivo)
{
    std::ofstream matriz;
    matriz.open(arquivo, std::ofstream::out);
    srand(time(NULL));

    if (!matriz)
    {
        std::cerr << "Erro ao abrir o arquivo " << std::endl;
        exit(1);
    }

    try
    {
        matriz << n << " " << m << std::endl;
        for (size_t i = 0; i < size_t(n); i++)
        {
            for (size_t j = 0; j < size_t(m); j++)
            {
                matriz << "c";
                matriz << i;
                matriz << j;
                matriz << " ";
                matriz << rand() % 100 + 1;
                matriz << std::endl;
            }
        }
    }
    catch (std::exception &error)
    {
        std::cerr << error.what() << std::endl;
        exit(2);
    }
    matriz.close();
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        std::cerr << "erro na formatação dos parâmetros de entrada" << std::endl;
        exit(2);
    }

    try
    {
        formacaoDaMatriz(atoi(argv[1]), atoi(argv[2]), "arquivos/matrizOriginal1.txt");
        formacaoDaMatriz(atoi(argv[3]), atoi(argv[4]), "arquivos/matrizOriginal2.txt");
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        exit(2);
    }
}