/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:33:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/12/14 17:37:51 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins_exit(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("exit\n");
	if (data->matrix[0] == NULL || data->matrix[1] == NULL
		|| data->matrix[2] != NULL)
	{
		data->exit = 0;
		free_total(data);
		exit(data->exit);
	}
	else if (data->matrix[2] != NULL)
	{
		printf("bash: exit: too many arguments\n");
		data->exit = 1;
		j = 1;
	}
	else if (data->matrix[1] != NULL)
	{
		while (data->matrix[1][i] != '\0')
		{
			if (ft_isdigit(data->matrix[1][i]) == 0)
			{
				if (data->f_pipe == true)
				{
					dup2(data->stdout_padrao, STDOUT_FILENO);
					close(data->stdout_padrao);
				}
				g_global = 1;
				printf("bash: exit: %s: numeric argument required\n",
					data->matrix[1]);
				data->exit = 2;
				j = 1;
				break ;
			}
			i++;
		}
	}
	if (data->matrix[1] != NULL && j == 0)
		data->exit = ft_atoi(data->matrix[1]);
	else if (j == 0)
		data->exit = 0;
	free_total(data);
	exit(data->exit);
}