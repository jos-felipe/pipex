/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:38:33 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/12 11:07:35 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

# define CMD_NOT_FOUND 127
# define SPACE 32
# define TWO_POINTS 58

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

// Start Functions
void	start_io_files(t_pipex *pipex, char *argv[]);
void	start_input_file(t_pipex *pipex, char *in_file);
void	start_output_file(t_pipex *pipex, char *out_file);

// Utils Functions
void	handle_error(short exit_code);
void	handle_file_error(short exit_code);
void	clear_all(t_pipex *pipex, short exit_code);
void	clear_invalid_command(t_pipex *pipex, size_t cmd_pos);
void	free_split(char **split);
void	free_variables(char *var, char **split_var);

// Commands Functions
void	get_commands(t_pipex *pipex, char *argv[], char *envp[]);
char	*validate_path(char *cmd_name, char **split_path);
char	*get_cmd_path(char *cmd_name, char *envp[]);
char	*get_cmd_name(char *cmd_name);
char	**get_arguments(char *argv);

// Execute Functions
void	execute_commands(t_pipex *pipex);
void	exec_child_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos);
void	initial_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos);
void	final_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos);

#endif