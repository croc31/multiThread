# multiThread
Trabalho da disciplina de Sistemas Operacionais para testar multithreading 
<p align="center">
  <img alt="GitHub top language" src="https://img.shields.io/github/languages/top/croc31/multiThread.svg?color=5863d2">

  <img alt="GitHub language count" src="https://img.shields.io/github/languages/count/croc31/multiThread.svg?color=5863d2">
  
  <a href="https://github.com/croc31/multiThread/commits/main">
    <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/croc31/multiThread?color=5863d2">
  </a>

  <img alt="GitHub" src="https://img.shields.io/github/license/croc31/multiThread?color=5863d2">
</p>

<p align="center">
  <a href="#sobre">Sobre</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#compilar">Compilar</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#matrizes">Como rodar?</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#licença-e-autor">Licença e Autor</a>
</p>

## Sobre 

## Compilar
Basta rodar o arquivo make
```bash
$ make
```
## Matrizes
 O algoritmo de matrizes cria duas matrizes, para utilizar basta executar o comando:
 ./matrizes <quantidade de linhas da matriz 1> <quantidade de colunas da matriz 1> <quantidade de linhas da matriz 2> <quantidade de colunas da matriz 2>
 
 Exemplo:
 ```bash
$ ./matrizes 200 100 300 100
```
 Esse comando cria uma matriz 200X100 e uma matriz 300X100
 
 OBS: Esses arquivos vão ser criados na pasta "arquivos", lembre de deixar uma pasta com esse nome no mesmo diretório que o programa
 
## Sequencial
 O algoritmo sequencial cria um arquivo com a multiplicação dde duas matrizes, para utilizar basta executar o comando:
 ./sequencial <matriz 1> <matriz 2>
 Exemplo:
 ```bash
$ ./sequencial teste1 teste2
```
Esse comando cria um arquivo chamado "sequencial" contendo a multiplicação das matrizes "teste1" e "teste2".

OBS: Esses arquivos vão ser criados na pasta "arquivos", lembre de deixar uma pasta com esse nome no mesmo diretório que o programa.

OBS2: O programa irá procurar os arquivos de entrada na pasta arquivos.

## Processos
 O algoritmo de processos cria um arquivo com a multiplicação de duas matrizes, para utilizar basta executar o comando:
 ./processos <matriz 1> <matriz 2>  <p>
 Exemplo:
 ```bash
$ ./processos teste1 teste2 2
```
Esse comando cria vários arquivos chamados "processoN" contendo parte da multiplicação das matrizes "teste1" e "teste2", a quantidade de arquivos criados é igual a quantidade de elementos da matriz final dividido por p.
  
OBS: Esses arquivos vão ser criados na pasta "arquivos", lembre de deixar uma pasta com esse nome no mesmo diretório que o programa.
  
OBS2: O programa irá procurar os arquivos de entrada na pasta arquivos.
  
## Thread
 O algoritmo de threads cria um arquivo com a multiplicação de duas matrizes, para utilizar basta executar o comando:
 ./thread <matriz 1> <matriz 2>  <p>
 Exemplo:
 ```bash
$ ./thread teste1 teste2 2
```
Esse comando cria vários arquivos chamados "threadN" contendo parte da multiplicação das matrizes "teste1" e "teste2", a quantidade de arquivos criados é igual a quantidade de elementos da matriz final dividido por p. /n

OBS: Esses arquivos vão ser criados na pasta "arquivos", lembre de deixar uma pasta com esse nome no mesmo diretório que o programa

OBS2: O programa irá procurar os arquivos de entrada na pasta arquivos
 
