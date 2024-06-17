#include "raylib.h"
#include "../include/text.h"
#include <ctype.h> // Adicionado para usar a função toupper

char inputText[256] = "\0"; // Buffer para armazenar o texto digitado
int letterCount = 0;        // Contador de caracteres
bool enterPressed = false;  // Flag para verificar se Enter foi pressionado

// Função para ler o conteúdo de um arquivo de texto
char *ReadTextFile(const char *filename)
{

    // Abre o arquivo para leitura de texto
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return NULL;
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
    size_t bytesRead = fread(buffer, 1, length, file);
    if (bytesRead != length)
    {
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[length] = '\0'; // Adiciona um terminador nulo ao final da string

    fclose(file); // Fecha o arquivo

    return buffer; // Retorna o buffer contendo o conteúdo do arquivo
}

// Função para desenhar texto com delay, considerando quebra de linha ao pressionar "Enter"
void DrawTextWithDelay(const char *text, int x, int y, int fontSize, Color baseColor, int *charCount, int textSpeed)
{
    if (text == NULL || charCount == NULL)
    {
        return;
    }

    int length = strlen(text); // Calcula o comprimento total do texto
    if (*charCount < length)
    {
        *charCount += textSpeed; // Incrementa o contador de caracteres com base na velocidade de desenho
    }

    int posX = x;                  // Define a posição X inicial
    int posY = y;                  // Define a posição Y inicial
    int lineHeight = fontSize + 2; // Define a altura da linha, ajustável conforme necessário
    char buffer[256];              // Cria um buffer temporário para armazenar as linhas de texto
    int bufferIndex = 0;           // Índice do buffer

    // Define o limite da tela
    int screenWidthLimit = GetScreenWidth() - 40;

    // Loop através do texto até o contador de caracteres
    for (int i = 0; i < *charCount && i < length; i++)
    {
        // Verifica se o caractere atual é uma quebra de linha ou se o buffer atingiu seu limite
        if (text[i] == '\n' || bufferIndex >= sizeof(buffer) - 1)
        {
            buffer[bufferIndex] = '\0';                        // Adiciona um terminador nulo ao final do buffer
            DrawText(buffer, posX, posY, fontSize, baseColor); // Desenha o texto atual no buffer
            posY += lineHeight;                                // Move para a próxima linha
            bufferIndex = 0;                                   // Reinicia o índice do buffer para o próximo texto
                                                               // Verifica se atingiu o limite da tela na posição X
            if (posX + 40 > screenWidthLimit)
            {
                posX = x;   // Reinicia a posição X
                posY += 10; // Avança a posição Y para a próxima linha
                break;      // Para de desenhar se atingir o limite da tela na posição X
            }
        }
        else
        {
            buffer[bufferIndex++] = text[i]; // Adiciona o caractere ao buffer
        }
    }

    // Desenha a última linha, se houver texto restante
    if (bufferIndex > 0)
    {
        buffer[bufferIndex] = '\0';                        // Adiciona um terminador nulo ao final do buffer
        DrawText(buffer, posX, posY, fontSize, baseColor); // Desenha o texto restante
    }
}

void GetUserInput(char *buffer, int maxLength, int *count)
{
    if (buffer == NULL || count == NULL)
    {
        return;
    }

    int key = GetCharPressed();
    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && (*count < (maxLength - 1)))
        {
            buffer[*count] = toupper((char)key); // Converte para maiúsculo antes de adicionar ao buffer
            (*count)++;
            buffer[*count] = '\0'; // Adiciona o caractere nulo
        }

        key = GetCharPressed(); // Verifica se mais teclas foram pressionadas
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (*count > 0)
        {
            (*count)--;
            buffer[*count] = '\0'; // Adiciona o caractere nulo
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        enterPressed = true; // Define a flag para indicar que Enter foi pressionado
    }
}
