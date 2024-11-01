/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almanuel <almanuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:29:40 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/01 20:51:26 by almanuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>

// Macros para cores de texto
# define BOLD   "\033[1m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define RESET   "\033[0m"

// Macros para cores de fundo
# define BG_RED     "\033[41m"
# define BG_GREEN   "\033[42m"
# define BG_YELLOW  "\033[43m"
# define BG_BLUE    "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN    "\033[46m"
# define BG_WHITE   "\033[47m"

typedef struct s_valuer
{
	char	**p;
	size_t	i;
	size_t	j;
	size_t	k;
	bool	signal;
}	t_valuer;

typedef struct s_data
{
	char	**p;
	char	**envp;
	char	**matrix;
	char	*path_main;
	char	*path;
	char	*command;
	bool	son;
}	t_data;

void	free_all(char **p);
void	free_total(t_data *data);
void	clear_screen(char **envp);
void	realine_prompt(t_data *data);
void	*ft_memset(void *s, int c, size_t n);
void	loop_prompt(t_data *data, t_valuer *val);
void	builtins_pwd(t_data *data);
void	builtins_echo(t_data *data);
void	builtins_env(t_data *data);

char	*str_alloc(char	*s1, char c);
char	*ft_strdup(const char	*src);
char	*find_executable(t_data	*data);
char	*ft_strcpy(char *dest, char *src);
char	**ft_split(const char	*str, char c);
char	**ft_split_one(t_valuer *val, char *str);
char	**builtins_unset(char **envp, char *clear);
char	**builtins_export(char **src, char *export);
char	*expand_variable(char *s1, char *s2, t_valuer *val);
char	*ft_strjoin(const char	*str, const char *src);

size_t	ft_strlen(const char *str);
size_t	checker_quotes(const char *str, char c);

int		verefy_quotes(char *str);
int		ft_strcmp(const char *s1, const char *s2);

bool	checker_builtins(t_data *data);

#endif
