/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_four.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:06:09 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/14 08:43:43 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_define_2(char **export, t_valuer *val)
{
	while (export[val->i][val->j])
	{
		if ((export[val->i][val->j] == '='))
		{
			val->p[val->i] = str_alloc(val->p[val->i], export[val->i][val->j++]);
			val->p[val->i] = str_alloc(val->p[val->i], '"');
		}
		else
			val->p[val->i] = str_alloc(val->p[val->i], export[val->i][val->j++]);
	}
}

char	**export_define(char **export)
{
	t_valuer	val;

	val.i = 0;
	while (export[val.i++])
		;
	val.p = (char **) malloc(sizeof(char *) * (val.i + 1));
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

static int	ft_strcmp_export(const char *s1, const char *s2)
{
	t_valuer	val;

	val.i = -1;
	val.j = 0;
	val.k = 0;
	while (s2[++val.i] && s2[val.i] != 'x')
		;
	val.i += 2;
	while (s1[val.k] != '=' && s1[val.k])
	{
		val.k++;
	}
	while (s1[val.j] && s1[val.j] != '=' && s2[val.i] && s2[val.i] != '=' && (s1[val.j] == s2[val.i]))
	{
		if (s1[val.j] == s2[val.i])
			val.k--;
		val.i++;
		val.j++;
	}
	if (val.k == 0 && s1[0] != '=')
		return (val.k);
	return (1);
}
/*
static
		int	verefy_export(const char *s1)
{
	size_t	k;

	k = -1;
	while (s1[++k] && s1[k] != '=')
		;
	if (s1[k] == '=' && s1[0] != '=')
		return (0);
	return (1);
}
*/

void	loop_builtins_export_2(t_valuer *val, char *export)
{
	bool	signal;

	signal = true;
	val->p[val->j] = ft_strdup("declare -x ");
	val->i = -1;
	while (export[++val->i])
	{
		if (export[val->i] == '=')
		{
			val->p[val->j] = str_alloc(val->p[val->j], export[val->i]);
			val->p[val->j] = str_alloc(val->p[val->j], '"');
			signal = false;
		}
		else
			val->p[val->j] = str_alloc(val->p[val->j], export[val->i]);
	}
	if (signal != true)
		val->p[val->j] = str_alloc(val->p[val->j], '"');
	val->signal = true;
}

static
		void	loop_builtins_export(t_valuer *val, char **src, char *export)
{
	if (ft_strcmp_export(export, src[val->j]) != 0)
	{
		val->i = -1;
		while (src[val->j][++val->i])
			;
		val->p[val->j] = (char *)malloc(sizeof(char) * (val->i + 1));
		val->i = -1;
		while (src[val->j][++val->i])
			val->p[val->j][val->i] = src[val->j][val->i];
		val->p[val->j][val->i] = '\0';
	}
	else
	{
		loop_builtins_export_2(val, export);
	}
	val->j++;
}

void	builtins_export_define_2(t_valuer *val, char *export)
{
	bool	signal;

	signal = true;
	val->i = -1;
	while (export[++val->i])
		;
	val->p[val->j] = ft_strdup("declare -x ");
	val->i = -1;
	while (export[++val->i])
	{
		if (export[val->i] == '=')
		{
			val->p[val->j] = str_alloc(val->p[val->j], export[val->i]);
			val->p[val->j] = str_alloc(val->p[val->j], '"');
			signal = false;
		}
		else
			val->p[val->j] = str_alloc(val->p[val->j], export[val->i]);
	}
	if (signal != true)
		val->p[val->j] = str_alloc(val->p[val->j], '"');
	val->j++;
}

char	**builtins_export_define(char **src, char *export)
{
	t_valuer	val;

	val.i = -1;
	val.j = 0;
	val.signal = false;
	while (src[++val.i])
		;
	val.p = (char **)malloc(sizeof(char *) * (val.i + 2));
	while (src[val.j])
		loop_builtins_export(&val, src, export);
	if (val.signal == false)
	{
		builtins_export_define_2(&val, export);
	}
	val.p[val.j] = NULL;
	free_all(src);
	return (val.p);
}
