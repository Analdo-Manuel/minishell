/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:04:52 by marccarv          #+#    #+#             */
/*   Updated: 2024/10/24 15:58:15 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parse_single_quotes(char *input)
{
	char	*result;
	int	i;
	int	j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(input) + 1);
	while(input[i])
	{
		if (input[i] == 39)
		{
			i++;
			while(input[i] && input[i] != 39)
				result[j++] = input[i++];
		}
		i++;
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*extract_comand(char *input, int *i)
{
	char	*variable;
	int	j;

	j = 0;
	variable = malloc(ft_strlen(input) + 1);
	while(input[i] && input[i] != ' ' || input[i] != '\t' || input[i] != '\n' || input[i] != 34)
	{
		variable[j] =  input[i];
		j++;
		*i += 1;
	}
	variable = '\0';
	return (variable);
}

char	*parse_double_quotes(char *input)
{
	char	*result;
	char	*variable_name;
	char	*variable_value;
	int	i;
	int	j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(input) + 1);

	while (input[i])
	{
		if (input[i] == 34)
		{
			i++;
			while (input[i] && input[i] != 34)
			{
				if (input[i] == '$')
				{
					i++;
					variable_name = extract_comand(input, &i);
					variable_value = getenv(variable_name);
					if (variable_value)
					{
						strcpy(&result[j], variable_value);
						j += strlen(variable_value);
					}
					free(variable_name);
				}
				else
					result[j++] = input[i++];
			}
			i[++];
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*expand_empty_variable(char *input)
{
	char	*result;
	int	i;
	int	j;

	i = 0;
	j = 0;
	result = (char *) malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			variable_name = extract_comand(input, &i);
			variable_value = getenv(variable_name);
			if (variable_value)
			{
				strcpy(&result[j], variable_value);
				j += ft_strlen(variable_value);
			}
			free(variable_name);
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
