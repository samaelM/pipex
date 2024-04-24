/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:42:42 by maemaldo          #+#    #+#             */
/*   Updated: 2024/04/16 17:42:06 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

char	*ft_get_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp == NULL)
			return (NULL);
		res = ft_strjoin(tmp, cmd);
		if (res == NULL)
			return (NULL);
		free(tmp);
		if (access(res, F_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

char	*ft_find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i] && ft_strncmp(env[i], "PATH=", 5) == 0)
		return (env[i] + 5);
	return (NULL);
}

void	ft_err_exit(char *msg)
{
	ft_printf("%s\n", msg);
	exit(0);
}
