#include "../includes/pipex.h"

int	get_exit_status(int exit_status)
{
	return (((exit_status & 0xff00)) >> 8);
}



// Splits a cmd into an array of strings
char	**split_cmd(char *cmd)
{
	char	**cmd_split;
	int		i;

	cmd_split = ft_split(cmd, ' ');
	i = 0;
	while (cmd_split[i])
	{
		cmd_split[i] = ft_strtrim(cmd_split[i], " ");
		i++;
	}
	return (cmd_split);
}

// Prints an array of strings
void	ft_print_array(char *const *array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[]) {
	t_pipex	pipex;

	validate_user_inputs(argc, argv, &pipex);
	connect_fds(&pipex);
	process_envp(&pipex, envp);
	process_cmds(&pipex);
	process_fns(&pipex);

	// execute cmd1
	if (pipex.fd_in > -1 && pipex.fn1 && pipex.fn2 && pipex.fd_out > -1)
	{
		pipex.pid1 = fork();
		if (pipex.pid1 < 0) 
		{
			ft_printf("Fork failed\n");
			return 2;
		}
		if (pipex.pid1 == 0) {
			dup2(pipex.fd_in, STDIN_FILENO);
			dup2(pipex.fd_pipe[1], STDOUT_FILENO);
			close(pipex.fd_pipe[0]);
			close(pipex.fd_pipe[1]);
			execve(pipex.fn1, pipex.argv1, envp);
		}
	}
	free(pipex.argv1);

	// execute cmd2
	if (pipex.fn2)
	{
		pipex.pid2 = fork();
		if (pipex.pid2 < 0) {
			ft_printf("Fork failed\n");
			return 2;
		}
		if (pipex.pid2 == 0) {
			dup2(pipex.fd_pipe[0], STDIN_FILENO);
			dup2(pipex.fd_out, STDOUT_FILENO);
			close(pipex.fd_pipe[0]);
			close(pipex.fd_pipe[1]);
			execve(pipex.fn2, pipex.argv2, envp);
		}
	}
	free(pipex.argv2);

	close(pipex.fd_in);
	close(pipex.fd_out);
	close(pipex.fd_pipe[0]);
	close(pipex.fd_pipe[1]);

	if (pipex.pid2 != -1)
	{
		waitpid(pipex.pid2, &pipex.status, 0);
		pipex.status = get_exit_status(pipex.status);
	}
	free_memory(pipex.lst_memory);
	exit(pipex.status);
}

