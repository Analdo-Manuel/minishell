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
	char	*str1 = "Marco ";
	char	*str2 = "Carvalho";
	char	*teste = ft_strcpy(str1, str2);

	printf("print cpy %s\n", teste);

	free(teste);
	return(0);
}
