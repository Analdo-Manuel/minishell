/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:28:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/23 16:37:11 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_screen(char **envp)
{
	char	**args;

    args = (char **) malloc(2);
	args[0] = "clear";
	args[1] = NULL;
	if (fork() == 0)
	{
    	if (execve("/usr/bin/clear", args, envp) == -1)
		{
        	perror("execve failed");
        	return ;
    	}
	}
	wait(0);
	free(args);
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*str;

	(void)ac;
	(void)av;
	clear_screen(envp);
	while (true)
	{
		data.son = false;
		str = getenv("USER");
		if (!str)
			printf(BOLD GREEN "minishell" RESET);
		else
			printf(BOLD GREEN "%s" RESET, str);
		data.command = readline(BOLD GREEN "% " RESET);
		add_history(data.command);
		data.matrix = ft_split_one(data.command);
		data.path_main = find_executable(&data);
		if (strcmp(data.command, "exit") == 0)
		{
			break ;
		}
		if (data.path_main)
		{
			if (fork() == 0)
				execve(data.path_main, data.matrix, envp);
			wait(0);	
			if (data.son == false)
				free_total(&data);
			else
				free_all(data.matrix);
		}
		else
			printf("Comando '%s' não encontrado\n", data.command);
	}
	free_total(&data);
	return (0);
}
