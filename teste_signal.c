/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:02:04 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/14 11:18:21 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo) {
    if (signo == SIGINT) {
        printf("\nRecebido SIGINT! Saindo...\n");
        exit(0);  // Termina o programa ao receber SIGINT
    }
    else
    {
        printf("\nRecebido SIGQUIT! Saindo...\n");
    }
}

int main() {
    // Configura o manipulador para o sinal SIGINT
    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("Erro ao configurar o manipulador de sinal");
        exit(1);
    }
    if (signal(SIGQUIT, handler) == SIG_ERR) {
        perror("Erro ao configurar o manipulador de sinal");
        exit(1);
    }
    
    // Loop infinito aguardando sinais
    while (1) {
        printf("Esperando sinal SIGINT...\n");
        sleep(1);  // Simula o programa fazendo trabalho
    }

    return 0;
}