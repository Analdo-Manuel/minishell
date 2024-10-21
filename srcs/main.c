/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:28:55 by almanuel          #+#    #+#             */
/*   Updated: 2024/10/21 16:42:26 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(char **p)
{
	size_t i;

	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *str, char *src)
{
	size_t	i;
	size_t	j;
	char *join;

	i = 0;
	j = 0;

	if(!str)
		return (NULL);
	
	join = (char *)malloc(ft_strlen(str) + ft_strlen(src) + 1);
	if (!str || !join ||!src )
		return (0);
	while (str[i] != '\0')
	{
		join[i] = str[i];
		i++;
	}
	while (src[j] != '\0')
	{
		join[i] = src[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

char	*find_executable(char *comando)
{
    char	**p;
    char	*path;
	char	*str;
	size_t	i;

    if (access(comando, X_OK) == 0)
	{
		if (access(comando, F_OK) == 0)
			printf("O comando exit");
        return strdup(comando);
	}
	path = getenv("PATH");
	char	*path_copy = strdup(path);
	p = ft_split(path_copy, ':');
	i = 0;
    while (p[i])
	{
		str = ft_strjoin(p[i], comando);
        if (access(str, X_OK) == 0)
			return (str);
		free(str);
		i++;
    }
    return (NULL);
}

int	main(void)
{
	char	*comando;
	char	*path;
	char	**p;

	while (1)
	{
		comando = readline("minishell> ");
		add_history(comando);
		printf("%s.", comando);
		p = ft_split_one(comando);
		path = find_executable(p[0]);
		if (execve(path, p, NULL) == -1)
			perror("Erro ao executar execvp");	
		if (strcmp(comando, "exit") == 0)
		{
			free(comando);
			break ;
		}
		free_all(p);
		free(comando);
	}
	return (0);
}
