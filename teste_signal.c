/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:02:04 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/18 12:33:40 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(__attribute__((unused)) int ac, char **av)
{    
    int original_fd = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(original_fd, 1); // 1 é o descritor de saída padrão (stdout)

    // Agora, a saída padrão será redirecionada para "file.txt"
    printf("Esta mensagem será gravada no arquivo!\n");
    

    close(original_fd); // Fecha o descritor original
    return 0;
}