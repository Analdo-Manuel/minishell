/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:28:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/05 14:18:28 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	**envp_copy(char **envp)
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
	loop_prompt(&data, &val);
	free_total(&data);
	return (0);
}
