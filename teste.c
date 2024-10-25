/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:16:46 by marccarv          #+#    #+#             */
/*   Updated: 2024/10/25 08:47:27 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;
	int	j;
	char	*aotput = malloc(ft_strlen(dest) + ft_strlen(src) + 1);

	i = 0;
	j = 0;
	while(dest[i] != '\0')
	{
		aotput[i] = dest[i];
		i++;
	}
	while(src[j] != '\0')
	{
		aotput[i] = src[j];
		i++;
		j++;
	}
	aotput[i] = '\0';
	return (aotput);
}



int	main(void)
{
	char	*str1 = "Ma";
	char	*str2 = "Marco ";
	char	*teste = ft_strcpy(str1, str2);
	int	teste2 = ft_strcmp(str1, str2);

	printf("print strcmp %d\n", teste2);
	printf("print cpy %s\n", teste);

	free(teste);
	return(0);
}
