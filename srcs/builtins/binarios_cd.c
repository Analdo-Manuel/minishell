/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:12:00 by marccarv          #+#    #+#             */
/*   Updated: 2024/12/13 16:27:53 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strcmp_cd(const char *s1, const char *s2)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = -1;
	while (s1[++k] && s1[k] != '=')
		;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		if (s1[i] == s2[i])
			k--;
		i++;
	}
	if (s2[i] == '=' && k == 0)
		return (k);
	return (1);
}

void	cd_home_copy(char **envp, char *home, t_data *data)
{
	t_valuer	val;

	val.j = 0;
	val.k = 0;
	while (envp[val.j])
	{
		val.i = -1;
		if (ft_strcmp_cd(home, envp[val.j]) == 0)
		{
			while (envp[val.j][++val.i])
				;
			data->home = (char *)malloc(sizeof(char) * (val.i + 1));
			val.i = -1;
			while (envp[val.j][++val.i] != '=')
				;
			val.i++;
			while (envp[val.j][val.i])
				data->home[val.k++] = envp[val.j][val.i++];
			data->home[val.k] = '\0';
		}
		val.j++;
	}
}

static void	builtins_cd(t_data *data, char *str)
{
	if (chdir(str) == 0)
		return ;
	else
	{
		if (data->f_pipe == true)
		{
			dup2(data->stdout_padrao, STDOUT_FILENO);
			close(data->stdout_padrao);
		}
		g_global = 1;
		printf("bash: cd: %s: No such file or directory\n", str);
	}
	return ;
}

void	builtins_cd_conf(t_data *data)
{
	cd_home_copy(data->envp, "HOME", data);
	if (data->matrix[1] == NULL)
	{
		if (data->home == NULL)
		{
			if (data->f_pipe == true)
			{
				dup2(data->stdout_padrao, STDOUT_FILENO);
				close(data->stdout_padrao);
			}
			g_global = 1;
			printf("bash: cd: HOME not set\n");
			return ;
		}
		builtins_cd(data, data->home);
	}
	else
	{
		if (ft_strcmp(data->matrix[1], "~") == 0)
		{
			if (data->matrix[2] != NULL)
			{
				if (data->f_pipe == true)
				{
					dup2(data->stdout_padrao, STDOUT_FILENO);
					close(data->stdout_padrao);
				}
				g_global = 1;
				printf("bash: cd: too many arguments\n");
			}
			else	
				builtins_cd(data, getenv("HOME"));
		}
		else
			builtins_cd(data, data->matrix[1]);
	}
}
