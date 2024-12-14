/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:05:15 by almanuel          #+#    #+#             */
/*   Updated: 2024/12/14 17:15:20 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	checke_comand(char *str)
{
	size_t	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	builtins_echo(t_data *data)
{
	size_t	i;

	i = 1;
	if (data->matrix[i][0] == '-' && data->matrix[i][1] == 'n'
		&& checke_comand(data->matrix[i]))
	{
		i++;
		while (data->matrix[i])
		{
			printf("%s", data->matrix[i++]);
			if (data->matrix[i])
				printf(" ");
		}
	}
	else
	{
		while (data->matrix[i])
		{
			printf("%s", data->matrix[i++]);
			if (data->matrix[i])
				printf(" ");
		}
		printf("\n");
	}
}

static void	builtins_pwd_one(t_data *data)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str == NULL)
	{
		if (data->f_pipe == true)
		{
			dup2(data->stdout_padrao, STDOUT_FILENO);
			close(data->stdout_padrao);
		}
		g_global = 1;
		printf("error getcwd\n");
		return ;
	}
	printf("%s\n", str);
	free(str);
}

void	builtins_pwd(t_data *data)
{
	if (data->matrix[1] != NULL)
	{
		if (data->f_pipe == true)
		{
			dup2(data->stdout_padrao, STDOUT_FILENO);
			close(data->stdout_padrao);
		}
		g_global = 1;
		printf("pwd: too many arguments\n");
		return ;
	}
	builtins_pwd_one(data);
	return ;
}

void	builtins_env(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->matrix[1] != NULL)
	{
		if (data->f_pipe == true)
		{
			dup2(data->stdout_padrao, STDOUT_FILENO);
			close(data->stdout_padrao);
		}
		g_global = 1;
		printf("env with no options or arguments\n");
		return ;
	}
	while (data->envp[i] != NULL)
		printf("%s\n", data->envp[i++]);
	return ;
}
