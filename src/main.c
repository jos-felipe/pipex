#include "../includes/pipex.h"

int	get_exit_status(int exit_status)
{
	return (((exit_status & 0xff00)) >> 8);
}



// Checks if a cmd exists pipex.fd_in PATH
int	check_cmd(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (1);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(tmp);
			free(paths);
			return (1);
		}
		free(tmp);
		i++;
	}
	free(paths);
	return (0);
}
// Get cmd path from PATH
char	*get_cmd_path(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free(paths);
	return (NULL);
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

	if (argc == 5)
		init(&pipex, argv);
	else
	{
		ft_printf("Usage:\n%s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	init_fd(&pipex);
	init_envp(&pipex, envp);
	
	char **argv1 = split_cmd(pipex.cmd1);
	char **argv2 = split_cmd(pipex.cmd2);

	// Checks if a cmd exists pipex.fd_in PATH
	char *fn1 = get_cmd_path(argv1[0], pipex.path);
	if (fn1 == NULL) {
		ft_printf("Command not found: %s\n", argv1[0]);
	}
	char *fn2 = get_cmd_path(argv2[0], pipex.path);
	if (fn2 == NULL) {
		ft_printf("Command not found: %s\n", argv2[0]);
		pipex.exit_code = 127;
	}
	free(pipex.path);

	// execute cmd1
	if (pipex.fd_in > -1 && fn1 && fn2 && pipex.fd_out > -1)
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
			execve(fn1, argv1, envp);
		}
	}
	free(argv1);

	// execute cmd2
	if (fn2)
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
			execve(fn2, argv2, envp);
		}
	}
	free(argv2);

	close(pipex.fd_in);
	close(pipex.fd_out);
	close(pipex.fd_pipe[0]);
	close(pipex.fd_pipe[1]);

	if (pipex.pid2 != -1)
	{
		waitpid(pipex.pid2, &pipex.exit_code, 0);
		pipex.exit_code = get_exit_status(pipex.exit_code);
	}
	free_memory(pipex.lst_memory);
	exit(pipex.exit_code);
}
