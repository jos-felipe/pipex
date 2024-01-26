/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:19:25 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/25 11:31:38 by josfelip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	free_heap(t_list *lst_memory)
{
	t_list	*tmp;

	while (lst_memory)
	{
		tmp = lst_memory;
		lst_memory = lst_memory->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_whereis(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	char	*fn;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fn = ft_strjoin(tmp, cmd);
		if (access(fn, X_OK) == 0)
		{
			free(tmp);
			free_split(paths);
			return (fn);
		}
		free(fn);
		free(tmp);
		i++;
	}
	free_split(paths);
	return (NULL);
}
