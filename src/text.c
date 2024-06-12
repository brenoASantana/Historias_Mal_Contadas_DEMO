#include "../include/text.h"

// Função para ler o conteúdo de um arquivo de texto
char *ReadTextFile(const char *filename)
{
    FILE *file = fopen(filename, "r"); // Abre o arquivo para leitura de texto
    if (!file)
    {
        return NULL; // Retorna NULL se o arquivo não puder ser aberto
    }

    // Obtém o tamanho do arquivo
    fseek(file, 0, SEEK_END);  // Move o cursor para o fim do arquivo
    long length = ftell(file); // Obtém o tamanho do arquivo em bytes
    fseek(file, 0, SEEK_SET);  // Move o cursor de volta para o início do arquivo

    // Aloca memória para armazenar o conteúdo do arquivo
    char *buffer = (char *)malloc(length + 1);
    if (!buffer)
    {
        fclose(file);
        return NULL;
    }

    // Lê o conteúdo do arquivo para o buffer
    fread(buffer, 1, length, file);
    buffer[length] = '\0'; // Adiciona um terminador nulo ao final da string

    fclose(file);  // Fecha o arquivo

    return buffer; // Retorna o buffer contendo o conteúdo do arquivo
}

// Função para desenhar texto com delay, considerando quebra de linha ao pressionar "Enter"
void DrawTextWithDelay(const char *text, int x, int y, int fontSize, Color baseColor, int *charCount, int textSpeed)
{   
    int length = strlen(text); // Calcula o comprimento total do texto
    if (*charCount < length)
    {
        *charCount += textSpeed; // Incrementa o contador de caracteres com base na velocidade de desenho
    }

    int posY = y; // Define a posição Y inicial
    int lineHeight = fontSize + 2; // Define a altura da linha, ajustável conforme necessário
    char buffer[256]; // Cria um buffer temporário para armazenar as linhas de texto
    int bufferIndex = 0; // Índice do buffer

    // Loop através do texto até o contador de caracteres
    for (int i = 0; i < *charCount; i++)
    {
        // Verifica se o caractere atual é uma quebra de linha ou se o buffer atingiu seu limite
        if (text[i] == '\n' || bufferIndex >= sizeof(buffer) - 1)
        {
            buffer[bufferIndex] = '\0'; // Adiciona um terminador nulo ao final do buffer
            DrawText(buffer, x, posY, fontSize, baseColor); // Desenha o texto atual no buffer

            // Move para a próxima linha se o caractere atual for uma quebra de linha
            if (text[i] == '\n') {
                posY += lineHeight; // Move para a próxima linha
            }

            bufferIndex = 0; // Reinicia o índice do buffer para o próximo texto
        }
        else
        {
            buffer[bufferIndex++] = text[i]; // Adiciona o caractere ao buffer
        }
    }

    // Desenha a última linha, se houver texto restante
    if (bufferIndex > 0)
    {
        buffer[bufferIndex] = '\0'; // Adiciona um terminador nulo ao final do buffer
        DrawText(buffer, x, posY, fontSize, baseColor); // Desenha o texto restante
    }
}
