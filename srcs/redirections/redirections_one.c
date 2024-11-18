/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:55:51 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/18 19:14:05 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
		bool	check_command(t_data *data)
{
	if (!ft_strcmp(data->matrix[0], "echo") || !ft_strcmp(data->matrix[0], "unset") \
		|| !ft_strcmp(data->matrix[0], "export") || !ft_strcmp(data->matrix[0], "env") \
		|| !ft_strcmp(data->matrix[0], "cd") || !ft_strcmp(data->matrix[0], "pwd") || !find_executable(data))
		return (true);
	return (false);
}

static
		char	*control(char **srca)
{
	char	*str;
	char	*src;
    size_t	i;
    size_t	count;

	i = 0;
	count = 0;
	src = *srca;
    while (src[count] == '>')
        count++;
    str = (char *) malloc(sizeof(char) * (count + 1));
    while (*src == '>')
        str[i++] = *(src++);
    str[i] = '\0';
    while (*src == ' ' || *src == '\t')
	{
        src++;
	}
	*srca = src;
    return (str);
}

void	create_file(t_data *data, char *name, char *index_r)
{
	if (ft_strcmp(index_r, ">") == 0)
	{
		data->fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(data->fd, STDOUT_FILENO);
	}
	if (ft_strcmp(index_r, ">>") == 0)
	{
		data->fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(data->fd, STDOUT_FILENO);
	}
	if (data->fd >= 0)
		close(data->fd);
}

bool	redirections_op(t_data *data, t_valuer *val1, char *str)
{
	t_valuer	val;
	char		*name;
	char		*c;

	data->stdout_padrao = dup(STDOUT_FILENO);
	val.str = (char *) malloc(sizeof(char) * 1000);
	ft_memset(val.str, 0, 1000);
	val.i = 0;
	while (*str)
	{
		if (*str == '>' || *str == '<')
		{	
			c = control(&str);
			name = (char *) malloc(sizeof(char) * 4086);
			val.j = 0;
			while (*str && *str != 32)
				name[val.j++] = *(str++);
			name[val.j] = '\0';
			while (*str == ' ' || *str == '\t')
				str++;
			if (val.str)
			{	
				data->matrix = ft_split_one(val1, val.str);
				if (check_command(data) == false)
				{
					printf("Command '%s' not found.\n", data->matrix[0]);
					free(name);
					free(c);
					free_all(data->matrix);
					return (false);
				}
				else
				{
					create_file(data, name, c);
					free(name);
					free(c);
				}
				free_all(data->matrix);
			}	
		}
		else if (*str == 34)
		{
			val.str = str_alloc(val.str, *(str++));
			while (*str != 34)
				val.str = str_alloc(val.str, *(str++));
			val.str = str_alloc(val.str, *(str++));
		}
		else if (*str == 39)
		{
			val.str = str_alloc(val.str, *(str++));
			while (*str != 39)
				val.str = str_alloc(val.str, *(str++));
			val.str = str_alloc(val.str, *(str++));
		}
		else if (*str)
			val.str = str_alloc(val.str, *(str++));
		//printf("%s\n", val.str);
	}
	data->matrix = ft_split_one(val1, val.str);
//	for (int i = 0; data->matrix[i]; i++)
//		printf("%s", data->matrix[i]);
	free(val.str);
	return (true);
}
