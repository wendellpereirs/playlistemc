#include "main.h"

Node* createNode(char *artista, char *musica) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->artista, artista);
    strcpy(newNode->musica, musica);
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void adicionar(CircularDoublyLinkedList *list, char *artista, char *musica) {
    Node *newNode = createNode(artista, musica);
    if (!list->head) {
        list->head = newNode;
        list->head->next = list->head;
        list->head->prev = list->head;
    } else {
        Node *tail = list->head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = list->head;
        list->head->prev = newNode;
    }
}

void exibir(CircularDoublyLinkedList *list) {
    if (!list->head) {
        printf("Lista de reprodução está vazia.\n");
        return;
    }
    Node *current = list->head;
    do {
        printf("%s - %s\n", current->artista, current->musica);
        current = current->next;
    } while (current != list->head);
}

void leiaArquivo(CircularDoublyLinkedList *list, const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *artista = strtok(line, ";");
        char *musica = strtok(NULL, "\n");
        if (artista && musica) {
            adicionar(list, artista, musica);
        }
    }
    fclose(file);
}

void escrevaArquivo(CircularDoublyLinkedList *list, const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "w");
    if (!file) {
        perror("Não foi possível abrir o arquivo");
        return;
    }
    Node *current = list->head;
    if (current) {
        do {
            fprintf(file, "%s;%s\n", current->artista, current->musica);
            current = current->next;
        } while (current != list->head);
    }
    fclose(file);
}

void verPlaylist(CircularDoublyLinkedList *list) {
    if (!list->head) {
        printf("Lista de reprodução está vazia.\n");
        return;
    }
    int count = 0;
    Node *current = list->head;
    do {
        count++;
        current = current->next;
    } while (current != list->head);

    Node *array[count];
    current = list->head;
    for (int i = 0; i < count; i++) {
        array[i] = current;
        current = current->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(array[j]->musica, array[j + 1]->musica) > 0) {
                Node *temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%s - %s\n", array[i]->artista, array[i]->musica);
    }
}

void inserirMusica(CircularDoublyLinkedList *list, const char *nomeArquivo) {
    char artista[100];
    char musica[100];
    printf("Digite o nome do(a) artista/banda: ");
    scanf(" %[^\n]s", artista);
    printf("Digite o nome da música: ");
    scanf(" %[^\n]s", musica);
    adicionar(list, artista, musica);
    escrevaArquivo(list, nomeArquivo);
    printf("Musica adicionada com sucesso.\n");
}

void removerMusica(CircularDoublyLinkedList *list, const char *nomeArquivo) {
    char nomeMusica[100];
    printf("Digite o nome da música para remover: ");
    scanf(" %[^\n]s", nomeMusica);

    if (!list->head) {
        printf("Lista de reprodução está vazia.\n");
        return;
    }

    Node *current = list->head;
    int found = 0;
    do {
        if (strcmp(current->musica, nomeMusica) == 0) {
            found = 1;
            if (current == list->head) {
                if (current->next == list->head) {
                    list->head = NULL;
                } else {
                    Node *tail = list->head->prev;
                    list->head = current->next;
                    tail->next = list->head;
                    list->head->prev = tail;
                }
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            break;
        }
        current = current->next;
    } while (current != list->head);

    if (found) {
        escrevaArquivo(list, nomeArquivo);
        printf("Música removida com sucesso.\n");
    } else {
        printf("Música não encontrada.\n");
    }
}

void buscarMusica(CircularDoublyLinkedList *list) {
    char nomeMusica[100];
    printf("Digite o nome da música para pesquisar: ");
    scanf(" %[^\n]s", nomeMusica);

    if (!list->head) {
        printf("Lista de reprodução está vazia.\n");
        return;
    }

    Node *current = list->head;
    int found = 0;
    do {
        if (strcmp(current->musica, nomeMusica) == 0) {
            printf("Música encontrada: %s - %s\n", current->artista, current->musica);
            found = 1;
            break;
        }
        current = current->next;
    } while (current != list->head);

    if (!found) {
        printf("Música não encontrada.\n");
    }
}

Node* avancarMusica(Node *current) {
    if (current && current->next) {
        current = current->next;
    }
    return current;
}

Node* voltarMusica(Node *current) {
    if (current && current->prev) {
        current = current->prev;
    }
    return current;
}

void menu() {
    printf("\n==============================\n");
    printf("          Menu de Opções      \n");
    printf("==============================\n");
    printf("1. Exibir playlist (ordem de cadastro)\n");
    printf("2. Exibir playlist (ordenada por nome da música)\n");
    printf("3. Inserir nova música\n");
    printf("4. Remover música\n");
    printf("5. Buscar música\n");
    printf("6. Avançar para a próxima música\n");
    printf("7. Retornar à música anterior\n");
    printf("8. Sair\n");
    printf("==============================\n");
}

int main() {
    CircularDoublyLinkedList playlist = {NULL};
    Node *currentmusica = NULL;
    const char *nomeArquivo = "musicas.txt";
    leiaArquivo(&playlist, nomeArquivo);
    currentmusica = playlist.head;

    while (1) {
        menu();
        int choice;
        printf("Digite uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                exibir(&playlist);
                break;
            case 2:
                verPlaylist(&playlist);
                break;
            case 3:
                inserirMusica(&playlist, nomeArquivo);
                break;
            case 4:
                removerMusica(&playlist, nomeArquivo);
                break;
            case 5:
                buscarMusica(&playlist);
                break;
            case 6:
                currentmusica = avancarMusica(currentmusica);
                if (currentmusica) {
                    printf("Está tocando: %s - %s\n", currentmusica->artista, currentmusica->musica);
                }
                break;
            case 7:
                currentmusica = voltarMusica(currentmusica);
                if (currentmusica) {
                    printf("Está tocando: %s - %s\n", currentmusica->artista, currentmusica->musica);
                }
                break;
            case 8:
                exit(0);
            default:
                printf("Escolha inválida, tente novamente.\n");
        }
    }

    return 0;
}
