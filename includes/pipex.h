/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:04:24 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/22 20:24:55 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
	int		exit_code;
}				t_pipex;

void	init(t_pipex *pipex, char *argv[]);
void	init_fd(t_pipex *pipex);
void	init_envp(t_pipex *pipex, char *envp[]);
char	*get_path(char *envp[]);
t_list	*ft_lstnew(void *content);
void	free_memory(t_list *lst_memory);

#endif