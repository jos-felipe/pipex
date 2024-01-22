#include "./lib/libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	get_exit_status(int exit_status)
{
	return (((exit_status & 0xff00)) >> 8);
}

// Looks for PATH in envp
char	*get_path(char *envp[]) 
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

// Checks if a cmd exists in PATH
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
		printf("%s\n", array[i]);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[]) {
	int		in;
	int		out;
	int		fd[2];
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
	int		exit_code;
	int		pid1;
	int 	pid2;

	if (argc == 5)
	{
		infile = argv[1];
		cmd1 = argv[2];
		cmd2 = argv[3];
		outfile = argv[4];
		exit_code = 0;
		pid1 = -1;
		pid2 = -1;
	}
	else
	{
		printf("Usage: ./%s infile cmd1 cmd2 outfile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// Creates the news file descriptors
	in = open(infile, O_RDONLY);
	if (in == -1) 
	{
		perror(infile);
	}
	out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1) 
	{
		perror(outfile);
	}
	if (pipe(fd) == -1) {
		perror(outfile);
	}

	// Looks for PATH in envp
	char *path = get_path(envp);
	if (path == NULL) {
		printf("PATH not found\n");
		return (1);
	}
	
	char **argv1 = split_cmd(cmd1);
	char **argv2 = split_cmd(cmd2);

	// Checks if a cmd exists in PATH
	char *fn1 = get_cmd_path(argv1[0], path);
	if (fn1 == NULL) {
		printf("Command not found: %s\n", argv1[0]);
	}
	char *fn2 = get_cmd_path(argv2[0], path);
	if (fn2 == NULL) {
		printf("Command not found: %s\n", argv2[0]);
		exit_code = 127;
	}
	free(path);

	// execute cmd1
	if (in > -1 && fn1 && fn2 && out > -1)
	{
		pid1 = fork();
		if (pid1 < 0) 
		{
			printf("Fork failed\n");
			return 2;
		}
		if (pid1 == 0) {
			dup2(in, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(fn1, argv1, envp);
		}
	}
	free(argv1);

	// execute cmd2
	if (fn2)
	{
		pid2 = fork();
		if (pid2 < 0) {
			printf("Fork failed\n");
			return 2;
		}
		if (pid2 == 0) {
			dup2(fd[0], STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(fn2, argv2, envp);
		}
	}
	free(argv2);

	close(in);
	close(out);
	close(fd[0]);
	close(fd[1]);

	if (pid2 != -1)
	{
		waitpid(pid2, &exit_code, 0);
		exit_code = get_exit_status(exit_code);
	}	
	exit(exit_code);
}