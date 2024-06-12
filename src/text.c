#include "../include/text.h"

char *ReadTextFile(const char *filename)
{
    FILE *file = fopen(filename, "rb"); // Abre o arquivo para leitura binária
    if (!file)
    {
        return NULL; // Retorna NULL se o arquivo não puder ser aberto
    }

    fseek(file, 0, SEEK_END);  // Move o cursor para o fim do arquivo
    long length = ftell(file); // Obtém o tamanho do arquivo em bytes
    fseek(file, 0, SEEK_SET);  // Move o cursor de volta para o início do arquivo

    char *buffer = (char *)malloc(length + 1); // Aloca memória para armazenar o conteúdo do arquivo
    if (buffer)
    {
        fread(buffer, 1, length, file); // Lê o conteúdo do arquivo para o buffer
        buffer[length] = '\0';          // Adiciona um terminador nulo ao final da string
    }

    fclose(file);  // Fecha o arquivo
    return buffer; // Retorna o buffer contendo o conteúdo do arquivo
}

void DrawTextWithDelay(const char *text, int x, int y, int fontSize, Color baseColor, int *charCount, int textSpeed)
{
    int length = strlen(text);
    if (*charCount < length)
    {
        *charCount += textSpeed;
    }

    DrawText(TextSubtext(text, 0, *charCount), x, y, fontSize, baseColor);
}
