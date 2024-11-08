/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:36:44 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/08 16:42:11 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
		int	ft_strcmp_unset(const char *s1, const char *s2)
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

static
		int	ft_strcmp_unset_export(const char *s1, const char *s2)
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

char	**builtins_unset(char **envp, char *clear, t_valuer val)
{
	val.i = -1;
	val.j = 0;
	val.k = 0;
	while (envp[++val.i])
		;
	val.p = (char **)malloc(sizeof(char *) * (val.i + 1));
	while (envp[val.j])
	{
		if (ft_strcmp_unset(clear, envp[val.j]) != 0)
		{
			val.i = -1;
			while (envp[val.j][++val.i])
				;
			val.p[val.k] = (char *)malloc(sizeof(char) * (val.i + 1));
			val.i = -1;
			while (envp[val.j][++val.i])
				val.p[val.k][val.i] = envp[val.j][val.i];
			val.p[val.k][val.i] = '\0';
			val.k++;
		}
		val.j++;
	}
	val.p[val.k] = NULL;
	free_all(envp);
	return (val.p);
}
