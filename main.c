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
    int atTable; // Adicionado para rastrear se o jogador está na mesa
} Player;

Player defaultPlayer()
{
    Player player = {3, 1, 0, 0, 0};
    return player;
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
                printGradually("Voce abriu a porta e saiu da sala.\n", DELAY_MICROSECONDS);
                return 0;
            }
            else
            {
                printGradually("A porta esta trancada. Voce precisa de uma chave.\n", DELAY_MICROSECONDS);
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
        else if (strstr(input, "AJUDA") != NULL)
        {
            printGradually(
                "Comandos disponiveis:\n"
                "- ABRIR PORTA: Tenta abrir a porta.\n"
                "- IR ATE MESA: Vai ate a mesa.\n"
                "- PEGAR CHAVE: Pega a chave na mesa (precisa estar perto).\n"
                "- DESTRANCAR PORTA: Destranca a porta (se voce tiver a chave).\n"
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

    printGradually(
        "Bem-vindo ao jogo! (Digite AJUDA caso nao saiba os comandos)\n"
        "Voce esta em uma sala. Veja se consegue sair.\n",
        DELAY_MICROSECONDS);

    firstRoom(&player);

    printGradually("Fim do jogo. Obrigado por jogar!\n", DELAY_MICROSECONDS);

    return 0;
}
