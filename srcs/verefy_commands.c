/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verefy_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:59:22 by marccarv          #+#    #+#             */
/*   Updated: 2024/11/15 11:40:00 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	verefy_quotes_cont(char *str, t_valuer *val)
{
	while (str[val->i] && str[val->i] != 34)
	{
		val->i++;
		if (str[val->i] == 34)
		{
			val->k++;
			break ;
		}
	}
}

static void	verefy_quotes_cont_2(char *str, t_valuer *val)
{
	while (str[val->i] && str[val->i] != 39)
	{
		val->i++;
		if (str[val->i] == 39)
		{
			val->j++;
			break ;
		}
	}
}

void	loop_verefy_quotes(char *str, t_valuer *val)
{
	if (str[val->i] == 34)
	{
		val->i++;
		val->k++;
		if (str[val->i] == 34)
			val->k++;
		verefy_quotes_cont(str, val);
	}
	else if (str[val->i] == 39)
	{
		val->i++;
		val->j++;
		if (str[val->i] == 39)
			val->j++;
		verefy_quotes_cont_2(str, val);
	}
	val->i++;
}

int	verefy_quotes(char *str)
{
	t_valuer	val;

	val.i = 0;
	val.j = 0;
	val.k = 0;
	if (str[0] == '\0')
		return (1);
	while (str[val.i] != '\0')
		loop_verefy_quotes(str, &val);
	if ((val.j % 2 != 0) || (val.k % 2 != 0))
	{
		printf("Error quotes not closed\n");
		return (1);
	}
	return (0);
}
