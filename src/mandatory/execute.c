/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:26:37 by josfelip          #+#    #+#             */
/*   Updated: 2023/12/19 11:26:40 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_commands(t_pipex *pipex)
{
	size_t	index;

	index = 0;
	while (index < pipex->commands)
	{
		if (index < pipex->commands - 1)
			if (pipe(pipex->fd_pipe) < 0)
				handle_error(2);
		pipex->commands_array[index].pid = fork();
		if (pipex->commands_array[index].pid < 0)
			handle_error(3);
		if (pipex->commands_array[index].pid == 0)
			exec_child_process(pipex, &pipex->commands_array[index], index);
		else
		{
			close(pipex->fd_pipe[1]);
			waitpid(pipex->commands_array[index].pid, NULL, WNOHANG);
		}
		free(pipex->commands_array[index].cmd);
		if (pipex->commands_array[index].argv)
			free_split(pipex->commands_array[index].argv);
		index++;
	}
	close(pipex->fd_pipe[0]);
}

void	exec_child_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos)
{
	if (command->proc_type == INITIAL)
		initial_process(pipex, command, cmd_pos);
	else if (command->proc_type == FINAL)
		final_process(pipex, command, cmd_pos);
}

void	initial_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos)
{
	short	read_pipe;
	short	write_pipe;

	read_pipe = pipex->fd_pipe[0];
	write_pipe = pipex->fd_pipe[1];
	dup2(pipex->fd_input_file, STDIN_FILENO);
	close(read_pipe);
	dup2(write_pipe, STDOUT_FILENO);
	close(write_pipe);
	if (execve(command->cmd, command->argv, command->envp) < 0)
		clear_invalid_command(pipex, cmd_pos);
}

void	final_process(t_pipex *pipex, t_cmd *command, size_t cmd_pos)
{
	short	read_pipe;
	short	write_pipe;

	read_pipe = pipex->fd_pipe[0];
	write_pipe = pipex->fd_pipe[1];
	dup2(pipex->fd_output_file, STDOUT_FILENO);
	close(write_pipe);
	dup2(read_pipe, STDIN_FILENO);
	close(read_pipe);
	if (execve(command->cmd, command->argv, command->envp) < 0)
		clear_invalid_command(pipex, cmd_pos);
}