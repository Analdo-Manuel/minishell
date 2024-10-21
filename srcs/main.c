/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:28:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/21 10:31:56 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		//char *const av[] = {str ,NULL};
		//char *path = getenv("PATH");
		//char *const envp[] = { path , NULL};

		//execve("/bin/ls", av, envp);
		if (strcmp(str, "exit") == 0)
		{
			free(str);
			break ;
		}/*
		if (strcmp(str, "alterar") == 0)
		{
			//rl_replace_line("Linha a substituir!\n", 0);
			rl_redisplay();
			add_history(str);
		}*/
		free(str);
	}
	return (0);
}
