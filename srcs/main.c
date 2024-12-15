/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:28:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/12/15 00:16:24 by marccarv         ###   ########.fr       */
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
	data->p = NULL;
	data->str = NULL;
	data->home = NULL;
	data->path = NULL;
	data->envp = NULL;
	data->matrix = NULL;
	data->command = NULL;
	data->path_main = NULL;
	g_global = 0;
	data->fd = -1;
	data->status = 0;
	data->control_padrao = 000;
	data->select = true;
	data->f_pipe = false;
	data->valuer_aux = false;
	data->block_error = false;
	data->signal_erro = false;
}

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_valuer	val;

	(void)ac;
	(void)av;
	inicializador(&data);
	//clear_screen(envp);
	data.envp = envp_copy(envp);
	data.export = envp_copy(envp);
	sort_params(data.export);
	data.export = export_define(data.export);
	loop_prompt(&data, &val);
	return (0);
}
