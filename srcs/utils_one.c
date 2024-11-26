/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:37:26 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/25 09:01:58 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 == NULL)
		return (EOF);
	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcpy(char *dest, char *src)
{
	int		i;
	int		j;
	char	*output;

	output = malloc(ft_strlen(dest) + ft_strlen(src) + 1);
	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		output[i] = dest[i];
		i++;
	}
	while (src[j] != '\0')
		output[i++] = src[j++];
	output[i] = '\0';
	return (output);
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
	if (!str || !src)
		return (NULL);
	join = (char *) malloc(ft_strlen(str) + ft_strlen(src) + 4);
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
