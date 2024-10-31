/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analdo <analdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:55:15 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/31 01:16:41 by analdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtins_echo(t_data *data)
{
	size_t	i;

	i = 1;
	if (ft_strcmp(data->matrix[1], "-n") != 0)
	{
		while (data->matrix[i])
		{
			printf("%s", data->matrix[i++]);
			if (data->matrix[i])
				printf(" ");
		}
		printf("\n");
	}
	else
	{
		while (ft_strcmp(data->matrix[i], "-n") == 0)
			i++;
		while (data->matrix[i])
		{
			printf("%s", data->matrix[i++]);
			if (data->matrix[i])
				printf(" ");
		}
	}
}

void	builtins_pwd(t_data *data)
{
	char	*str;

	if (data->matrix[1] != NULL)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	str = getcwd(NULL, 0);
	if (str == NULL)
	{
		printf("error getcwd\n");
		return ;
	}
	printf("%s\n", str);
	free(str);
	return ;
}

void	builtins_env(char *str, char **envp)
{
	size_t	i;

	i = 0;
	if (str != NULL)
	{
		printf("env with no options or arguments\n");
		return ;
	}
	while (envp[i] != NULL)
		printf("%s\n", envp[i++]);
	return ;
}

bool	checker_builtins(t_data *data, char **envp)
{
	bool	s;

	s = false;
	if (ft_strcmp(data->matrix[0], "echo") == 0)
	{
		if (data->matrix[1] != NULL)
			builtins_echo(data);
		s = true;
	}
	else if (ft_strcmp(data->matrix[0], "pwd") == 0)
	{
		builtins_pwd(data);
		s = true;
	}
	else if (ft_strcmp(data->matrix[0], "env") == 0)
	{
		builtins_env(data->matrix[1], envp);
		s = true;
	}
	
	if (s == true)
	{
		free_all(data->matrix);
		return (false);
	}
	return (true);
}
