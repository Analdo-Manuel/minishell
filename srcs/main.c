/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analdo <analdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:28:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/06 23:54:28 by analdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	main(int ac, char **av, char **envp)
{
	t_data		data;
	t_valuer	val;

	(void)ac;
	(void)av;
	clear_screen(envp);
	data.envp = envp_copy(envp);
	data.export = envp_copy(envp);
	sort_params(data.export);
	data.export = export_define(data.export);
	loop_prompt(&data, &val);
	free_total(&data);
	return (0);
}
