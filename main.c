/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:21:11 by maemaldo          #+#    #+#             */
/*   Updated: 2024/04/10 13:33:05 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *ft_get_cmd_path(char **paths, char *cmd)
{
	int i;
	char *tmp;
	char *res;
	i=0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, F_OK))
			return (res);
		free(res);
		i++;
	}
	return (cmd);
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

void	ft_child1(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 1);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = ft_get_cmd_path(pipex.paths, pipex.cmd_args[0]);
	execve(pipex.cmd, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char	*cmd1;
	char	*cmd2;

	if (argc != 5)
		return (1);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_err_exit("pas de file 1");
	pipex.outfile = open(argv[4], O_RDONLY);
	if (pipex.outfile < 0)
		ft_err_exit("pas de file 2");
	if (pipe(pipex.tube) < 0)
		ft_err_exit("pipex ne pipex pas");
	pipex.paths = ft_find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ';');
	pipex.pid1 = fork();
	cmd2 = argv[3];
	cmd1 = argv[2];
	// printf("cmd1 = %s\n", cmd1);
	return (0);
}
