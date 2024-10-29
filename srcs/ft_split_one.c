/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:19:35 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/29 18:25:38 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quotes_double(t_valuer *val, char *str)
{
	val->p[val->j][val->k] = '\0';
	val->i++;
	while (str[val->i] && str[val->i] != 34)
	{
		if (str[val->i] == '$' && str[val->i + 1] != 34)
		{
			val->i++;
			val->p[val->j] = expand_variable(val->p[val->j], str, val);
		}
		else if (str[val->i] == '$' && str[val->i + 1] == 34)
		{
			val->p[val->j] = str_alloc(val->p[val->j], str[val->i]);
			val->i++;
			break ;
		}
		if (str[val->i] && str[val->i] != 34 && str[val->i] != '$')
			val->p[val->j] = str_alloc(val->p[val->j], str[val->i++]);
		val->signal = true;
	}
	if (str[val->i] == 34)
		val->i++;
}

void	selection_option(t_valuer *val, char *str)
{
	if (str[val->i] == 34)
	{
		quotes_double(val, str);
		return ;
	}
	if (str[val->i] == '$' && str[val->i + 1] != 34)
	{
		val->i++;
		val->p[val->j] = expand_variable(val->p[val->j], str, val);
		val->signal = true;
		return ;
	}
	val->p[val->j][val->k++] = str[val->i++];
}

char	**ft_split_one(t_valuer *val, char *str)
{
	val->p = (char **) malloc(sizeof(char *) * 4096);
	val->i = 0;
	val->j = 0;
	while (str[val->i])
	{
		val->signal = false;
		while (str[val->i] == ' ' || str[val->i] == '\t' || str[val->i] == '\n')
			val->i++;
		val->p[val->j] = (char *) malloc(sizeof(char) * 8096);
		ft_memset(val->p[val->j], 0, 8096);
		val->k = 0;
		while (str[val->i] && str[val->i] != ' ' && str[val->i] != '\t')
			selection_option(val, str);
		if (val->signal == false)
			val->p[val->j][val->k] = '\0';
		val->j++;
	}
	val->p[val->j] = NULL;
	return (val->p);
}
