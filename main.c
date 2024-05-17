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
  int hasKey; // Adicionado para rastrear se o jogador tem a chave
} Player;

Player defaultPlayer()
{
  Player player;
  player.hp = 3;
  player.hit = 1;
  player.habilityID = 0;
  player.hasKey = 0; // Inicialmente, o jogador não tem a chave
  return player;
}

typedef struct Enemy
{
  int hp;
  int hit;
} Enemy;

int saveNumber = 1; // Variável estática para rastrear o número de salvamentos

int save(Player *player)
{
  FILE *file;
  char filename[MAX_FILENAME_LENGTH];

  // Construindo o nome do arquivo com base no número de salvamentos
  sprintf(filename, "save%d.txt", saveNumber);

  // Abrindo o arquivo para escrita
  file = fopen(filename, "w");
  if (file == NULL)
  {
    printf("Erro ao criar o arquivo de salvamento.\n");
    return 1; // Indica falha
  }

  // Escrevendo os dados do jogador no arquivo
  fprintf(file, "HP: %d\n", player->hp);
  fprintf(file, "Hit: %d\n", player->hit);
  fprintf(file, "HabilityID: %d\n", player->habilityID);
  fprintf(file, "HasKey: %d\n", player->hasKey);

  // Fechando o arquivo
  fclose(file);

  printf("Jogo salvo com sucesso em %s\n", filename);

  // Incrementando o número de salvamentos para o próximo
  saveNumber++;

  return 0; // Indica sucesso
}

int load(Player *player)
{
  FILE *file;
  char filename[MAX_FILENAME_LENGTH];
  int hp, hit, habilityID, hasKey;

  printf("Digite o número do salvamento que deseja carregar: ");
  scanf("%d", &saveNumber); // Solicita ao usuário o número do salvamento a ser carregado
  getchar();                // Limpa o buffer de entrada

  // Construindo o nome do arquivo com base no número fornecido pelo usuário
  sprintf(filename, "save%d.txt", saveNumber);

  // Abrindo o arquivo para leitura
  file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de salvamento.\n");
    return 1; // Indica falha
  }

  // Lendo os dados do arquivo e atualizando a estrutura Player
  fscanf(file, "HP: %d\n", &hp);
  fscanf(file, "Hit: %d\n", &hit);
  fscanf(file, "HabilityID: %d\n", &habilityID);
  fscanf(file, "HasKey: %d\n", &hasKey);

  // Atualizando os dados do jogador na estrutura Player
  player->hp = hp;
  player->hit = hit;
  player->habilityID = habilityID;
  player->hasKey = hasKey;

  // Fechando o arquivo
  fclose(file);

  printf("Dados do salvamento %d carregados com sucesso.\n", saveNumber);

  return 0; // Indica sucesso
}

void printGradually(const char *text, unsigned int microseconds)
{
  while (*text)
  {
    putchar(*text++);
    fflush(stdout); // Força a saída do buffer para o terminal
    usleep(microseconds);
  }
}

void tutorial()
{

}

void firstRoom(Player *player)
{
  static int doorUnlocked = 0;

  char input[50]; // Variável para armazenar a entrada do usuário

  // Abrir e imprimir o conteúdo do arquivo
  FILE *file = fopen("C:/Coding/IHNMAIMS_Demo/dialogues/prologue.txt", "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de diálogo.\n");
    return;
  }

  char line[100];
  while (fgets(line, sizeof(line), file) != NULL)
  {
    printGradually(line, DELAY_MICROSECONDS);
  }

  fclose(file);

  // Solicita que o usuário insira uma entrada
  printGradually("Digite um comando: ", DELAY_MICROSECONDS);
  fgets(input, sizeof(input), stdin);

  // Remove o caractere de nova linha (\n) no final da entrada
  input[strcspn(input, "\n")] = '\0';

  // Converter entrada para maiúsculas
  for (int i = 0; input[i]; i++)
  {
    input[i] = toupper(input[i]);
  }

  // Verifica se a entrada contém palavras-chave específicas
  if (strstr(input, "ABRIR PORTA") != NULL)
  {
    if (doorUnlocked)
    {
      printGradually("Você abriu a porta e saiu da sala.\n", DELAY_MICROSECONDS);
    }
    else
    {
      printGradually("A porta está trancada.\n", DELAY_MICROSECONDS);
    }
  }
  else if (strstr(input, "IR ATE MESA") != NULL)
  {
    printGradually("Você foi até a mesa.\n", DELAY_MICROSECONDS);
  }
  else if (strstr(input, "PEGAR CHAVE") != NULL)
  {
    player->hasKey = 1;
    printGradually("Você pegou a chave.\n", DELAY_MICROSECONDS);
  }
  else if (strstr(input, "DESTRANCAR PORTA") != NULL)
  {
    if (player->hasKey)
    {
      doorUnlocked = 1;
      printGradually("Você destrancou a porta.\n", DELAY_MICROSECONDS);
    }
    else
    {
      printGradually("Você não tem a chave para destrancar a porta.\n", DELAY_MICROSECONDS);
    }
  }
  else if (strstr(input, "JUMPSCARE") != NULL)
  {
    // Implementação do jumpscare
  }
  else if (strstr(input, "AJUDA") != NULL)
  {
    tutorial();
  }
  else
  {
    printGradually("Comando não reconhecido.\n", DELAY_MICROSECONDS);
  }
}

int main()
{
  Player player = defaultPlayer();

    // Abrir e imprimir o conteúdo do arquivo
  FILE *file = fopen("C:/Coding/IHNMAIMS_Demo/dialogues/tutorial.txt", "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo de diálogo.\n");
    return;
  }

  char line[100];
  while (fgets(line, sizeof(line), file) != NULL)
  {
    printGradually(line, DELAY_MICROSECONDS);
  }
  while (1)
  {
    firstRoom(&player);
    // Adicione outras salas ou lógica do jogo aqui
    break;
  }

  return 0;
}