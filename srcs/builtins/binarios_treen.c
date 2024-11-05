/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_treen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:45:52 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/05 15:15:50 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strcmp_export(const char *s1, const char *s2)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = -1;
	while (s1[++k] && s1[k] != '=')
		;
	while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=' && (s1[i] == s2[i]))
	{
		if (s1[i] == s2[i])
		{
			printf("k == %ld\n", k);
			printf("export: %c || env: %c\n", s1[i], s2[i]);
			k--;
		}
		i++;
	}
	if (s2[i] == '=' && k == 0 && s1[i] == '=' && s1[0] != '=')
		return (k);
	return (1);
}

static int	verefy_export(const char *s1)
{
	size_t	k;

	k = -1;
	while (s1[++k] && s1[k] != '=')
		;
	if (s1[k] == '=' && s1[0] != '=')
		return (0);
	return (1);
}

static
		void	loop_builtins_export(t_valuer *val, char **src, char *export)
{
	val->i = -1;
	if (ft_strcmp_export(export, src[val->j]) != 0)
	{
		while (src[val->j][++val->i])
			;
		val->p[val->j] = (char *)malloc(sizeof(char) * (val->i + 1));
		val->i = -1;
		while (src[val->j][++val->i])
			val->p[val->j][val->i] = src[val->j][val->i];
	}
	else
	{
		val->i = -1;
		while (export[++val->i])
			;
		val->p[val->j] = (char *)malloc(sizeof(char) * (val->i + 1));
		val->i = -1;
		while (export[++val->i])
			val->p[val->j][val->i] = export[val->i];
		val->signal = true;
	}
	val->p[val->j][val->i] = '\0';
	val->j++;
}	

char	**builtins_export(char **src, char *export)
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
	if (val.signal == false && verefy_export(export) == 0)
	{
		val.i = -1;
		while (export[++val.i])
			;
		val.p[val.j] = (char *)malloc(sizeof(char) * (val.i + 1));
		val.i = -1;
		while (export[++val.i])
			val.p[val.j][val.i] = export[val.i];
		val.p[val.j][val.i] = '\0';
		val.j++;
	}
	val.p[val.j] = NULL;
	return (val.p);
}
