/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:02:04 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/25 11:10:34 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
 
 /*
int main() {
    // Abre ou cria o arquivo para escrita
    int fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Salvar o descritor de arquivo original de STDOUT_FILENO (1)
    int stdout_backup = dup(1);
    if (stdout_backup == -1) {
        perror("dup");
        return 1;
    }
    printf("Agora estamos de volta ao terminal!\n");

    // Redireciona stdout para o arquivo 'saida.txt'
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }
    close(fd);
    printf("Esta linha será escrita no arquivo 'saida.txt'.\n");

    // A partir daqui, qualquer coisa que escrevemos no stdout será gravada no arquivo 'saida.txt'

    // Fechar o descritor do arquivo

    if (dup2(stdout_backup, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }    // Restaurar o stdout original (do terminal)

    // Agora a saída padrão volta a ser para o terminal

    // Fechar o descritor de backup
    close(stdout_backup);

    return 0;
}
*/

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putnbr(int n)
{
    if (n > INT_MAX || n < INT_MIN)
        return ;
    if (n < 0)
    {
        ft_putchar('-');
        n = -n;
    }
    if (n > 9)
        ft_putnbr(n / 10);
    ft_putchar(n % 10 + '0');
}

void ft_foreach(int *tab, int length, void (*f)(int))
{
    int i;

    i = 0;
    while (i < length)
    {
        f(tab[i]);
        ft_putchar('\n');
        i++;
    }
}

int main(void)
{
    int tab[100];

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
        tab[i] = rand() % 10000;
    ft_foreach(tab, 100, &ft_putnbr);
    return (0);
}


