/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:05:15 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/18 19:31:36 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins_echo(t_data *data)
{
	size_t	i;

	i = 1;
	if (data->matrix[i][0] != '-' && data->matrix[i][1] != 'n')
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
		while (data->matrix[i][0] == '-' && data->matrix[i][1] == 'n')
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

void	builtins_env(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->matrix[1] != NULL)
	{
		printf("env with no options or arguments\n");
		return ;
	}
	while (data->envp[i] != NULL)
		printf("%s\n", data->envp[i++]);
	return ;
}
