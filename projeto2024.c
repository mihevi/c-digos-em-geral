#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_PLYLST 200
#define TAM_NOME 50
#define TAM_LOGIN 15
#define TAM_SENHA 15
#define TAM_PLAYLIST 100
#define TAM_TITULO 50
#define TAM_MUSICAS 100
#define MAX_USUARIOS 100
#define MAX_MUSICAS 100

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

struct Usuario usuarios[MAX_USUARIOS];
struct Musica musicas[MAX_MUSICAS];

int qtdUsuarios = 0;
int qtdMusicas = 0;

void salvarUsuarios();
void administradorMenu();
void usuarioMenu();
void cadastrarPlaylist();
void inserirMusicaNaPlaylist();
void favoritarPlaylist();
void excluirPlaylist();
void salvarMusicas();
int gerarCodigoUnicoParaPlaylist();
void excluirMusicaDaPlaylist();
void consultarPorCodigo();
void consultarPorTitulo();
void consultarPorArtista();
int IndiceAtual();
void MenuDoUsuario();
void listarUsuarios();
void consultarUsuario();
void alterarSenhaUsuario();
void cadastrarMusica();
void listarMusicas();
void consultarMusicas();
void alterarMusica();
void excluirMusica();
void listarPlaylists();
void consultarPlaylist();
int buscarUsuarioPorCodigo(int codigo);
int buscarMusicaPorCodigo(int codigo);

int main() {
    int escolha;
    char senhaAdmin[TAM_SENHA];

    while (1) {
        printf("Escolha uma opção:\n");
        printf("1. Administrador\n");
        printf("2. Usuário\n");
        printf("3. Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite a senha do administrador: ");
                scanf("%s", senhaAdmin);
                if (strcmp(senhaAdmin, "m@st3r2024") == 0) {
                    administradorMenu();
                } else {
                    printf("Senha incorreta!\n");
                }
                break;
            case 2:
                usuarioMenu();
                break;
            case 3:
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}

void administradorMenu() {
    int escolha;

    while (1) {
        printf("Menu do Administrador:\n");
        printf("1. Listar usuários\n");
        printf("2. Consultar usuário\n");
        printf("3. Alterar senha de um usuário\n");
        printf("4. Cadastrar novas músicas\n");
        printf("5. Listar todas as músicas\n");
        printf("6. Consultar músicas\n");
        printf("7. Alterar dados de músicas\n");
        printf("8. Excluir músicas\n");
        printf("9. Listar todas as playlists\n");
        printf("10. Consultar playlists\n");
        printf("11. Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                listarUsuarios();
                break;
            case 2:
                consultarUsuario();
                break;
            case 3:
                alterarSenhaUsuario();
                break;
            case 4:
                cadastrarMusica();
                break;
            case 5:
                listarMusicas();
                break;
            case 6:
                consultarMusicas();
                break;
            case 7:
                alterarMusica();
                break;
            case 8:
                excluirMusica();
                break;
            case 9:
                listarPlaylists();
                break;
            case 10:
                consultarPlaylist();
                break;
            case 11:
                return;
            default:
                printf("Opção inválida!\n");
        }
    }
}

void usuarioMenu() {
    int escolha;
    int logado = 0; // variável para controlar o estado de login do usuário
    int usuarioAtualIndice; // índice do usuário atual logado

    while (1) {
        if (!logado) {
            printf("Tela de Login:\n");
            printf("1. Login\n");
            printf("2. Cadastrar novo usuário\n");
            printf("3. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &escolha);

            switch (escolha) {
                case 1:
                    int usuarioAtualIndice = IndiceAtual();
                    if (usuarioAtualIndice != -1) {
                        logado = 1;
                    }
                    break;
                case 2: {
                    if (qtdUsuarios >= MAX_USUARIOS) {
                        printf("Número máximo de usuários atingido.\n");
                        break;
                    }
                    struct Usuario novoUsuario;
                    novoUsuario.codigo = qtdUsuarios + 1; // Atribui um código único
                    novoUsuario.qtdPlaylists = 0;
                    novoUsuario.qtdPlaylistsFav = 0;

                    printf("Digite seu nome: ");
                    scanf(" %[^\n]s", novoUsuario.nome);
                    printf("Digite seu login: ");
                    scanf("%s", novoUsuario.login);

                    char senha[50];
                    char confirmacaoSenha[50];
                    do {
                        printf("Digite sua senha: ");
                        scanf("%s", senha);
                        printf("Confirme sua senha: ");
                        scanf("%s", confirmacaoSenha);

                        if (strcmp(senha, confirmacaoSenha) != 0) {
                            printf("As senhas não conferem. Tente novamente.\n");
                        }
                    } while (strcmp(senha, confirmacaoSenha) != 0);

                    strcpy(novoUsuario.senha, senha);

                    usuarios[qtdUsuarios] = novoUsuario;
                    qtdUsuarios++;
                    salvarUsuarios(); // Salva o novo usuário no arquivo

                    printf("Usuário cadastrado com sucesso!\n");
                    break;
                }
                case 3:
                    return; // Sai do programa
                default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
            }
        } else {
            printf("Menu do Usuário:\n");
            printf("1. Listar seus dados\n");
            printf("2. Alterar nome\n");
            printf("3. Alterar login\n");
            printf("4. Alterar senha\n");
            printf("5. Listar usuários\n");
            printf("6. Consultar usuários por parte do nome\n");
            printf("7. Listar todas as músicas\n");
            printf("8. Consultar músicas\n");
            printf("9. Listar todas as suas playlists\n");
            printf("10. Listar todas as playlists (exceto suas)\n");
            printf("11. Consultar playlist\n");
            printf("12. Cadastrar uma playlist\n");
            printf("13. Inserir música na sua playlist\n");
            printf("14. Excluir música de uma playlist sua\n");
            printf("15. Excluir uma playlist\n");
            printf("16. Favoritar uma playlist\n");
            printf("17. Deslogar\n");
            scanf("%d", &escolha);

            switch (escolha) {
                case 1:
                    printf("Seus dados:\n");
                    printf("Código: %d, Nome: %s, Login: %s, Qtd Playlists: %d, Qtd Playlists Fav: %d\n",
                           usuarios[usuarioAtualIndice].codigo, usuarios[usuarioAtualIndice].nome, usuarios[usuarioAtualIndice].login,
                           usuarios[usuarioAtualIndice].qtdPlaylists, usuarios[usuarioAtualIndice].qtdPlaylistsFav);
                    break;
                case 2:
                    printf("Digite a senha atual: ");
                    char senha[50];
                    scanf("%s", senha);
                    if (strcmp(usuarios[usuarioAtualIndice].senha, senha) == 0) {
                        printf("Digite o novo nome: ");
                        char nome[100];
                        scanf(" %[^\n]s", nome);
                        strcpy(usuarios[usuarioAtualIndice].nome, nome);
                        salvarUsuarios(); // Salva a alteração no arquivo
                        printf("Nome alterado com sucesso!\n");
                    } else {
                        printf("Senha incorreta!\n");
                    }
                    break;
                case 3:
                    printf("Digite a senha atual: ");
                    scanf("%s", senha);
                    if (strcmp(usuarios[usuarioAtualIndice].senha, senha) == 0) {
                        printf("Digite o novo login: ");
                        char login[50];
                        scanf("%s", login);
                        strcpy(usuarios[usuarioAtualIndice].login, login);
                        salvarUsuarios(); // Salva a alteração no arquivo
                        printf("Login alterado com sucesso!\n");
                    } else {
                        printf("Senha incorreta!\n");
                    }
                    break;
                case 4:
                    printf("Digite a senha atual: ");
                    scanf("%s", senha);
                    if (strcmp(usuarios[usuarioAtualIndice].senha, senha) == 0) {
                        printf("Digite a nova senha: ");
                        char novaSenha[50];
                        scanf("%s", novaSenha);
                        printf("Confirme a nova senha: ");
                        char confirmacaoSenha[50];
                        scanf("%s", confirmacaoSenha);
                        if (strcmp(novaSenha, confirmacaoSenha) == 0) {
                            strcpy(usuarios[usuarioAtualIndice].senha, novaSenha);
                            salvarUsuarios(); // Salva a alteração no arquivo
                            printf("Senha alterada com sucesso!\n");
                        } else {
                            printf("As senhas não conferem!\n");
                        }
                    } else {
                        printf("Senha incorreta!\n");
                    }
                    break;
                case 5:
                    printf("Lista de Usuários:\n");
                    for (int i = 0; i < qtdUsuarios; i++) {
                        printf("Nome: %s\n", usuarios[i].nome);
                    }
                    break;
                case 6:
                    printf("Digite parte do nome do usuário: ");
                    char nome[100];
                    scanf(" %[^\n]s", nome);
                    printf("Usuários encontrados:\n");
                    for (int i = 0; i < qtdUsuarios; i++) {
                        if (strstr(usuarios[i].nome, nome) != NULL) {
                            printf("Nome: %s\n", usuarios[i].nome);
                        }
                    }
                    break;
                case 7:
                    listarMusicas();
                    break;
                case 8:
                    consultarMusicas();
                    break;
                case 9:
                    printf("Suas playlists:\n");
                    for (int i = 0; i < usuarios[usuarioAtualIndice].qtdPlaylists; i++) {
                        struct Playlist *playlist = &usuarios[usuarioAtualIndice].playlists[i];
                        printf("Código: %d, Título: %s\n", playlist->codigo, playlist->titulo);
                        for (int j = 0; j < playlist->qtdMusicas; j++) {
                            int codigoMusica = playlist->musicas[j];
                            int indexMusica = buscarMusicaPorCodigo(codigoMusica);
                            if (indexMusica != -1) {
                                printf("  Música: %s - %s\n", musicas[indexMusica].titulo, musicas[indexMusica].artista);
                            }
                        }
                    }
                    printf("Playlists favoritadas:\n");
                    for (int i = 0; i < usuarios[usuarioAtualIndice].qtdPlaylistsFav; i++) {
                        int codigo = usuarios[usuarioAtualIndice].playlistsFav[i];
                        for (int j = 0; j < qtdUsuarios; j++) {
                            for (int k = 0; k < usuarios[j].qtdPlaylists; k++) {
                                if (usuarios[j].playlists[k].codigo == codigo) {
                                    struct Playlist *playlist = &usuarios[j].playlists[k];
                                    printf("Código: %d, Título: %s, Criador: %s\n", playlist->codigo, playlist->titulo, usuarios[j].nome);
                                    for (int l = 0; l < playlist->qtdMusicas; l++) {
                                        int codigoMusica = playlist->musicas[l];
                                        int indexMusica = buscarMusicaPorCodigo(codigoMusica);
                                        if (indexMusica != -1) {
                                            printf("  Música: %s - %s\n", musicas[indexMusica].titulo, musicas[indexMusica].artista);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 10:
                    printf("Playlists de outros usuários:\n");
                    for (int i = 0; i < qtdUsuarios; i++) {
                        if (i != usuarioAtualIndice) {
                            for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
                                struct Playlist *playlist = &usuarios[i].playlists[j];
                                printf("Código: %d, Título: %s, Criador: %s\n", playlist->codigo, playlist->titulo, usuarios[i].nome);
                                for (int k = 0; k < playlist->qtdMusicas; k++) {
                                    int codigoMusica = playlist->musicas[k];
                                    int indexMusica = buscarMusicaPorCodigo(codigoMusica);
                                    if (indexMusica != -1) {
                                        printf("  Música: %s - %s\n", musicas[indexMusica].titulo, musicas[indexMusica].artista);
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 11:
                    consultarPlaylist(usuarioAtualIndice);
                    break;
                case 12:
                    cadastrarPlaylist(usuarioAtualIndice);
                    break;
                case 13:
                    inserirMusicaNaPlaylist(usuarioAtualIndice);
                    break;
                case 14:
                    excluirMusicaDaPlaylist(usuarioAtualIndice);
                    break;
                case 15:
                    excluirPlaylist(usuarioAtualIndice);
                    break;
                case 16:
                    favoritarPlaylist(usuarioAtualIndice);
                    break;
                case 17:
                    logado = 0; // Desloga o usuário
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
            }
        }
    }
}

void listarUsuarios() {
    printf("Lista de Usuários:\n");
    for (int i = 0; i < qtdUsuarios; i++) {
        printf("Código: %d, Nome: %s, Login: %s, Qtd Playlists: %d, Qtd Playlists Fav: %d\n",
               usuarios[i].codigo, usuarios[i].nome, usuarios[i].login, usuarios[i].qtdPlaylists, usuarios[i].qtdPlaylistsFav);
    }
}

void consultarUsuario() {
    char nome[100];
    printf("Digite o nome do usuário que deseja consultar: ");
    scanf(" %[^\n]s", nome);

    int encontrado = 0;
    for (int i = 0; i < qtdUsuarios; i++) {
        if (strstr(usuarios[i].nome, nome) != NULL) {
            printf("Usuário encontrado:\n");
            printf("Código: %d\n", usuarios[i].codigo);
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Login: %s\n", usuarios[i].login);
            printf("Quantidade de playlists: %d\n", usuarios[i].qtdPlaylists);
            printf("Quantidade de playlists favoritadas: %d\n", usuarios[i].qtdPlaylistsFav);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Usuário não encontrado.\n");
    }
}

void alterarSenhaUsuario() {
    int codigoUsuario;
    printf("Digite o código do usuário para o qual deseja alterar a senha: ");
    scanf("%d", &codigoUsuario);

    int indiceUsuario = -1;
    for (int i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].codigo == codigoUsuario) {
            indiceUsuario = i;
            break;
        }
    }

    if (indiceUsuario == -1) {
        printf("Usuário não encontrado.\n");
        return;
    }

    char senhaAtual[TAM_SENHA];
    printf("Digite a senha atual: ");
    scanf("%s", senhaAtual);

    if (strcmp(usuarios[indiceUsuario].senha, senhaAtual) != 0) {
        printf("Senha atual incorreta.\n");
        return;
    }

    char novaSenha[TAM_SENHA];
    char confirmacaoSenha[TAM_SENHA];
    printf("Digite a nova senha: ");
    scanf("%s", novaSenha);
    printf("Confirme a nova senha: ");
    scanf("%s", confirmacaoSenha);

    if (strcmp(novaSenha, confirmacaoSenha) != 0) {
        printf("As senhas não conferem.\n");
        return;
    }

    strcpy(usuarios[indiceUsuario].senha, novaSenha);
    salvarUsuarios(); // Salva a alteração no arquivo
    printf("Senha alterada com sucesso.\n");
}

void cadastrarMusica() {
    if (qtdMusicas < MAX_MUSICAS) {
        struct Musica novaMusica;
        novaMusica.codigo = qtdMusicas + 1; // autoincremento
        printf("Digite o título da música: ");
        scanf(" %[^\n]s", novaMusica.titulo);
        printf("Digite o nome do artista: ");
        scanf(" %[^\n]s", novaMusica.artista);

        musicas[qtdMusicas] = novaMusica;
        qtdMusicas++;
    } else {
        printf("Capacidade máxima de músicas atingida!\n");
    }
}

void listarMusicas() {
    printf("Lista de Músicas:\n");
    for (int i = 0; i < qtdMusicas; i++) {
        printf("Código: %d, Título: %s, Artista: %s\n",
               musicas[i].codigo, musicas[i].titulo, musicas[i].artista);
    }
}

void consultarMusicas() {
    int escolha;
    printf("Selecione o critério de consulta:\n");
    printf("1. Por código\n");
    printf("2. Por título da música\n");
    printf("3. Por nome do artista\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            consultarPorCodigo();
            break;
        case 2:
            consultarPorTitulo();
            break;
        case 3:
            consultarPorArtista();
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}

void consultarPorCodigo() {
    int codigoMusica;
    printf("Digite o código da música que deseja consultar: ");
    scanf("%d", &codigoMusica);

    int indiceMusica = buscarMusicaPorCodigo(codigoMusica);
    if (indiceMusica != -1) {
        printf("Música encontrada:\n");
        printf("Título: %s\n", musicas[indiceMusica].titulo);
        printf("Artista: %s\n", musicas[indiceMusica].artista);
        // Adicione outros campos, se necessário
    } else {
        printf("Música não encontrada.\n");
    }
}

void consultarPorTitulo() {
    char titulo[100];
    printf("Digite parte ou o título completo da música que deseja consultar: ");
    scanf(" %[^\n]s", titulo);

    int encontradas = 0;
    for (int i = 0; i < qtdMusicas; i++) {
        if (strstr(musicas[i].titulo, titulo) != NULL) {
            printf("Música encontrada:\n");
            printf("Título: %s\n", musicas[i].titulo);
            printf("Artista: %s\n", musicas[i].artista);
            // Adicione outros campos, se necessário
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma música encontrada com o título fornecido.\n");
    }
}

void consultarPorArtista() {
    char artista[100];
    printf("Digite parte ou o nome completo do artista que deseja consultar: ");
    scanf(" %[^\n]s", artista);

    int encontradas = 0;
    for (int i = 0; i < qtdMusicas; i++) {
        if (strstr(musicas[i].artista, artista) != NULL) {
            printf("Música encontrada:\n");
            printf("Título: %s\n", musicas[i].titulo);
            printf("Artista: %s\n", musicas[i].artista);
            // Adicione outros campos, se necessário
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma música encontrada com o artista fornecido.\n");
    }
}


void alterarMusica() {
    int codigoMusica;
    printf("Digite o código da música que deseja alterar: ");
    scanf("%d", &codigoMusica);

    int indiceMusica = buscarMusicaPorCodigo(codigoMusica);
    if (indiceMusica == -1) {
        printf("Música não encontrada.\n");
        return;
    }

    printf("Digite o novo título da música: ");
    scanf(" %[^\n]s", musicas[indiceMusica].titulo);
    printf("Digite o novo nome do artista: ");
    scanf(" %[^\n]s", musicas[indiceMusica].artista);

    // Adicione outras informações a serem alteradas, se necessário

    salvarMusicas(); // Salva as alterações no arquivo
    printf("Música alterada com sucesso.\n");
}


void excluirMusica() {
    int codigoMusica;
    printf("Digite o código da música que deseja excluir: ");
    scanf("%d", &codigoMusica);

    int indiceMusica = buscarMusicaPorCodigo(codigoMusica);
    if (indiceMusica == -1) {
        printf("Música não encontrada.\n");
        return;
    }

    // Remover a música da lista de músicas
    for (int i = indiceMusica; i < qtdMusicas - 1; i++) {
        musicas[i] = musicas[i + 1];
    }
    qtdMusicas--;

    // Atualizar as playlists removendo a música
    for (int i = 0; i < qtdUsuarios; i++) {
        for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
            struct Playlist *playlist = &usuarios[i].playlists[j];
            for (int k = 0; k < playlist->qtdMusicas; k++) {
                if (playlist->musicas[k] == codigoMusica) {
                    for (int l = k; l < playlist->qtdMusicas - 1; l++) {
                        playlist->musicas[l] = playlist->musicas[l + 1];
                    }
                    playlist->qtdMusicas--;
                }
            }
        }
    }

    salvarMusicas(); // Salva as alterações no arquivo
    printf("Música excluída com sucesso.\n");
}


void listarPlaylists() {
    int usuarioAtualIndice = IndiceAtual(); // Obtém o índice do usuário atual
    printf("Suas playlists:\n");
    for (int i = 0; i < usuarios[usuarioAtualIndice].qtdPlaylists; i++) {
        struct Playlist *playlist = &usuarios[usuarioAtualIndice].playlists[i];
        printf("Código: %d, Título: %s\n", playlist->codigo, playlist->titulo);
        for (int j = 0; j < playlist->qtdMusicas; j++) {
            int codigoMusica = playlist->musicas[j];
            int indexMusica = buscarMusicaPorCodigo(codigoMusica);
            if (indexMusica != -1) {
                printf("  Música: %s - %s\n", musicas[indexMusica].titulo, musicas[indexMusica].artista);
            }
        }
    }
}


void consultarPlaylist() {
    int escolha;
    printf("Selecione o critério de consulta:\n");
    printf("1. Por código da playlist\n");
    printf("2. Por título da playlist\n");
    printf("3. Por código de música\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            consultarPorCodigoPlaylist();
            break;
        case 2:
            consultarPorTituloPlaylist();
            break;
        case 3:
            consultarPorCodigoMusica();
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}

void consultarPorCodigoPlaylist() {
    int codigoPlaylist;
    printf("Digite o código da playlist que deseja consultar: ");
    scanf("%d", &codigoPlaylist);

    int usuarioAtualIndice = IndiceAtual(); // Obtém o índice do usuário atual
    int encontradas = 0;
    for (int i = 0; i < usuarios[usuarioAtualIndice].qtdPlaylists; i++) {
        if (usuarios[usuarioAtualIndice].playlists[i].codigo == codigoPlaylist) {
            exibirPlaylist(&usuarios[usuarioAtualIndice].playlists[i]);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("Playlist não encontrada.\n");
    }
}

void consultarPorTituloPlaylist() {
    char titulo[100];
    printf("Digite parte ou o título completo da playlist que deseja consultar: ");
    scanf(" %[^\n]s", titulo);

    int usuarioAtualIndice = IndiceAtual(); // Obtém o índice do usuário atual
    int encontradas = 0;
    for (int i = 0; i < usuarios[usuarioAtualIndice].qtdPlaylists; i++) {
        if (strstr(usuarios[usuarioAtualIndice].playlists[i].titulo, titulo) != NULL) {
            exibirPlaylist(&usuarios[usuarioAtualIndice].playlists[i]);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma playlist encontrada com o título fornecido.\n");
    }
}

void consultarPorCodigoMusica() {
    int codigoMusica;
    printf("Digite o código da música que deseja buscar: ");
    scanf("%d", &codigoMusica);

    int encontradas = 0;
    for (int i = 0; i < qtdUsuarios; i++) {
        for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
            struct Playlist *playlist = &usuarios[i].playlists[j];
            for (int k = 0; k < playlist->qtdMusicas; k++) {
                if (playlist->musicas[k] == codigoMusica) {
                    exibirPlaylist(playlist);
                    encontradas++;
                    break;
                }
            }
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma playlist encontrada com a música fornecida.\n");
    }
}

void exibirPlaylist(struct Playlist *playlist) {
    printf("Código: %d, Título: %s\n", playlist->codigo, playlist->titulo);
    for (int i = 0; i < playlist->qtdMusicas; i++) {
        int codigoMusica = playlist->musicas[i];
        int indexMusica = buscarMusicaPorCodigo(codigoMusica);
        if (indexMusica != -1) {
            printf("  Música: %s - %s\n", musicas[indexMusica].titulo, musicas[indexMusica].artista);
        }
    }
    printf("\n");
}

int buscarUsuarioPorCodigo(int codigo) {
    for (int i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarMusicaPorCodigo(int codigo) {
    for (int i = 0; i < qtdMusicas; i++) {
        if (musicas[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int  IndiceAtual(){
    char nome[TAM_NOME];
    char senha[TAM_SENHA];
    printf("Digite seu nome: ");
    scanf("%s", nome);
    printf("Digite sua senha: ");
    scanf("%s", senha);
        for (int i = 0; i < qtdUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            return i; // Retorna o índice do usuário encontrado
        }
    }

    return -1; // Retorna -1 se o usuário não for encontrado
}

void MenuDoUsuario() {

    int escolha;
    int logado = 1;
    int usuarioAtual = IndiceAtual();
    char confirmacaoSenha[TAM_SENHA];
    char senha[TAM_SENHA];
    char nome[TAM_NOME];
    while (logado == 1)
    {
        printf("1. Listar seus dados\n");
        printf("2. Alterar nome\n");
        printf("3. Alterar login\n");
        printf("4. Alterar senha\n");
        printf("5. Listar usuários\n");
        printf("6. Consultar usuários por parte do nome\n");
        printf("7. Listar todas as músicas\n");
        printf("8. Consultar músicas\n");
        printf("9. Listar todas as suas playlists\n");
        printf("10. Listar todas as playlists (exceto suas)\n");
        printf("11. Consultar playlist\n");
        printf("12. Cadastrar uma playlist\n");
        printf("13. Inserir música na sua playlist\n");
        printf("14. Excluir música de uma playlist sua\n");
        printf("15. Excluir uma playlist\n");
        printf("16. Favoritar uma playlist\n");
        printf("17. Deslogar\n");

        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Seus dados:\n");
                printf("Código: %d, Nome: %s, Login: %s, Qtd Playlists: %d, Qtd Playlists Fav: %d\n",
                    usuarios[usuarioAtual].codigo, usuarios[usuarioAtual].nome, usuarios[usuarioAtual].login,
                    usuarios[usuarioAtual].qtdPlaylists, usuarios[usuarioAtual].qtdPlaylistsFav);
                break;

            case 2:
                printf("Digite a senha atual: ");
                scanf("%s", senha);
                if (strcmp(usuarios[usuarioAtual].senha, senha) == 0) {
                    printf("Digite o novo nome: ");
                    scanf(" %[^\n]s", nome);
                    strcpy(usuarios[usuarioAtual].nome, nome);
                    salvarUsuarios(); // Salva a alteração no arquivo
                    printf("Nome alterado com sucesso!\n");
                } else {
                    printf("Senha incorreta!\n");
                }
                break;

            case 3:
                printf("Digite a senha atual: ");
                scanf("%s", senha);
                if (strcmp(usuarios[usuarioAtual].senha, senha) == 0) {
                    printf("Digite o novo login: ");
                    scanf("%s", usuarios[usuarioAtual].login);
                    salvarUsuarios(); // Salva a alteração no arquivo
                    printf("Login alterado com sucesso!\n");
                } else {
                    printf("Senha incorreta!\n");
                }
                break;

            case 4:
                printf("Digite a senha atual: ");
                scanf("%s", senha);
                if (strcmp(usuarios[usuarioAtual].senha, senha) == 0) {
                    printf("Digite a nova senha: ");
                    scanf("%s", senha);
                    printf("Confirme a nova senha: ");
                    scanf("%s", confirmacaoSenha);
                    if (strcmp(senha, confirmacaoSenha) == 0) {
                        strcpy(usuarios[usuarioAtual].senha, senha);
                        salvarUsuarios(); // Salva a alteração no arquivo
                        printf("Senha alterada com sucesso!\n");
                    } else {
                        printf("As senhas não conferem!\n");
                    }
                } else {
                    printf("Senha incorreta!\n");
                }
                break;

            case 5:
                printf("Lista de Usuários:\n");
                for (int i = 0; i < qtdUsuarios; i++) {
                    printf("Nome: %s\n", usuarios[i].nome);
                }
                break;

            case 6:
                printf("Digite parte do nome do usuário: ");
                scanf(" %[^\n]s", nome);
                printf("Usuários encontrados:\n");
                for (int i = 0; i < qtdUsuarios; i++) {
                    if (strstr(usuarios[i].nome, nome) != NULL) {
                        printf("Nome: %s\n", usuarios[i].nome);
                    }
                }
                break;

            case 7:
                listarMusicas();
                break;

            case 8:
                consultarMusicas();
                break;

            case 9:
                printf("Suas playlists:\n");
                for (int i = 0; i < usuarios[usuarioAtual].qtdPlaylists; i++) {
                    struct Playlist *playlist = &usuarios[usuarioAtual].playlists[i];
                    printf("Código: %d, Título: %s\n", playlist->codigo, playlist->titulo);
                }
                break;

            case 10:
                printf("Playlists de outros usuários:\n");
                for (int i = 0; i < qtdUsuarios; i++) {
                    if (i != usuarioAtual) {
                        for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
                            struct Playlist *playlist = &usuarios[i].playlists[j];
                            printf("Código: %d, Título: %s, Criador: %s\n", playlist->codigo, playlist->titulo, usuarios[i].nome);
                        }
                    }
                }
                break;

            case 11:
                consultarPlaylist();
                break;

            case 12:
                cadastrarPlaylist(usuarioAtual);
                break;

            case 13:
                inserirMusicaNaPlaylist(usuarioAtual);
                break;

            case 14:
                excluirMusicaDaPlaylist(usuarioAtual);
                break;

            case 15:
                excluirPlaylist(usuarioAtual);
                break;

            case 16:
                favoritarPlaylist(usuarioAtual);
                break;

            case 17:
                logado = 0;
                break;

            default:
                printf("Opção inválida!\n");
        }
    }
}
void salvarUsuarios() {
    FILE *arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar usuários.\n");
        return;
    }

    for (int i = 0; i < qtdUsuarios; i++) {
        fprintf(arquivo, "%d %s %s %s %d %d\n",
                usuarios[i].codigo,
                usuarios[i].nome,
                usuarios[i].login,
                usuarios[i].senha,
                usuarios[i].qtdPlaylists,
                usuarios[i].qtdPlaylistsFav);
        // Adicionar a lógica para salvar playlists e playlistsFav, se necessário.
    }

    fclose(arquivo);
    printf("Usuários salvos com sucesso.\n");
}

void cadastrarPlaylist(int usuarioAtualIndice) {
    if (usuarios[usuarioAtualIndice].qtdPlaylists >= TAM_PLAYLIST) {
        printf("Limite de playlists atingido.\n");
        return;
    }

    struct Playlist novaPlaylist;
    novaPlaylist.codigo = gerarCodigoUnicoParaPlaylist();
    novaPlaylist.codUsuario = usuarios[usuarioAtualIndice].codigo;
    novaPlaylist.qtdMusicas = 0;

    printf("Digite o título da playlist: ");
    scanf(" %[^\n]s", novaPlaylist.titulo);

    usuarios[usuarioAtualIndice].playlists[usuarios[usuarioAtualIndice].qtdPlaylists++] = novaPlaylist;

    salvarUsuarios();
    printf("Playlist cadastrada com sucesso.\n");
}

void excluirMusicaDaPlaylist(int usuarioAtualIndice) {
    int codigoPlaylist, codigoMusica;

    printf("Digite o código da playlist: ");
    scanf("%d", &codigoPlaylist);

    struct Playlist* playlist = NULL;
    for (int i = 0; i < usuarios[usuarioAtualIndice].qtdPlaylists; i++) {
        if (usuarios[usuarioAtualIndice].playlists[i].codigo == codigoPlaylist) {
            playlist = &usuarios[usuarioAtualIndice].playlists[i];
            break;
        }
    }

    if (playlist == NULL) {
        printf("Playlist não encontrada.\n");
        return;
    }

    while (1) {
        printf("Digite o código da música para excluir (ou -1 para sair): ");
        scanf("%d", &codigoMusica);

        if (codigoMusica == -1) break;

        int found = 0;
        for (int i = 0; i < playlist->qtdMusicas; i++) {
            if (playlist->musicas[i] == codigoMusica) {
                found = 1;
                for (int j = i; j < playlist->qtdMusicas - 1; j++) {
                    playlist->musicas[j] = playlist->musicas[j + 1];
                }
                playlist->qtdMusicas--;
                break;
            }
        }

        if (!found) {
            printf("Música não encontrada na playlist.\n");
        }
    }

    salvarUsuarios();
}

void excluirPlaylist(int usuarioAtualIndice) {
    int codigoPlaylist;

    printf("Digite o código da playlist: ");
    scanf("%d", &codigoPlaylist);

    int found = 0;
    for (int i = 0; i < usuarios[usuarioAtualIndice].qtdPlaylists; i++) {
        if (usuarios[usuarioAtualIndice].playlists[i].codigo == codigoPlaylist) {
            found = 1;
            printf("Playlist %s será excluída. Confirmar? (s/n): ", usuarios[usuarioAtualIndice].playlists[i].titulo);
            char confirm;
            scanf(" %c", &confirm);

            if (confirm == 's' || confirm == 'S') {
                for (int j = i; j < usuarios[usuarioAtualIndice].qtdPlaylists - 1; j++) {
                    usuarios[usuarioAtualIndice].playlists[j] = usuarios[usuarioAtualIndice].playlists[j + 1];
                }
                usuarios[usuarioAtualIndice].qtdPlaylists--;
                salvarUsuarios();
                printf("Playlist excluída com sucesso.\n");
            } else {
                printf("Exclusão cancelada.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Playlist não encontrada.\n");
    }
}

void favoritarPlaylist(int usuarioAtualIndice) {
    int codigoPlaylist;

    printf("Digite o código da playlist para favoritar: ");
    scanf("%d", &codigoPlaylist);

    // Verificar se a playlist não é do próprio usuário
    int found = 0;
    for (int i = 0; i < qtdUsuarios; i++) {
        if (i != usuarioAtualIndice) {
            for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
                if (usuarios[i].playlists[j].codigo == codigoPlaylist) {
                    found = 1;
                    break;
                }
            }
        }
    }

    if (!found) {
        printf("Playlist não encontrada ou pertence ao próprio usuário.\n");
        return;
    }

    // Adicionar a playlist aos favoritos do usuário
    if (usuarios[usuarioAtualIndice].qtdPlaylistsFav < TAM_PLAYLIST) {
        usuarios[usuarioAtualIndice].playlistsFav[usuarios[usuarioAtualIndice].qtdPlaylistsFav++] = codigoPlaylist;
        salvarUsuarios();
        printf("Playlist favoritada com sucesso.\n");
    } else {
        printf("Limite de playlists favoritadas atingido.\n");
    }
}

int gerarCodigoUnicoParaPlaylist() {
    int codigo;
    int codigoUnico = 0;

    // Função auxiliar para verificar se o código já existe entre todas as playlists de todos os usuários
    int codigoJaExiste(int codigo) {
        for (int i = 0; i < qtdUsuarios; i++) {
            for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
                if (usuarios[i].playlists[j].codigo == codigo) {
                    return 1;
                }
            }
        }
        return 0;
    }

    do {
        codigo = rand(); // Gera um código aleatório
        codigoUnico = !codigoJaExiste(codigo);
    } while (!codigoUnico);

    return codigo;
}

void inserirMusicaNaPlaylist(int usuarioAtualIndice) {
    int codigoPlaylist, codigoMusica;
    printf("Digite o código da playlist: ");
    scanf("%d", &codigoPlaylist);

    struct Usuario *usuario = &usuarios[usuarioAtualIndice];
    struct Playlist *playlist = NULL;

    for (int i = 0; i < usuario->qtdPlaylists; i++) {
        if (usuario->playlists[i].codigo == codigoPlaylist) {
            playlist = &usuario->playlists[i];
            break;
        }
    }

    if (playlist == NULL) {
        printf("Playlist não encontrada.\n");
        return;
    }

    printf("Digite o código da música: ");
    scanf("%d", &codigoMusica);

    int indexMusica = buscarMusicaPorCodigo(codigoMusica);
    if (indexMusica == -1) {
        printf("Música não encontrada.\n");
        return;
    }

    if (playlist->qtdMusicas >= MAX_MUSICAS) {
        printf("A playlist já contém o número máximo de músicas.\n");
        return;
    }

    playlist->musicas[playlist->qtdMusicas] = codigoMusica;
    playlist->qtdMusicas++;
    salvarUsuarios();

    printf("Música inserida na playlist com sucesso!\n");
}

void salvarMusicas() {
    FILE *arquivo = fopen("musicas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de músicas.\n");
        return;
    }

    for (int i = 0; i < qtdMusicas; i++) {
        fprintf(arquivo, "%d;%s;%s\n", musicas[i].codigo, musicas[i].titulo, musicas[i].artista);
    }

    fclose(arquivo);
}
