/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:33:37 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/15 12:34:33 by almanuel         ###   ########.fr       */
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
		char	*find_executable(t_data *data)
{
	char	*str;
	size_t	i;

	if (access(data->matrix[0], X_OK) == 0)
		return (data->matrix[0]);
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

void	handler_process(int sig)
{
	if (sig == SIGINT)
		exit (130);
	if (sig == SIGQUIT)
		exit (131);
	return ;
}

void	handler_sign(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		global = 130;
	}
}

static
		void	print_prompt(t_data *data)
{
	if (data->path_main)
	{
		data->pid = fork();
		if (data->pid == 0)
		{
			signal(SIGINT, handler_process);
			signal(SIGQUIT, handler_process);
			execve(data->path_main, data->matrix, data->envp);
		}
		else if (data->pid > 0)
		{
			signal(SIGINT, SIG_IGN);
			waitpid(data->pid, &data->status, 0);
			if (WTERMSIG(data->status) == 3)
			{
				global = 131;
				printf("Quit (core dumped)\n");
			}
			else if (WTERMSIG(data->status) == 2)
				global = 130;
			free_all(data->matrix);
		}
	}
	else
		printf("Command '%s' not found.\n", data->command);
}

static
		void	init_valuer(t_data *data)
{
	data->path_main = NULL;
	data->matrix = NULL;
	
}


void	loop_prompt(t_data *data, t_valuer *val)
{
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler_sign);
		realine_prompt(data);
		if (ft_strcmp(data->command, "exit") == 0 || data->command == NULL)
			break ;
		if (verefy_quotes(data->command) == 0)
		{
			data->matrix = ft_split_one(val, data->command);
			if (checker_builtins(data))
			{
				data->path_main = find_executable(data);
				print_prompt(data);
				free(data->path_main);
			}
			else
				global = 0;
		}
		init_valuer(data);
	}
}
