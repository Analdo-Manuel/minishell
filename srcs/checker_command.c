/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:33:37 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/29 08:43:38 by marccarv         ###   ########.fr       */
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
		
		if (data->control_padrao == 2)
		{
			if (ft_strcmp(data->matrix[0], "cat") == 0 || ft_strcmp(data->matrix[0], "wc") == 0)
			{
				dup2(data->stdout_padrao, STDOUT_FILENO);
				data->fd = open(".temp", O_RDONLY);
				dup2(data->fd, STDIN_FILENO);
			}
			unlink(".temp");
			close(data->fd);
		}
		data->pid = fork();
		if (data->pid == 0)
		{
			signal(SIGINT, handler_process);
			signal(SIGQUIT, handler_process);
			if (execve(data->path_main, data->matrix, data->envp) == -1)
			{
    			perror("execve");
   				exit(EXIT_FAILURE);
			}
		}
		else if (data->pid > 0)
		{
			signal(SIGINT, SIG_IGN);
			waitpid(data->pid, &data->status, 0);
			if (WIFEXITED(data->status))
            	g_global = WEXITSTATUS(data->status);
			else if (WTERMSIG(data->status) == 3)
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
		printf("%s: Command not found.\n", data->matrix[0]);
		free_all(data->matrix);
	}
}

static
		void	init_valuer(t_data *data)
{
	data->path_main = NULL;
	data->matrix = NULL;
	data->fd = -1;
	data->control_padrao = 0;
}

void	loop_prompt(t_data *data, t_valuer *val)
{
	char	**str;
	int		i;

	i = 0;
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler_sign);
		realine_prompt(data);
		if ( data->command == NULL)
		{
			free_total(data);
			exit (0);
		}
		if (verefy_quotes(data->command) == 0)
		{
			if (verefiy_redirect(data->command) != 3 && verefiy_pipe(data->command) != 3)
			{
				if (verefiy_pipe(data->command) == 1)
				{
					data->f_pipe = true;
					val->f_pipe = true;
					data->stdout_padrao = dup(STDOUT_FILENO);
					data->stdin_padrao = dup(STDIN_FILENO);
					pipe(data->fdpipe);
					str = ft_split_pipe(data->command, '|');
					i = 0;
					while (str[i])
					{
						printf("Com pipe\n");
						if (str[i + 1] != NULL)
							dup2(data->fdpipe[1], STDOUT_FILENO);
						else
							dup2(data->stdout_padrao, STDOUT_FILENO);
						if (i > 0)
							dup2(data->fdpipe[0], STDIN_FILENO);
						if (verefiy_redirect(str[i]) != 0)
							redirections_op(data, val, str[i]);
						else
							data->matrix = ft_split_one(val, str[i]);
						if (data->select)
						{
							if (checker_builtins(data))
							{
								data->path_main = find_executable(data);
								print_prompt(data);
								if (data->path_main != NULL)
									free(data->path_main);
							}
							else
							{
								g_global = 0;
								free_all(data->matrix);
							}
						}
						else
						{
							data->select = true;
							free_all(data->matrix);
						}
						data->f_pipe = false;
						val->f_pipe = false;
						if (i > 0)
							close(data->fdpipe[0]);
						if (str[i + 1] != NULL)
							close(data->fdpipe[1]);
						dup2(data->stdout_padrao, STDOUT_FILENO);
						dup2(data->stdin_padrao, STDIN_FILENO);
						i++;
					}
				}
				else
				{
					printf("Sem pipe\n");
					if (verefiy_redirect(data->command) != 0)
						redirections_op(data, val, NULL);
					else
						data->matrix = ft_split_one(val, data->command);
					if (data->select)
					{
						if (checker_builtins(data))
						{
							data->path_main = find_executable(data);
							print_prompt(data);
							if (data->path_main != NULL)
								free(data->path_main);
						}
						else
						{
							g_global = 0;
							free_all(data->matrix);
						}
					}
					else
					{
						data->select = true;
						free_all(data->matrix);
					}
				}
			}
		}
		if (data->fd >= 0 && data->control_padrao == 1)
		{
			dup2(data->stdout_padrao, STDOUT_FILENO);
			close(data->stdout_padrao);
		}
		if (data->fd >= 0 && data->control_padrao == 2)
		{
			dup2(data->stdin_padrao, STDIN_FILENO);
			close(data->stdin_padrao);
		}
		init_valuer(data);
	}
}
