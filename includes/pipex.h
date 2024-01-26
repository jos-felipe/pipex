/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:04:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/26 12:23:56 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	int		pid1;
	int		pid2;
	char	*path;
	char	**argv1;
	char	**argv2;
	char	*fn1;
	char	*fn2;
	t_list	*lst_memory;
	int		status;
}				t_pipex;

//  parser.c functions prototype
void	ft_process_envp(t_pipex *pipex, char *envp[]);
void	ft_parse_cmd1(t_pipex *pipex);
void	ft_parse_cmd2(t_pipex *pipex);

//  main.c functions prototype
int		main(int argc, char *argv[], char *envp[]);
void	ft_init(t_pipex *pipex);
void	ft_connect_fds(t_pipex *pipex);

//  safety.c functions prototype
void	ft_validate_user_inputs(int argc, char *argv[], char *envp[], \
t_pipex *pipex);
char	*ft_hacker_protection(char *cmd);
void	ft_safe_exit(t_pipex *pipex);

//  shell.c functions prototype
void	ft_tty1(t_pipex *pipex, char *envp[]);
void	ft_tty2(t_pipex *pipex, char *envp[]);
int		ft_get_exit_status(int exit_status);

//  utils.c functions prototype
char	*get_path(char *envp[]);
t_list	*ft_lstnew(void *content);
void	free_heap(t_list *lst_memory);
void	free_split(char **split);
char	*ft_whereis(char *cmd, char *path);

#endif