/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analdo <analdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:55:15 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/06 23:46:12 by analdo           ###   ########.fr       */
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
	if (ft_strcmp(data->matrix[0], "pwd") == 0)
	{
		builtins_pwd(data);
		return (true);
	}
	if (ft_strcmp(data->matrix[0], "env") == 0)
	{
		builtins_env(data);
		return (true);
	}
	return (false);
}

static bool	unset_export_cd(t_data *data)
{
	t_valuer	val;
	size_t		i;
	size_t		j;

	i = 1;
	j = 0;
	if (ft_strcmp(data->matrix[0], "unset") == 0)
	{
		if (data->matrix[1] != NULL)
		{
			while (data->matrix[i])
				data->envp = builtins_unset(data->envp, data->matrix[i++], val);
		}
		return (true);
	}
	if (ft_strcmp(data->matrix[0], "export") == 0)
	{
		if (data->matrix[1] != NULL)
		{	
			if (ft_isdigit(data->matrix[1][0]))
				printf("bash: export: '%s': not a valid identifier\n", data->matrix[1]);
			else
			{
				data->export = builtins_export_define(data->export, data->matrix[1]);
				sort_params(data->export);
				data->envp = builtins_export(data->envp, data->matrix[1]);
			}
		}
		else
		{
			while (data->export[j])
				printf("%s\n", data->export[j++]);
		}
		return (true);
	}
	if (ft_strcmp(data->matrix[0], "cd") == 0)
	{
		builtins_cd_conf(data);
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
	if (unset_export_cd(data))
	{
		free_all(data->matrix);
		return (false);
	}
	return (true);
}
