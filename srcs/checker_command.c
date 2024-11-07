/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:33:37 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/07 16:14:26 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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

static
		void	print_prompt(t_data *data)
{
	if (data->path_main)
	{
		if (fork() == 0)
			execve(data->path_main, data->matrix, data->envp);
		wait(0);
	}
	else
		printf("Command '%s' not found.\n", data->command);
}

static
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

void	loop_prompt(t_data *data, t_valuer *val)
{
	while (true)
	{
		realine_prompt(data);
		if (verefy_quotes(data->command) == 0)
		{
			data->matrix = ft_split_one(val, data->command);
			if (checker_builtins(data))
			{
				data->path_main = find_executable(data);
				if (ft_strcmp(data->command, "exit") == 0)
					break ;
				print_prompt(data);
			}
		}
	}
}
