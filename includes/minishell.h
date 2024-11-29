/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marccarv <marccarv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:29:40 by almanuel          #+#    #+#             */
/*   Updated: 2024/11/29 13:24:43 by marccarv         ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>
# include <fcntl.h>

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

# define BUFFER_SIZE 42

typedef struct s_valuer
{
	char	**p;
	char	*str;
	long	i;
	long	j;
	long	k;
	bool	signal;
	bool	f_pipe;
}	t_valuer;

typedef struct s_data
{
	char	**p;
	char	**str;
	char	**envp;
	char	**matrix;
	char	**export;
	char	*path_main;
	char	*path;
	char	*home;
	char	*command;
	bool	select;
	bool	f_pipe;
	int		status;
	int		exit;
	int		fd;
	int		fdpipe[2];
	int		control_padrao;
	int		stdout_padrao;
	int		stdin_padrao;
	pid_t	pid;
}	t_data;

extern int	g_global;

void	free_all(char **p);
void	handler_process(int sig);
void	sort_params(char **envp);
void	free_total(t_data *data);
void	clear_screen(char **envp);
void	realine_prompt(t_data *data);
void	*ft_memset(void *s, int c, long n);
void	loop_prompt(t_data *data, t_valuer *val);
void	builtins_pwd(t_data *data);
void	builtins_echo(t_data *data);
void	builtins_env(t_data *data);
void	builtins_cd_conf(t_data *data);
void	redirections_op(t_data *data, t_valuer *val1, char *str);

char	*ft_itoa(int n);
char	*get_next_line(int fd);
char	*str_alloc(char	*s1, char c);
char	*ft_strdup(const char	*src);
char	*expand_var_heredoc(char *s1);
char	**export_define(char **export);
char	*find_executable(t_data *data);
char	*ft_strcpy(char *dest, char *src);
char	**ft_split(const char	*str, char c);
char	**ft_split_pipe(char const *s, char c);
char	**ft_split_one(t_valuer *val, char *str);
char	**builtins_export_define(char **src, char *export);
char	**builtins_unset(char **envp, char *clear, t_valuer val);
char	**builtins_export(char **src, char *export);
char	*expand_variable(char *s1, char *s2, t_valuer *val);
char	*ft_strjoin(const char	*str, const char *src);
char	*ft_strjoin_des(char *str, const char *src);
char	*ft_strjoin_des1(char *str, char *src);

size_t	ft_strlen(const char *str);
size_t	checker_quotes(const char *str, char c);

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		verefy_quotes(char *str);
int		verefiy_redirect(char *str);
int		verefiy_pipe(char *str);
int		ft_strcmp(const char *s1, const char *s2);

bool	checker_builtins(t_data *data);

#endif
