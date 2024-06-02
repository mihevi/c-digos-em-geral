#include <stdio.h>
#include <string.h>
#define TAM_MAX_PLYLST 200
#define TAM_NOME 50
#define TAM_LOGIN 15
#define TAM_SENHA 15
#define TAM_PLAYLIST 100
#define TAM_TITULO 50
#define TAM_MUSICAS 100
FILE *file;
FILE file = fopen("usuarios.txt", "a");
struct Musica {

int codigo; // autoincremento

char titulo[TAM_TITULO]; // título da música
char artista[TAM_NOME]; // nome do artista que canta esta música

};
struct Playlist {
int codigo; // autoincremento
int codUsuario; // o código do usuário que criou a playlist
char titulo[TAM_TITULO]; // título desta playlist
int qtdMusicas; // qtd atual de músicas incluídas nesta playlist
int musicas[TAM_MUSICAS]; // vetor contendo os códigos das músicas
};

struct Usuario {
int codigo; // autoincremento
char nome[TAM_NOME];
char login[TAM_LOGIN];
char senha[TAM_SENHA];
int qtdPlaylists; // quantid. de playlists criadas pelo usuário
struct Playlist playlists[TAM_PLAYLIST]; // todas playlists criadas
int qtdPlaylistsFav; // quantid. de playlists favoritadas pelo usuário
int playlistsFav[TAM_PLAYLIST]; // códigos das playlists favoritadas pelo usuário
};

void lerDadosUsuario(struct Usuario *usuario) {
    char novoLogin[TAM_LOGIN];
    int loginExistente = 0;
    
    do {
        printf("Digite o nome: ");
        fgets(usuario->nome, TAM_NOME, stdin);
        usuario->nome[strcspn(usuario->nome, "\n")] = '\0'; // Remover newline

        printf("Digite o login: ");
        fgets(novoLogin, TAM_LOGIN, stdin);
        novoLogin[strcspn(novoLogin, "\n")] = '\0'; // Remover newline

        printf("Digite a senha: ");
        fgets(usuario->senha, TAM_SENHA, stdin);
        usuario->senha[strcspn(usuario->senha, "\n")] = '\0'; // Remover newline

        FILE file = fopen("usuarios.dat", "rb");
            struct Usuario temp;
            while (fread(&temp, sizeof(struct Usuario), 1, file)) {
                if (strcmp(temp.login, novoLogin) == 0) {
                    loginExistente = 1;
                    printf("Este login já está em uso. Por favor, escolha outro.\n");
                    break;
                }
            }
            fclose(file);
    } while (loginExistente);

    strcpy(usuario->login, novoLogin);
}

int obterProximoCodigo(FILE *file) {
    int codigo = 0;
    struct Usuario usuario;
    while (fread(&usuario, sizeof(struct Usuario), 1, file)) {
        if (usuario.codigo > codigo) {
            codigo = usuario.codigo;
        }
    }

    return codigo + 1;
}

void escreverUsuarioNoArquivo(FILE *file, struct Usuario usuario) {
    fwrite(&usuario, sizeof(struct Usuario), 1, file);
}
int fazerLogin(const char *login, const char *senha) {
    FILE *file = fopen("usuarios.dat", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    struct Usuario usuario;
    while (fread(&usuario, sizeof(struct Usuario), 1, file)) {
        if (strcmp(usuario.login, login) == 0 && strcmp(usuario.senha, senha) == 0) {
            fclose(file);
            return 1; // Login bem-sucedido
        }
    }

    fclose(file);
    return 0; 
}
int main() {
    struct Usuario usuario;
    FILE *file;
    int escolha;
    printf("Escolha uma opção:\n1. Cadastrar\n2. Login\n");
    scanf("%d", &escolha);
    getchar(); // Consumir o newline deixado pelo scanf
    while((escolha) == 1){
        if (escolha == 1) {
            lerDadosUsuario(&usuario);

            file = fopen("usuarios.dat", "rb");
            if (file != NULL) {
                usuario.codigo = obterProximoCodigo(file);
                fclose(file);
            } else {
                usuario.codigo = 1; // Primeiro usuário
            }

            file = fopen("usuarios.dat", "ab");
            if (file == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }

            escreverUsuarioNoArquivo(file, usuario);
            fclose(file);
        }
        printf("Dados armazenados com sucesso em 'usuarios.dat'\n");
    }
        if (escolha == 2) {
            char login[TAM_LOGIN];
            char senha[TAM_SENHA];

            printf("Digite o login: ");
            fgets(login, TAM_LOGIN, stdin);
            login[strcspn(login, "\n")] = '\0'; // Remover newline

            printf("Digite a senha: ");
            fgets(senha, TAM_SENHA, stdin);
            senha[strcspn(senha, "\n")] = '\0'; // Remover newline

            if (fazerLogin(login, senha)) {
                printf("Login bem-sucedido!\n");
            } else {
                printf("Login ou senha incorretos!\n");
            }
        } else {
            printf("Opção inválida!\n");
        }

    return 0;
}