/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:28:53 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/22 09:12:16 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

char	*ft_strjoin_des(char *str, const char *src)
{
	size_t	i;
	size_t	j;
	char	*join;

	i = 0;
	j = 0;
	join = (char *) malloc(ft_strlen(str) + ft_strlen(src) + 3);
	while (str[i] != '\0')
	{
		join[i] = str[i];
		i++;
	}
	while (src[j] != '\0')
		join[i++] = src[j++];
	join[i] = '\0';
	free(str);
	return (join);
}

char	*ft_strjoin_des1(char *str, char *src)
{
	size_t	i;
	size_t	j;
	char	*join;

	i = 0;
	j = 0;
	join = (char *) malloc(ft_strlen(str) + ft_strlen(src) + 3);
	while (str[i] != '\0')
	{
		join[i] = str[i];
		i++;
	}
	while (src[j] != '\0')
		join[i++] = src[j++];
	join[i] = '\0';
	free(str);
	free(src);
	return (join);
}
