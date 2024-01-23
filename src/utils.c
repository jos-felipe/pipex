/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:19:25 by josfelip          #+#    #+#             */
/*   Updated: 2024/01/23 12:15:18 by josfelip         ###   ########.fr       */
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

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
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

char	*ft_whereis(char *cmd, char *path)
{
	char	**paths;
	char	*tmp;
	char	*fn;
	int		i;

	if (access(cmd, F_OK) == 0)
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
			free(paths);
			return (fn);
		}
		free(fn);
		free(tmp);
		i++;
	}
	free(paths);
	return (NULL);
}
