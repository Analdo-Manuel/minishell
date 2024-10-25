/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analdo <analdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:28:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/23 23:19:37 by analdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(t_data *data, char **envp)
{
	if (data->path_main)
	{
		if (fork() == 0)
			execve(data->path_main, data->matrix, envp);
		wait(0);
		if (data->son == false)
			free_total(data);
		else
			free_all(data->matrix);
	}
	else
		printf("zsh: command not found: %s\n", data->command);
}

void	loop_prompt(t_data *data, char **envp)
{
	while (true)
	{
		data->son = false;
		if (!getenv("USER"))
			printf(BOLD GREEN "minishell" RESET);
		else
			printf(BOLD GREEN "%s" RESET, getenv("USER"));
		data->command = readline(BOLD GREEN "% " RESET);
		add_history(data->command);
		data->matrix = ft_split_one(data->command);
		data->path_main = find_executable(data);
		if (strcmp(data->command, "exit") == 0)
			break ;
		print_prompt(data, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	clear_screen(envp);
	(void)ac;
	(void)av;
	loop_prompt(&data, envp);
	free_total(&data);
	return (0);
}
