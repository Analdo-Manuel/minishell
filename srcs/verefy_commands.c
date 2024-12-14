/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verefy_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:59:22 by marccarv          #+#    #+#             */
/*   Updated: 2024/12/14 17:26:55 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	verefy_quotes_cont(char *str, t_valuer *val)
{
	while (str[val->i])
	{
		if (str[val->i] == 34)
		{
			if (val->j % 2 == 0)
				val->k++;
			val->i++;
			break ;
		}
		val->i++;
	}
}

static void	verefy_quotes_cont_2(char *str, t_valuer *val)
{
	while (str[val->i])
	{
		if (str[val->i] == 39)
		{
			if (val->k % 2 == 0)
				val->j++;
			val->i++;
			break ;
		}
		val->i++;
	}
}

void	loop_verefy_quotes(char *str, t_valuer *val)
{
	if (str[val->i] == 34)
	{
		val->i++;
		if (val->j % 2 == 0)
			val->k++;
		if (!str[val->i])
			return ;
		if (str[val->i] == 34 && val->j % 2 == 0 && val->k % 2 != 0)
		{
			val->i++;
			val->k++;
		}
		verefy_quotes_cont(str, val);
	}
	else if (str[val->i] == 39)
	{
		val->i++;
		if (val->k % 2 == 0)
			val->j++;
		if (str[val->i] == '\0')
			return ;
		if (str[val->i] == 39 && val->k % 2 == 0 && val->j % 2 != 0)
		{
			val->i++;
			val->j++;
		}
		verefy_quotes_cont_2(str, val);
	}
	else
		val->i++;
}

int	verefy_quotes(char *str)
{
	t_valuer	val;

	val.i = 0;
	val.j = 0;
	val.k = 0;
	while (str[val.i] == ' ' || str[val.i] == '\t')
		val.i++;
	if (str[val.i] == '\0')
		return (1);
	while (str[val.i] != '\0')
		loop_verefy_quotes(str, &val);
	if ((val.j % 2 != 0) || (val.k % 2 != 0))
	{
		g_global = 1;
		printf("Error quotes not closed\n");
		return (1);
	}
	return (0);
}
