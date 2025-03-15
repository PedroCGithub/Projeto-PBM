#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lerArquivo(const char *nomeArquivo, int *altura, int *largura, int ***imagem) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    char linha[256];
    // Ler o magic number (P1)
    fgets(linha, sizeof(linha), arquivo);

    // Ignorar comentários
    do {
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            printf("Erro ao ler o arquivo.\n");
            fclose(arquivo);
            exit(EXIT_FAILURE);
        }
    } while (linha[0] == '#');

    // Lê as dimensões da imagem
    if (sscanf(linha, "%d %d", largura, altura) != 2) {
        printf("Erro ao ler dimensões da imagem.\n");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    // Verifica se as dimensões são válidas
    if (*altura <= 0 || *largura <= 0) {
        printf("Dimensões inválidas: %dx%d\n", *largura, *altura);
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    // Aloca a matriz da imagem
    *imagem = (int **)malloc(*altura * sizeof(int *));
    if (*imagem == NULL) {
        printf("Erro na alocação de memória.\n");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *altura; i++) {
        (*imagem)[i] = (int *)malloc(*largura * sizeof(int));
        if ((*imagem)[i] == NULL) {
            // Libera memória já alocada
            for (int j = 0; j < i; j++) {
                free((*imagem)[j]);
            }
            free(*imagem);
            printf("Erro na alocação de memória.\n");
            fclose(arquivo);
            exit(EXIT_FAILURE);
        }
    }

    // Lê os pixels
    for (int i = 0; i < *altura; i++) {
        for (int j = 0; j < *largura; j++) {
            int valor;
            if (fscanf(arquivo, "%d", &valor) != 1) {
                printf("Erro ao ler pixel na posição [%d][%d]\n", i, j);
                // Libera memória alocada
                for (int k = 0; k < *altura; k++) {
                    free((*imagem)[k]);
                }
                free(*imagem);
                fclose(arquivo);
                exit(EXIT_FAILURE);
            }
            (*imagem)[i][j] = valor;
            printf("%d ", valor);
        }
        printf("\n");
    }

    fclose(arquivo);
}

char verificarSeHomogenio(int **imagem, int x, int y, int largura, int altura) {
    if (imagem == NULL || largura <= 0 || altura <= 0) {
        return 'B';  // Retorno padrão caso a imagem seja invalida
    }

    int cor = imagem[y][x];
    for (int i = y; i < y + altura; i++) {
        for (int j = x; j < x + largura; j++) {
            if (imagem[i][j] != cor) {
                return 'X';
            }
        }
    }
    return cor == 0 ? 'B' : 'P';
}
// Função recursiva para codificar a imagem
void criarCodigoDaImagem(int **imagem, int x, int y, int largura, int altura, char *codigo) {
    // Checagem de segurança
    if (largura <= 0 || altura <= 0 || imagem == NULL || codigo == NULL) {
        return;
    }

    char resultado = verificarSeHomogenio(imagem, x, y, largura, altura);
    if (resultado != 'X') {
        strncat(codigo, &resultado, 1);
    } else {
        strcat(codigo, "X");

        // Calcula o tamanho dos quadrantes
        int largura1 = (largura + 1) / 2;  // A metade superior recebe a coluna extra se for ímpar
        
        int altura1 = (altura + 1) / 2;    //A metade esquerda recebe a linha extra se for ímpar

        // Processa quadrantes na ordem correta com verificação de limites
        if (largura1 > 0 && altura1 > 0) {
            criarCodigoDaImagem(imagem, x, y, largura1, altura1, codigo);
        }

        if ((largura - largura1) > 0 && altura1 > 0) {
            criarCodigoDaImagem(imagem, x + largura1, y, largura - largura1, altura1, codigo);
        }

        if (largura1 > 0 && (altura - altura1) > 0) {
            criarCodigoDaImagem(imagem, x, y + altura1, largura1, altura - altura1, codigo);
        }

        if ((largura - largura1) > 0 && (altura - altura1) > 0) {
            criarCodigoDaImagem(imagem, x + largura1, y + altura1, largura - largura1, altura - altura1, codigo);
        }
    }
}

int main(int argc, char *argv[]) {
    // Caminho do arquivo PBM
    const char *caminho_arquivo = "./imagem.pbm";

    //Checa se Tem algum argumento alem do nome do arquivo, senão tiver printa a mensagem que diz os comandos
    if (argc < 2) {
        printf("Uso: %s [-? | -m | -f ARQUIVO]\n", argv[0]);
        printf("-?, --ajuda  : exibe esta ajuda.\n");
        printf("-m, --manual : entrada manual dos dados da imagem.\n");
        printf("-f, --arquivo: lê a imagem do arquivo PBM.\n");
        return 0;
    }

    //se tiver algum comandos dados retorna a resposta corespondente
    //se o comando usado for -? ou --ajuda
    if (strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "--ajuda") == 0) {
        printf("Uso: %s [-? | -m | -f ARQUIVO]\n", argv[0]);
        printf("-?, --ajuda  : exibe esta ajuda.\n");
        printf("-m, --manual : entrada manual dos dados da imagem.\n");
        printf("-f, --arquivo: lê a imagem do arquivo PBM.\n");
    
        //se o comando usado for -m ou --manual
    } else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "--manual") == 0) {
        printf("-m, --manual : entrada manual dos dados da imagem.\n");
         int largura, altura;
         printf("Informe a largura e altura da imagem: ");
         scanf("%d %d", &largura, &altura);

         int **imagem = (int **)malloc(altura * sizeof(int *));
         for (int i = 0; i < altura; i++) {
             imagem[i] = (int *)malloc(largura * sizeof(int));
         }

         printf("Informe os pixels (0 para branco, 1 para preto):\n");
         for (int i = 0; i < altura; i++) {
             for (int j = 0; j < largura; j++) {
                 scanf("%d", &imagem[i][j]);
             }
         }

         char codigo[1024] = "";
         criarCodigoDaImagem(imagem, 0, 0, largura, altura, codigo);
         printf("Código gerado: %s\n", codigo);


    //se o comando usado for -f ou --arquivo
} else if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--arquivo") == 0) {
    if (argc < 3) {
        printf("Erro: arquivo não especificado.\n");
        return EXIT_FAILURE;
    }

    int largura, altura;
    int **imagem;
    lerArquivo(argv[2], &altura, &largura, &imagem);

    // Aloca espaço para a string de código
    // Grande o suficiente para lidar com o pior caso
    char *codigo = (char *)malloc(largura * altura * 4 + 1); 
    if (codigo == NULL) {
        printf("Erro na alocação de memória para o código.\n");
        // Limpa a memória da imagem
        for (int i = 0; i < altura; i++) {
            free(imagem[i]);
        }
        free(imagem);
        return EXIT_FAILURE;
    }
    codigo[0] = '\0'; // Inicializa uma string vazia

    // Gerar o código
    criarCodigoDaImagem(imagem, 0, 0, largura, altura, codigo);

    printf("\nCodigo gerado: %s\n", codigo);

    // Limpa da memória
    free(codigo);
    for (int i = 0; i < altura; i++) {
        free(imagem[i]);
    }
    free(imagem);
}
}