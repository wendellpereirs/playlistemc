#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da lista circular duplamente encadeada
typedef struct Node {
    char artista[100];
    char musica[100];
    struct Node *next;
    struct Node *prev;
} Node;

// Estrutura da lista circular duplamente encadeada
typedef struct {
    Node *head;
} CircularDoublyLinkedList;

// Funções para manipulação da lista
Node* createNode(char *artista, char *musica);
void adicionar(CircularDoublyLinkedList *list, char *artista, char *musica);
void exibir(CircularDoublyLinkedList *list);
void leiaArquivo(CircularDoublyLinkedList *list, const char *nomeArquivo);
void escrevaArquivo(CircularDoublyLinkedList *list, const char *nomeArquivo);
void vePlaylist(CircularDoublyLinkedList *list);
void inserirMusica(CircularDoublyLinkedList *list, const char *nomeArquivo);
void removerMusica(CircularDoublyLinkedList *list, const char *nomeArquivo);
void buscarMusica(CircularDoublyLinkedList *list);
Node* avancarMusica(Node *current);
Node* voltarMusica(Node *current);
void menu();

#endif // MAIN_H
