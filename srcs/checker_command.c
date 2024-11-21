/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:33:37 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/21 16:30:51 by marccarv         ###   ########.fr       */
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

char	*find_executable(t_data *data)
{
	char	*str;
	size_t	i;

	if (data->matrix == NULL || data->matrix[0] == NULL)
		return (NULL);
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
	{
		printf("\n");
		exit (130);
	}
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
		g_global = 130;
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
				g_global = 131;
				printf("Quit (core dumped)\n");
			}
			else if (WTERMSIG(data->status) == 2)
			{
				if (data->fd >= 0)
				{
					dup2(data->stdout_padrao, STDOUT_FILENO);
					close(data->stdout_padrao);
				}
				data->fd = -1;
				printf("\n");
				g_global = 130;
			}
			free_all(data->matrix);
		}
	}
	else
	{	
		g_global = 127;
		printf("Command '%s' not found.\n", data->matrix[0]);
		free_all(data->matrix);
	}
}

static
		void	init_valuer(t_data *data)
{
	data->path_main = NULL;
	data->matrix = NULL;
}

void	loop_prompt(t_data *data, t_valuer *val)
{
	int		i = 0;
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler_sign);
		realine_prompt(data);
		if (ft_strcmp(data->command, "exit") == 0 || data->command == NULL)
		{
			break ;
		}
		if (verefy_quotes(data->command) == 0)
		{
			if (verefiy_redirect(data->command) != 3)
			{
				if (verefiy_redirect(data->command) != 0)
					redirections_op(data, val);
				else
					data->matrix = ft_split_one(val, data->command);
				if (data->select)
				{
					if (checker_builtins(data))
					{
						data->path_main = find_executable(data);
						print_prompt(data);
						free(data->path_main);
					}
					else
						g_global = 0;
				}
				else
				{
					data->select = true;
					free_all(data->matrix);
				}
			}
		}
		if (data->fd >= 0)
		{
			dup2(data->stdout_padrao, STDOUT_FILENO);
			close(data->stdout_padrao);
		}
		init_valuer(data);
	}
}
