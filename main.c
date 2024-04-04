#include <stdio.h>
#include <string.h>

int main()
{
  char entrada[50]; // Variável para armazenar a entrada do usuário

  // Solicita que o usuário insira uma entrada
  printf("Digite um comando: ");
  fgets(entrada, sizeof(entrada), stdin);

  // Remove o caractere de nova linha (\n) no final da entrada
  entrada[strcspn(entrada, "\n")] = '\0';

  // Verifica se a entrada contém palavras-chave específicas
  if (strstr(entrada, "Abrir Porta") != NULL)
  {
    printf("Comando reconhecido: Abrir Porta\n");
  }
  else if (strstr(entrada, "Fechar Porta") != NULL)
  {
    printf("Comando reconhecido: Fechar Porta\n");
  }
  else
  {
    printf("Comando não reconhecido.\n");
  }

  return 0;
}

void tutorial()
{
  printf("Bem-vindo ao tutorial do jogo!\n");
}
