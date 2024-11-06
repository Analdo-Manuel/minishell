/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:04:37 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/06 14:56:37 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static
        void	ft_swap(char **a, char **b)
{
	char	*swp;

	swp = *a;
	*a = *b;
	*b = swp;
}
static
        int	ft_strcmp_params(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

void	sort_params(char **envp)
{
	int	i;

	i = 0;
    if (envp == NULL)
    {   
        return ;
    }
	while (envp[i + 1] != NULL)
	{
		if (ft_strcmp_params(envp[i], envp[i + 1]) > 0)
		{
			ft_swap(&envp[i], &envp[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	return ;
}