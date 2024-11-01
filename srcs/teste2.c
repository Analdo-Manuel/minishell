/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:43:42 by marccarv          #+#    #+#             */
/*   Updated: 2024/11/01 08:43:50 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = -1;
	while (s1[++k] && s1[k] != '=')
		;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		if (s1[i] == s2[i])
			k--;
		i++;
	}
	if (s2[i] == '=' && k == 0 && s1[i] == '=')
		return (k);
	return (s1[i] - s2[i]);
}

char	**ft_strdup(char **src, char *export)
{
	char	**str;
	int		i;
	int		j;
	int		k;
	bool	teste = false;

	i = -1;
	j = 0;
	k = 0;
	while (src[++i])
		;
	str = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (src[j])
	{
		i = -1;
		while (src[j][++i])
			;
		str[j] = (char *)malloc(sizeof(char) * (i + 1));
		i = -1;
		printf("%s\n", src[j]);
		printf("%d\n", ft_strcmp(export, src[j]));
		printf("----------------------------------\n\n\n");
		while (src[j][++i])
		{
			if (ft_strcmp(export, src[j]) == 0)
			{
				i = -1;
				while (export[++i])
					;
				str[k] = (char *)malloc(sizeof(char) * (i + 1));
				i = -1;
				while (export[++i])
					str[j][i] = export[i];
				printf("%s\n", export);
				printf("teste----------------------------------\n\n\n");
				teste = true;
				break ;
			}
			str[j][i] = src[j][i];
		}
		str[j][i] = '\0';
		//k++;
		j++;
	}
	if (teste == false)
	{
		i = -1;
		while (export[++i])
			;
		str[j] = (char *)malloc(sizeof(char) * (i + 1));
		i = -1;
		while (export[++i])
			str[j][i] = export[i];
		printf("%s\n", export);
		printf("----------------------------------\n\n\n");
		str[j][i] = '\0';
		j++;
	}
	str[j] = NULL;
	return (str);
}

void	free_all(char **p)
{
	size_t	i;

	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int	i;
	char	**teste;
	
	teste = ft_strdup(env, "SHLVL=0");
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	printf("----------------------------------\n\n\n");
	i = 0;
	while (teste[i])
		printf("%s\n", teste[i++]);
	free_all(teste);
	return (0);
}
