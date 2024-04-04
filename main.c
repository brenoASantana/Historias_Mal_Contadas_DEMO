#include <stdio.h>
#include <string.h>
#include <unistd.h> // Para o usleep()
#include <conio.h>
#include "inc/fmod.h"

FSOUND_SAMPLE *handle;

#define atraso 100000 // 100000 microssegundos = 100 milissegundos = 0,1 segundos

void imprimirGradualmente(const char *texto, unsigned int microseconds)
{
  while (*texto)
  {
    putchar(*texto++);
    fflush(stdout); // Força a saída do buffer para o terminal
    usleep(milliseconds);
  }
}

void tutorial()
{
  imprimirGradualmente("Seja bem-vindo ao tutorial!\n", atraso);
  imprimirGradualmente("Digite \"ajuda\" caso queira ver este tutorial durante o jogo.\n", atraso);
}

int main()
{
  // init FMOD sound system
  FSOUND_Init(44100, 32, 0);

  // load and play mp3
  handle = FSOUND_Sample_Load(0, "my.mp3", 0, 0, 0);
  FSOUND_PlaySound(0, handle);

  // wait until the users hits a key to end the app
  while (!_kbhit())
  {
  }

  // clean up
  FSOUND_Sample_Free(handle);
  FSOUND_Close();

  while (1)
  {
    tutorial();
    char entrada[50]; // Variável para armazenar a entrada do usuário

    // Solicita que o usuário insira uma entrada
    imprimirGradualmente("Digite um comando: ", atraso);
    fgets(entrada, sizeof(entrada), stdin);

    // Remove o caractere de nova linha (\n) no final da entrada
    entrada[strcspn(entrada, "\n")] = '\0';

    // Verifica se a entrada contém palavras-chave específicas
    if (strstr(entrada, "Abrir Porta") != NULL)
    {
      imprimirGradualmente("Comando reconhecido: Abrir Porta\n", atraso);
    }
    else if (strstr(entrada, "Fechar Porta") != NULL)
    {
      imprimirGradualmente("Comando reconhecido: Fechar Porta\n", atraso);
    }
    else
    {
      imprimirGradualmente("Comando não reconhecido.\n", atraso);
    }

    return 0;
  }
}