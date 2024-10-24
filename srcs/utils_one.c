/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:37:26 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/23 23:39:32 by analdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char	*src)
{
	char	*str;
	int		i;

	i = -1;
	while (src[++i])
		;
	str = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (src[++i])
		str[i] = src[i];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(const char *str, const char *src)
{
	size_t	i;
	size_t	j;
	char	*join;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	join = (char *) malloc(ft_strlen(str) + ft_strlen(src) + 1);
	if (!str || !join || !src)
		return (0);
	while (str[i] != '\0')
	{
		join[i] = str[i];
		i++;
	}
	while (src[j] != '\0')
		join[i++] = src[j++];
	join[i] = '\0';
	return (join);
}
