/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:55:15 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/22 09:37:48 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void builtins_exit(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("exit\n");
	if (data->matrix[2] != NULL)
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
				printf("bash: exit: %s: numeric argument required\n", data->matrix[1]);
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
	if (ft_strcmp(data->matrix[0], "exit") == 0)
	{
		builtins_exit(data);
	}
	return (false);
}

void	unset_export_unset(t_data *data, t_valuer val)
{
	size_t		i;

	i = 0;
	if (data->matrix[1] != NULL)
	{
		while (data->matrix[i])
		{
			val.signal = false;
			data->export = builtins_unset(data->export, data->matrix[i], val);
			val.signal = true;
			data->envp = builtins_unset(data->envp, data->matrix[i++], val);
		}
	}
}

static
		void	unset_export_export(t_data *data)
{
	size_t		j;

	j = 0;
	if (data->matrix[1] != NULL)
	{
		if (ft_isdigit(data->matrix[1][0]))
		{
			g_global = 1;
			printf("bash: export: '%s': not a valid identifier\n", data->matrix[1]);
		}
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
}

static bool	unset_export_cd(t_data *data)
{
	t_valuer	val;

	if (ft_strcmp(data->matrix[0], "unset") == 0)
	{
		unset_export_unset(data, val);
		return (true);
	}
	if (ft_strcmp(data->matrix[0], "export") == 0)
	{
		unset_export_export(data);
		return (true);
	}
	if (ft_strcmp(data->matrix[0], "cd") == 0)
	{
		builtins_cd_conf(data);
		free(data->home);
		return (true);
	}
	return (false);
}

bool	checker_builtins(t_data *data)
{
	if (data->matrix == NULL || data->matrix[0] == NULL)
		return (false);
	else if (echo_pwd_env(data))
	{
		free_all(data->matrix);
		return (false);
	}
	else if (unset_export_cd(data))
	{
		free_all(data->matrix);
		return (false);
	}
	return (true);
}
