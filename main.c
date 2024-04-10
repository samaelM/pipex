/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:21:11 by maemaldo          #+#    #+#             */
/*   Updated: 2024/04/10 18:45:39 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;
	// int fd;

	i = 0;
	// fd = open("text", O_RDWR);
	// 	ft_putstr_fd("tab[i]", fd);
	while (tab[i])
		// ft_putstr_fd(tab[i], fd);
		free(tab[i++]);
	free(tab);
	// close(fd);
}

char	*ft_get_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, F_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

char	*ft_find_path(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	return (env[i] + 5);
}

void	ft_err_exit(char *msg)
{
	ft_printf("%s", msg);
	exit(0);
}

void	ft_cmd1(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = ft_get_cmd_path(pipex.cmd_paths, pipex.cmd_args[0]);
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	execve(pipex.cmd, pipex.cmd_args, envp);
	ft_free_tab(pipex.cmd_args);
	free(pipex.cmd);
}

void	ft_cmd2(t_pipex pipex, char *argv[], char *envp[])
{
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = ft_get_cmd_path(pipex.cmd_paths, pipex.cmd_args[0]);
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	execve(pipex.cmd, pipex.cmd_args, envp);
	ft_free_tab(pipex.cmd_args);
	free(pipex.cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (1);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_err_exit("pas de file 1");
	pipex.outfile = open(argv[4], O_TRUNC | O_RDWR);
	if (pipex.outfile < 0)
		ft_err_exit("pas de file 2");
	if (pipe(pipex.tube) < 0)
		ft_err_exit("pipex ne pipex pas");
	pipex.paths = ft_find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		ft_cmd1(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		ft_cmd2(pipex, argv, envp);
	ft_free_tab(pipex.cmd_paths);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
