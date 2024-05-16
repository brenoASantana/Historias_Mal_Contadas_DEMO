#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para o usleep()

// Definindo o atraso em microssegundos
#define atraso 15000 

void imprimirGradualmente(const char *texto, unsigned int microseconds)
{
  while (*texto)
  {
    putchar(*texto++);
    fflush(stdout); // Força a saída do buffer para o terminal
    usleep(microseconds);
  }
}

void tutorial()
{
  imprimirGradualmente("Seja bem-vindo ao tutorial!\n", atraso);
  imprimirGradualmente("Digite \"ajuda\" caso queira ver este tutorial durante o jogo.\n", atraso);
}

int main()
{
  while (1)
  {
    tutorial();
    char entrada[50]; // Variável para armazenar a entrada do usuário

    // Solicita que o usuário insira uma entrada
    imprimirGradualmente("Digite um comando: ", atraso);
    fgets(entrada, sizeof(entrada), stdin);

    // Remove o caractere de nova linha (\n) no final da entrada
    entrada[strcspn(entrada, "\n")] = '\0';

    // Converter entrada para minúsculas
    for (int i = 0; entrada[i]; i++)
    {
      entrada[i] = tolower(entrada[i]);
    }

    // Verifica se a entrada contém palavras-chave específicas
    if (strstr(entrada, "abrir porta") != NULL)
    {
      imprimirGradualmente("Comando reconhecido: Abrir Porta\n", atraso);
    }
    else if (strstr(entrada, "fechar porta") != NULL)
    {
      imprimirGradualmente("Comando reconhecido: Fechar Porta\n", atraso);
    }
    else if (strstr(entrada, "jumpscare") != NULL)
    {
      // Abrir e imprimir o conteúdo do arquivo "jumpscaSe.txt"
      FILE *arquivo;
      arquivo = fopen("C:/Coding/IHNMAIMS_Demo/images/jumpscare.txt", "r");
      if (arquivo == NULL)
      {
        printf("Erro ao abrir o arquivo jumpscare.txt\n");
        return 1;
      }

      char linha[100];
      while (fgets(linha, sizeof(linha), arquivo) != NULL)
      {
        printf("%s", linha);
        usleep(atraso); // Adiciona um atraso entre cada linha para imprimir gradualmente
      }

      fclose(arquivo);
    }
    else
    {
      imprimirGradualmente("Comando não reconhecido.\n", atraso);
    }
  }

  return 0;
}
