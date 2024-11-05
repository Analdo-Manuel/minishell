/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:55:15 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/01 20:53:54 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	echo_pwd_env(t_data *data)
{
	if (ft_strcmp(data->matrix[0], "echo") == 0)
	{
		if (data->matrix[1] != NULL)
			builtins_echo(data);
		return (true);
	}
	else if (ft_strcmp(data->matrix[0], "pwd") == 0)
	{
		builtins_pwd(data);
		return (true);
	}
	else if (ft_strcmp(data->matrix[0], "env") == 0)
	{
		builtins_env(data);
		return (true);
	}
	else if (ft_strcmp(data->matrix[0], "cd") == 0)
	{
		builtins_cd_conf(data);
		return (true);
	}
	return (false);
}

static bool	unset_export(t_data *data)
{
	size_t	i;

	i = 1;
	if (ft_strcmp(data->matrix[0], "unset") == 0)
	{
		if (data->matrix[1] != NULL)
		{
			while (data->matrix[i])
				data->envp = builtins_unset(data->envp, data->matrix[i++]);
		}
		return (true);
	}
	if (ft_strcmp(data->matrix[0], "export") == 0)
	{
		if (data->matrix[1] != NULL)
		{
			data->envp = builtins_export(data->envp, data->matrix[1]);
		}
		return (true);
	}
	return (false);
}

bool	checker_builtins(t_data *data)
{
	if (echo_pwd_env(data))
	{
		free_all(data->matrix);
		return (false);
	}
	if (unset_export(data))
	{
		free_all(data->matrix);
		return (false);
	}
	return (true);
}
