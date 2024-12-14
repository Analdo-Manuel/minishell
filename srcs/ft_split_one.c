/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:19:35 by almanuel          #+#    #+#             */
/*   Updated: 2024/12/14 21:22:25 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quotes_double(t_data *data, t_valuer *val, char *str)
{
	val->i++;
	while (str[val->i] && str[val->i] != ' ' && str[val->i] != '\t')
	{
		while (str[val->i] && str[val->i] != 34)
		{
			if (str[val->i + 1] && str[val->i] == '$' && str[val->i + 1] != 34 && str[val->i + 1] != 32)
			{
				val->i++;
				if (str[val->i] == '?')
				{
					val->p[val->j] = ft_strjoin_des1(val->p[val->j], \
					ft_itoa(g_global));
					val->i++;
				}
				val->p[val->j] = expand_variable(data, val->p[val->j], str, val);
//				while (str[val->i] == 32)
//					val->i++;
			}
			else if (str[val->i] == '$' && (str[val->i + 1] == 34 || str[val->i + 1] == 32))
			{
				val->p[val->j] = str_alloc(val->p[val->j], str[val->i]);
				val->i++;
			}
			if (str[val->i] && str[val->i] != 34 && str[val->i] != '$')
				val->p[val->j] = str_alloc(val->p[val->j], str[val->i++]);
			val->signal = true;
		}
		if (str[val->i] == 34)
		{
			val->i++;
			break ;
		}
	}
}

void	quotes_simple(t_valuer *val, char *str)
{
	val->i++;
	while (str[val->i])
	{
/*		if (str[val->i] == ' ' && str[val->i] != 9)
		{
			val->p[val->j] = str_alloc(val->p[val->j], str[val->i++]);
			while (str[val->i] == ' ')
				val->i++;
		}
*/
		if (str[val->i] == 39)
		{
			val->i++;
			break ;
		}
		else
			val->p[val->j] = str_alloc(val->p[val->j], str[val->i++]);
	}
}

void	selection_option(t_data *data, t_valuer *val, char *str)
{
	if (str[val->i] == 34)
		quotes_double(data, val, str);
	else if (str[val->i] == 39)
		quotes_simple(val, str);
	else if (str[val->i] == '$' && (str[val->i + 1] != 34 && str[val->i + 1] != 32 && str[val->i + 1] != '\0' && str[val->i + 1] != '.'))
	{
		val->i++;
		if (str[val->i] == '?')
		{
			val->p[val->j] = ft_strjoin_des1(val->p[val->j], ft_itoa(g_global));
			val->i++;
		}
		else
			val->p[val->j] = expand_variable(data, val->p[val->j], str, val);
		if (str[val->i] == 32)
			val->p[val->j] = str_alloc(val->p[val->j], str[val->i++]);
		while (str[val->i] == 32)
			val->i++;
	}
	else
		val->p[val->j] = str_alloc(val->p[val->j], str[val->i++]);
}

char	**ft_split_one(t_data *data, t_valuer *val, char *str)
{
	if (str == NULL)
		return (NULL);
	val->p = (char **) malloc(sizeof(char *) * 4096);
	val->i = 0;
	val->j = 0;
	while (str[val->i] == ' ' || str[val->i] == '\t' || str[val->i] == '\n' || str[val->i] == '"')
		val->i++;
	while (str[val->i])
	{
		val->p[val->j] = (char *) malloc(sizeof(char) * 8084);
		ft_memset(val->p[val->j], 0, 8084);
		while (str[val->i] && str[val->i] != ' ' && str[val->i] != '\t')
			selection_option(data, val, str);
		while (str[val->i] == ' ' || str[val->i] == '\t' || str[val->i] == '\n')
			val->i++;
		val->j++;
	}
	val->p[val->j] = NULL;
	return (val->p);
}
