/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarios_treen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:45:52 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/01 20:56:12 by almanuel         ###   ########.fr       */
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

char	**builtins_export(char **src, char *export)
{
	char	**str;
	int		i;
	int		j;
	bool	s = false;

	i = -1;
	j = 0;
	while (src[++i])
		;
	str = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (src[j])
	{
		i = -1;
		if (ft_strcmp_export(export, src[j]) != 0)
		{
			while (src[j][++i])
				;
			str[j] = (char *)malloc(sizeof(char) * (i + 1));
			i = -1;
			while (src[j][++i])
				str[j][i] = src[j][i];
		}
		else
		{
			i = -1;
			while (export[++i])
				;
			str[j] = (char *)malloc(sizeof(char) * (i + 1));
			i = -1;
			while (export[++i])
				str[j][i] = export[i];
			s = true;
		}
		str[j][i] = '\0';
		j++;
	}
	if (s == false && verefy_export(export) == 0)
	{
		i = -1;
		while (export[++i])
			;
		str[j] = (char *)malloc(sizeof(char) * (i + 1));
		i = -1;
		while (export[++i])
			str[j][i] = export[i];
		str[j][i] = '\0';
		j++;
	}
	str[j] = NULL;
	return (str);
}
