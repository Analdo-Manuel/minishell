/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:28:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/25 15:07:59 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_global;

static
		char	**envp_copy(char **envp)
{
	t_valuer	val;

	val.i = 0;
	while (envp[val.i])
		val.i++;
	val.p = (char **) malloc(sizeof(char *) * (val.i + 1));
	val.i = 0;
	val.j = 0;
	while (envp[val.i])
	{
		val.k = 0;
		while (envp[val.i][val.k])
			val.k++;
		val.p[val.j] = (char *) malloc(sizeof(char) * (val.k + 1));
		val.k = -1;
		while (envp[val.i][++val.k])
			val.p[val.j][val.k] = envp[val.i][val.k];
		val.p[val.j][val.k] = '\0';
		val.i++;
		val.j++;
	}
	val.p[val.j] = NULL;
	return (val.p);
}

void	inicializador(t_data *data)
{
	data->home = NULL;
	data->command = NULL;
	data->envp = NULL;
	data->matrix = NULL;
	data->p = NULL;
	data->path = NULL;
	data->path_main = NULL;
	data->select = true;
	data->status = 0;
	data->exit = 0;
	data->fd = -1;
	data->control_padrao = 000;
	g_global = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_valuer	val;

	(void)ac;
	(void)av;
	inicializador(&data);
	clear_screen(envp);
	data.envp = envp_copy(envp);
	data.export = envp_copy(envp);
	sort_params(data.export);
	data.export = export_define(data.export);
	loop_prompt(&data, &val);
	return (0);
}
