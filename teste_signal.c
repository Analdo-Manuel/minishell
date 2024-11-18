/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:02:04 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/15 15:27:35 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int original_fd = open("file.txt", O_WRONLY | O_CREAT, 0644);
    if (original_fd == -1) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Duplica o descritor de arquivo original para o descritor 1 (stdout)
    int new_fd = dup2(original_fd, 1); // 1 é o descritor de saída padrão (stdout)
    if (new_fd == -1) {
        perror("Erro ao duplicar o descritor");
        return 1;
    }

    // Agora, a saída padrão será redirecionada para "file.txt"
    printf("Esta mensagem será gravada no arquivo!\n");
    printf("Esta mensagem será gravada no arquivo!\n");
    

    close(original_fd); // Fecha o descritor original
    return 0;
}