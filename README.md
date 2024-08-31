# Apresentacao

Este repositorio eh uma refatoracao do zero, utilizando novas praticas de C++ adquiridas pela leitura do livro "C++ Software Design: Design Principles and Patterns for High-Quality Software" e "Modern C++ Programming Cookbook: Master Modern C++ with comprehensive solutions for C++23 and all previous standards", ambos excelentes livros.

Apos a leitura desses livros, surgiram novas ideais de implementacao, e um desafio proprio de refazer um trabalho ardiloso proposto por meus professores na faculdade

# Objetivos
 
manipular uma base real de dados

implementar 3 alg. de ordenacao, 3 way quicksort, heapsort, combsort e tabela hash com sondagem dupla 

implementar b tree e red black tree

implementar compressao de huffman

## INPUT

Arquivo de entrada pode ser encontrado no link:
https://www.kaggle.com/shivamb/35-million-tiktok-mobile-app-reviews

## BUILD 1

colocar o arquivo de entrada na pasta "src",usar a seguinte linha via terminal na pasta para compilar:

```
++ -O3 *.cpp -o main -g
```

e a seguinte linha para rodar:
```
./main <entrada do arquivo CSV> 
```
exemplo de linha para execução:
```
./main tiktok_reviews.csv
```
## BUILD ALTERNATIVA 2

PRE REQUISITOS:
> CMAKE

## PARA EXECUTAR

ABRA O TERMINAL NA PASTA SRC E EXECUTE:

```
cmake ../.
```
```
make && ./ED2021 <entrada do arquivo CSV> 
```


## Integrantes:

> Andressa Augusta Ferrugini de Oliveira - 201665251AC

> Arthur Monteiro Pereira - 201865552C

> Daniel Fagundes Portes Fernandes - 201965574C

> Guilherme Gonçalves de Souza Alves - 201665503B
