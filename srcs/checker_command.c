/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:33:37 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/29 08:12:54 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_prompt(t_data *data, char **envp)
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

void	clear_screen(char **envp)
{
	char	**args;

	args = (char **) malloc(sizeof(char *) * 2);
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

char	*find_executable(t_data *data)
{
	char	*str;
	size_t	i;

	if (access(data->matrix[0], X_OK) == 0)
	{
		data->son = true;
		return (data->matrix[0]);
	}
	data->path = getenv("PATH");
	data->path = ft_strdup(data->path);
	data->p = ft_split(data->path, ':');
	free(data->path);
	i = 0;
	while (data->p[i])
	{
		str = ft_strjoin(data->p[i++], data->matrix[0]);
		if (access(str, X_OK) == 0)
		{
			free_all(data->p);
			return (str);
		}
		free(str);
	}
	free_all(data->p);
	return (NULL);
}
