/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_five.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:00:54 by almanuel          #+#    #+#             */
/*   Updated: 2024/12/14 17:08:45 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_define_2(char **export, t_valuer *val)
{
	while (export[val->i][val->j])
	{
		if ((export[val->i][val->j] == '='))
		{
			val->p[val->i] = str_alloc(val->p[val->i],
					export[val->i][val->j++]);
			val->p[val->i] = str_alloc(val->p[val->i], '"');
		}
		else
			val->p[val->i] = str_alloc(val->p[val->i],
					export[val->i][val->j++]);
	}
}

char	**export_define(char **export)
{
	t_valuer	val;

	val.i = 0;
	while (export[val.i++])
		;
	val.p = (char **)malloc(sizeof(char *) * (val.i + 1));
	val.i = 0;
	while (export[val.i])
	{
		val.p[val.i] = ft_strdup("declare -x ");
		val.j = 0;
		export_define_2(export, &val);
		val.p[val.i] = str_alloc(val.p[val.i], '"');
		val.i++;
	}
	val.p[val.i] = NULL;
	free_all(export);
	return (val.p);
}
