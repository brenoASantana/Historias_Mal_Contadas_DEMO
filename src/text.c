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
        
        // Substitui todos os pontos de interrogação por pontos finais
        for (int i = 0; i < length; i++)
        {
            if (buffer[i] == '?')
                buffer[i] = '.';
        }
    }

    fclose(file);  // Fecha o arquivo
    return buffer; // Retorna o buffer contendo o conteúdo do arquivo
}

void DrawTextWithFade(const char *text, int x, int y, int fontSize, Color baseColor, int *charCount, float *alpha, TextState *state)
{
    int length = strlen(text);
    Color color = baseColor;
    color.a = (unsigned char)(*alpha * 255);

    switch (*state)
    {
        case FADE_IN:
            *alpha += FADE_SPEED;
            if (*alpha >= 1.0f)
            {
                *alpha = 1.0f;
                *state = FULL_DISPLAY;
            }
            break;
        case FULL_DISPLAY:
            if (*charCount < length)
            {
                char nextChar = text[*charCount];
                if (nextChar == '?')
                {
                    DrawText(".", x + MeasureText(TextSubtext(text, 0, *charCount), fontSize), y, fontSize, color);
                    (*charCount)++;
                }
                else
                {
                    DrawText(TextSubtext(text, 0, *charCount + 1), x, y, fontSize, color);
                    (*charCount)++;
                }
            }
            else
            {
                DrawText(text, x, y, fontSize, color);
            }
            *state = FADE_OUT;
            break;
        case FADE_OUT:
            *alpha -= FADE_SPEED;
            if (*alpha <= 0.0f)
            {
                *alpha = 0.0f;
                *state = FADE_IN;
                *charCount = 0; // Reinicia a contagem de caracteres
            }
            break;
    }

    DrawText(TextSubtext(text, 0, *charCount + 1), x, y, fontSize, color);
}
