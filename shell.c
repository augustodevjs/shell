#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_ARGS 64
#define TRUE 1

char entrada_usuario[64];
char *args[MAX_ARGS];

void mostrar_prompt()
{
    printf("#Inserir comando: ");
}

void ler_entrada(char *args[])
{
    int n = 0;

    fgets(entrada_usuario, sizeof(entrada_usuario), stdin);
    entrada_usuario[strcspn(entrada_usuario, "\n")] = '\0';

    args[0] = strtok(entrada_usuario, " ");
    while (n < MAX_ARGS - 1 && args[n] != NULL)
    {
        n++;
        args[n] = strtok(NULL, " ");
    }
    args[n] = NULL;
}

int main()
{
    while (TRUE)
    {
        mostrar_prompt();
        ler_entrada(args);

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Erro ao criar processo");
            exit(EXIT_FAILURE);
        }
        else if (pid != 0)
        {
            wait(NULL);
        }
        else
        {
            if (execvp(args[0], args) == -1)
            {
                perror("Erro ao executar comando");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}