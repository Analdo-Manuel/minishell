/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:55:51 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/18 10:41:59 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_command(t_data *data)
{
	if (!ft_strcmp(data->matrix, "echo") || !ft_strcmp(data->matrix, "unset") \
		|| !ft_strcmp(data->matrix, "export") || !ft_strcmp(data->matrix, "env") \
		|| !ft_strcmp(data->matrix, "cd") || !ft_strcmp(data->matrix, "pwd") || !find_executable(data))
		return (true);
	return (false);
}

void	redirections_op(t_data *data, t_valuer *val1, char *str)
{
	t_valuer	val;
	char		*name;
	char		c[3];
	
	val.str = (char *) malloc(sizeof(char) * 4086);
	val.i = 0;
	val.j = 0;
	while (*str)
	{
		if (*str == '>' || *str == '<')
		{
			while (*str == '>')
				c[val.j++] = *str;
			c[val.j] = '\0';
			while (*str == 32)
				*str++;
			name = (char *) malloc(sizeof(char) * 4086);
			val.j = 0;
			while (*str && *str != 32)
				name[val.j++] = *str++;
		}
		if (*str == 34)
		{
			while (*str != 34)
				val.str[val.i++] = *str++;
		}
		if (*str == 39)
		{
			while (*str != 39)
				val.str[val.i++] = *str++;
		}
	}
	data->matrix = ft_split_one(val1, val.str);
	free(val.str);
	for (int i = 0; data->matrix[i] ; i++)
		printf("%s", data->matrix[i]);
	printf("\n");
	/*
	if (check_command(data))
	{
		
	}
	*/
}
