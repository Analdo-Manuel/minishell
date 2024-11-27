/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:55:51 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/27 15:18:50 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
		bool	check_command(t_data *data)
{
	char	*str;

	str = find_executable(data);
	if (data->matrix == NULL || data->matrix[0] == NULL)
		return (true);
	if (!ft_strcmp(data->matrix[0], "echo") 		\
		|| !ft_strcmp(data->matrix[0], "unset") 	\
		|| !ft_strcmp(data->matrix[0], "export") 	\
		|| !ft_strcmp(data->matrix[0], "env") 		\
		|| !ft_strcmp(data->matrix[0], "cd") 		\
		|| !ft_strcmp(data->matrix[0], "pwd") 		\
		|| str )
	{
		if (str)
			free(str);
		return (true);
	}
	return (false);
}

static
		char	*control(char *src, t_valuer *val)
{
	char	*str;
	size_t	i;

	i = 0; 
	str = (char *) malloc(sizeof(char) * 3);
	while (src[val->i] == '>' || src[val->i] == '<')
		str[i++] = src[val->i++];
	str[i] = '\0';
	while (src[val->i] && (src[val->i] == ' ' || src[val->i] == '\t'))
		val->i++;
	return (str);
}

void	exec_filho(t_data *data, char *name)	
{
	t_valuer	val;
	char	*str;

	signal(SIGINT, handler_process);
	signal(SIGQUIT, handler_process);
	data->fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (true)
	{
		val.i = 0;
		val.j = 0;
		str = readline("> ");
		if (str != NULL)
		{
			if (ft_strcmp(str, name) == 0)
			{
				if (str)
					free(str);
				break;
			}
			val.str = (char *) malloc(sizeof(char) * 1);
			val.str[0] = '\0';
			while (str[val.i])
			{
				if (str[val.i] == '$')
				{
					val.i++;
					val.str = ft_strjoin_des(val.str, expand_var_heredoc(str));
					while (str[val.i] && str[val.i] != 32)
						val.i++;
				}
				else
					val.str = str_alloc(val.str, str[val.i++]);
			}
			write(data->fd, val.str, ft_strlen(val.str));
			write(data->fd, "\n", 1);
			free(str);
			free(val.str);
		}
	}
	close(data->fd);
	exit(0);
}

void	create_file(t_data *data, t_valuer *val, char *name, char *index_r)
{
	if (ft_strcmp(index_r, ">") == 0)
	{
		data->fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(data->fd, STDOUT_FILENO);
		data->control_padrao = 1;
	}
	else if (ft_strcmp(index_r, ">>") == 0)
	{
		data->fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(data->fd, STDOUT_FILENO);
		data->control_padrao = 1;
	}
	else if (ft_strcmp(index_r, "<") == 0)
	{
		data->fd = open(name, O_RDONLY, 0644);
		if (data->fd == -1)
		{
			g_global = 1;
			printf("bash: %s: No such file or directory\n", name);
			data->select = false;
		}
		else
		{
			while (data->command[val->i] == ' ' || data->command[val->i] == '\t')
				 val->i++;
			if (data->command[val->i] == '\0')
				val->str = ft_strjoin_des(val->str, name);
		}
	}
	else if (ft_strcmp(index_r, "<<") == 0)
	{
		if (fork() == 0)
			exec_filho(data, name);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(-1, &data->status, 0);
		g_global = WEXITSTATUS(data->status);
		data->control_padrao = 2;
	}
	if (data->fd >= 0)
		close(data->fd);
}

void	add_valuer(t_valuer *val, char *str)
{
	if (str[val->i] == '\0' || str[val->i] == '>')
		return ;
	if (str[val->i] == 34)
	{
		val->str = str_alloc(val->str, str[val->i++]);
		while (str[val->i] != 34)
			val->str = str_alloc(val->str, str[val->i++]);
		val->str = str_alloc(val->str, str[val->i++]);
	}
	if (str[val->i] == 39)
	{
		val->str = str_alloc(val->str, str[val->i++]);
		while (str[val->i] != 39)
			val->str = str_alloc(val->str, str[val->i++]);
		val->str = str_alloc(val->str, str[val->i++]);
	}
	if (str[val->i])
		val->str = str_alloc(val->str, str[val->i++]);
}

void	redirections_op(t_data *data, t_valuer *val1, char *str)
{
	t_valuer	val;
	char		*name;
	char		*c;

	if (data->f_pipe == false)
	{
		data->stdout_padrao = dup(STDOUT_FILENO);
		data->stdin_padrao = dup(STDIN_FILENO);
	}
	if (str != NULL)
		data->command = str;
	val.str = (char *) malloc(sizeof(char) * 1000);
	ft_memset(val.str, 0, 1000);
	val.i = 0;
	while (data->command[val.i] && (data->command[val.i] == ' ' || data->command[val.i] == '\t'))
		val.i++;
	while (data->command[val.i])
	{
		if (data->command[val.i] == '>' || data->command[val.i] == '<')
		{	
			c = control(data->command, &val);
			name = (char *) malloc(sizeof(char) * 4086);
			val.j = 0;
			while (data->command[val.i] && data->command[val.i] != 32 \
			&& (data->command[val.i] != '>' || data->command[val.i] != '<'))
				name[val.j++] = data->command[val.i++];
			name[val.j] = '\0';
			while (data->command[val.i] && (data->command[val.i] == ' ' || data->command[val.i] == '\t'))
				val.i++;
			if (val.str)
			{
				data->matrix = ft_split_one(val1, val.str);
				if (check_command(data) == false)
				{
					g_global = 127;
					printf("Command '%s' not found.\n", data->matrix[0]);
					if (name)
						free(name);
					if (c)
						free(c);
					free_all(data->matrix);
					return ;
				}
				else
				{
					create_file(data, &val, name, c);
					free(name);
					free(c);
					free_all(data->matrix);
				}
			}	
		}
		else
			add_valuer(&val, data->command);
	}
	data->matrix = ft_split_one(val1, val.str);
	if (val.str != NULL)
		free(val.str);
	return ;
}
