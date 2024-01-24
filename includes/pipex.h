/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:04:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/24 10:53:35 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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

//  heap.c functions prototype
void	process_envp(t_pipex *pipex, char *envp[]);
void	process_cmds(t_pipex *pipex);
void 	process_fns(t_pipex *pipex);
void	free_split(char **split);

//  main.c functions prototype
int	main(int argc, char *argv[], char *envp[]);

//  safety.c functions prototype
void	validate_user_inputs(int argc, char *argv[], t_pipex *pipex);
void	safe_exit(t_pipex *pipex);
int	get_exit_status(int exit_status);

//  shell.c functions prototype
void	tty1(t_pipex *pipex, char *envp[]);
void	tty2(t_pipex *pipex, char *envp[]);

//  stack.c functions prototype
void	init(t_pipex *pipex, char *argv[]);
void	connect_fds(t_pipex *pipex);

//  utils.c functions prototype
char	*get_path(char *envp[]);
t_list	*ft_lstnew(void *content);
void	free_heap(t_list *lst_memory);
char	*ft_whereis(char *cmd, char *path);

#endif