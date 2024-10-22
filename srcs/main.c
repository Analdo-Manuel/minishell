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

char	*ft_strdup(char	*src)
{
	char	*str;
	int	i;

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
    char	*path_copy;
	char	*str;
	size_t	i;

    if (access(comando, X_OK) == 0)
	{
		if (access(comando, F_OK) == 0)
			printf("O comando exit");
        return (comando);
	}
	path = getenv("PATH");
	path_copy = ft_strdup(path);
	p = ft_split(path_copy, ':');
	free(path_copy);
	i = 0;
    while (p[i])
	{
		str = ft_strjoin(p[i], comando);
        if (access(str, X_OK) == 0)
        {
        	free_all(p);
			return (str);
	}
		free(str);
		i++;
    }
    free_all(p);
    return (NULL);
}

int	main(void)
{
	char	*comando;
	char	*path;
	char	**p;
	pid_t	son;
	

	while (1)
	{
		comando = readline("minishell> ");
		add_history(comando);
		//printf("%s.", comando);
		p = ft_split_one(comando);
		path = find_executable(p[0]);
		son = fork();
		if (son == 0)
		{
			//free(path);
			execve(path, p, NULL);
			perror("Erro ao executar execvp");
		}
		wait(&son);	
		if (strcmp(comando, "exit") == 0)
		{
			free(path);
			free_all(p);
			free(comando);
			break ;
		}
		free(path);
		free_all(p);
		//free(comando);
	}
	return (0);
}
