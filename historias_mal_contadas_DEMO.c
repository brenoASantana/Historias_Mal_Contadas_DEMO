#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para o usleep()
#include <ctype.h>  // Para toupper()

#define MAX_FILENAME_LENGTH 20
#define DELAY_MICROSECONDS 15000

typedef struct Player
{
    int hp;
    int hit;
    int habilityID;
    int hasKey;
    int atTable;
} Player;

Player defaultPlayer()
{
    Player player = {3, 1, 0, 0, 0};
    return player;
}

typedef struct Enemy
{
    int hp;
    int hit;
} Enemy;

Enemy *createEnemy()
{
    Enemy *enemy = malloc(sizeof(Enemy));
    if (enemy == NULL)
    {
        // Falha na alocação de memória
        return NULL;
    }
    enemy->hp = 2; // Definindo os valores iniciais para o inimigo
    enemy->hit = 1;
    return enemy;
}

int battle(Player *player, Enemy *enemy)
{
    printGradually("e entrou em uma batalha!\n", DELAY_MICROSECONDS);

    while (player->hp > 0 && enemy->hp > 0)
    {
        // Mostrar a vida do jogador
        printf("Sua vida: %d\n", player->hp);

        // Opções de ação
        printGradually("Escolha sua acao (ATAQUE ou BLOQUEAR): ", DELAY_MICROSECONDS);
        char action[20];
        fgets(action, sizeof(action), stdin);
        action[strcspn(action, "\n")] = '\0';
        for (int i = 0; action[i]; i++)
        {
            action[i] = toupper(action[i]);
        }

        if (strcmp(action, "ATAQUE") == 0)
        {
            // Player ataca
            enemy->hp -= player->hit;
            printGradually("Você atacou o inimigo!\n", DELAY_MICROSECONDS);
        }
        else if (strcmp(action, "BLOQUEAR") == 0)
        {
            // Player bloqueia
            player->hp++;
            printGradually("Você bloqueou o ataque do inimigo!\n", DELAY_MICROSECONDS);
        }
        else
        {
            printGradually("Acao inválida! Escolha ATAQUE ou BLOQUEAR.\n", DELAY_MICROSECONDS);
            continue; // Volta para o início do loop para permitir uma nova escolha
        }

        // Verificar se o inimigo foi derrotado
        if (enemy->hp <= 0)
        {
            printGradually("Você derrotou o inimigo!\n", DELAY_MICROSECONDS);
            return 1; // Retorna 1 para indicar vitória
        }

        // Inimigo ataca
        player->hp -= enemy->hit;
        printGradually("O inimigo atacou você!\n", DELAY_MICROSECONDS);

        // Verificar se o jogador foi derrotado
        if (player->hp <= 0)
        {
            printGradually("Você foi derrotado!\n", DELAY_MICROSECONDS);
            return 0; // Retorna 0 para indicar derrota
        }
    }

    return 0; // Nunca deve chegar aqui, mas apenas para evitar warning do compilador
}

void printGradually(const char *text, unsigned int microseconds)
{
    while (*text)
    {
        putchar(*text++);
        fflush(stdout);
        usleep(microseconds);
    }
}

int saveGame(Player *player, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printGradually("Erro ao salvar o jogo.\n", DELAY_MICROSECONDS);
        return 1;
    }
    fprintf(file, "%d %d %d %d %d\n", player->hp, player->hit, player->habilityID, player->hasKey, player->atTable);
    fclose(file);
    printGradually("Jogo salvo com sucesso.\n", DELAY_MICROSECONDS);
    return 0;
}

int loadGame(Player *player, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printGradually("Erro ao carregar o jogo salvo.\n", DELAY_MICROSECONDS);
        return 1;
    }
    fscanf(file, "%d %d %d %d %d", &player->hp, &player->hit, &player->habilityID, &player->hasKey, &player->atTable);
    fclose(file);
    printGradually("Jogo carregado com sucesso.\n", DELAY_MICROSECONDS);
    return 0;
}

int firstRoom(Player *player)
{
    static int doorUnlocked = 0;
    char input[50];

    printGradually("Voce esta em uma sala. Voce ve uma porta e uma mesa.\n", DELAY_MICROSECONDS);

    while (1)
    {
        printGradually("Digite um comando: ", DELAY_MICROSECONDS);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        for (int i = 0; input[i]; i++)
        {
            input[i] = toupper(input[i]);
        }

        if (strstr(input, "ABRIR PORTA") != NULL)
        {
            if (doorUnlocked)
            {
                printGradually("Voce abriu a porta e entrou em uma sala escura.\n", DELAY_MICROSECONDS);
                Enemy *enemy = createEnemy();
                if (enemy != NULL)
                {
                    if (battle(player, enemy))
                    {
                        printGradually("Voce derrotou o inimigo e encontrou a saida!\n", DELAY_MICROSECONDS);
                        // Aqui você pode adicionar recompensas para o jogador
                    }
                    else
                    {
                        printGradually("Voce foi derrotado pelo inimigo!\n", DELAY_MICROSECONDS);
                        // Aqui você pode adicionar consequências por perder a batalha
                    }
                    free(enemy); // Liberando a memória alocada para o inimigo
                }
                else
                {
                    printGradually("Erro ao criar o inimigo. Memória insuficiente.\n", DELAY_MICROSECONDS);
                }
                return 0;
            }
            else
            {
                printGradually("A porta está trancada. Você precisa de uma chave.\n", DELAY_MICROSECONDS);
            }
        }

        else if (strstr(input, "IR ATE MESA") != NULL)
        {
            player->atTable = 1;
            printGradually("Voce foi ate a mesa.\n", DELAY_MICROSECONDS);
        }
        else if (strstr(input, "PEGAR CHAVE") != NULL)
        {
            if (player->atTable)
            {
                if (!player->hasKey)
                {
                    player->hasKey = 1;
                    printGradually("Voce pegou a chave.\n", DELAY_MICROSECONDS);
                }
                else
                {
                    printGradually("Voce ja pegou a chave.\n", DELAY_MICROSECONDS);
                }
            }
            else
            {
                printGradually("Voce esta longe da mesa. Va ate a mesa primeiro.\n", DELAY_MICROSECONDS);
            }
        }
        else if (strstr(input, "DESTRANCAR PORTA") != NULL)
        {
            if (player->hasKey)
            {
                doorUnlocked = 1;
                printGradually("Voce destrancou a porta.\n", DELAY_MICROSECONDS);
            }
            else
            {
                printGradually("Voce nao tem a chave para destrancar a porta.\n", DELAY_MICROSECONDS);
            }
        }
        else if (strstr(input, "SALVAR") != NULL)
        {
            saveGame(player, "savegame.txt");
        }
        else if (strstr(input, "SAIR") != NULL)
        {
            printGradually("Saindo do jogo...\n", DELAY_MICROSECONDS);
            exit(0);
        }
        else if (strstr(input, "AJUDA") != NULL)
        {
            printGradually(
                "Comandos disponiveis:\n"
                "- ABRIR PORTA: Tenta abrir a porta.\n"
                "- IR ATE MESA: Vai ate a mesa.\n"
                "- PEGAR CHAVE: Pega a chave na mesa (precisa estar perto).\n"
                "- DESTRANCAR PORTA: Destranca a porta (se voce tiver a chave).\n"
                "- SALVAR: Salva o jogo.\n"
                "- SAIR: Sai do jogo.\n"
                "- AJUDA: Mostra esta mensagem de ajuda.\n",
                DELAY_MICROSECONDS);
        }
        else
        {
            printGradually("Comando nao reconhecido.\n", DELAY_MICROSECONDS);
        }
    }
}

int main()
{
    Player player = defaultPlayer();
    char input[10];

    printGradually(
        "Bem-vindo ao jogo! (Digite AJUDA caso nao saiba os comandos)\n"
        "Deseja iniciar um novo jogo ou carregar um save? (novo/carregar): ",
        DELAY_MICROSECONDS);

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcasecmp(input, "carregar") == 0)
    {
        if (loadGame(&player, "savegame.txt") != 0)
        {
            printGradually("Falha ao carregar o save. Iniciando um novo jogo.\n", DELAY_MICROSECONDS);
            player = defaultPlayer();
        }
    }
    else
    {
        player = defaultPlayer();
    }

    firstRoom(&player);

    printGradually("Fim do jogo. Obrigado por jogar!\n", DELAY_MICROSECONDS);

    return 0;
}
