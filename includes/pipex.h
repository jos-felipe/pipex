/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:38:33 by josfelip          #+#    #+#             */
/*   Updated: 2023/12/18 16:22:46 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE,
}		t_bool;

typedef enum e_proc
{
	INITIAL,
	FINAL,
}		t_proc;

typedef struct s_cmd
{
	pid_t	pid;
	t_proc	proc_type;
	char	*cmd;
	char	**argv;
	char	**envp;
}			t_cmd;

typedef struct s_pipex
{
	int		fd_input_file;
	int		fd_output_file;
	int		fd_pipe[2];
	size_t	commands;
	t_cmd	*commands_array;
	t_bool	success;
}			t_pipex;

#endif