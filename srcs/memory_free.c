/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:47:50 by almanuel          #+#    #+#             */
/*   Updated: 2024/12/14 22:45:20 by marccarv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(char **p)
{
	size_t	i;

	i = 0;
	if (p == NULL)
		return ;
	while (p[i])
		free(p[i++]);
	free(p);
}

void	free_total(t_data *data)
{
	if (data->path_main)
		free(data->path_main);
	if (data->matrix)
		free_all(data->matrix);
	if (data->envp)
		free_all(data->envp);
	if (data->export)
		free_all(data->export);
	if (data->command)
		free(data->command);
	printf("exit\n");
	exit(0);
}
void	free_total_exit(t_data *data)
{
	if (data->path_main)
		free(data->path_main);
	if (data->matrix)
		free_all(data->matrix);
	if (data->envp)
		free_all(data->envp);
	if (data->export)
		free_all(data->export);
	if (data->command)
		free(data->command);
}
