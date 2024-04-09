/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:21:11 by maemaldo          #+#    #+#             */
/*   Updated: 2024/04/09 17:47:08 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void ft_child1(t_pipex *pipex, char *argv[],char *envp[])
{
	dup2(pipex->tube[1],1);
	close(pipex->tube[0]);
	dup2(pipex->infile,1);
}

// int	ft_len_first_word(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	return (i);
// }
// int ft_copy_first_word(char *str, int len)
// {

// }
// int	ft_conv_cmd(char *str)
// {
// 	char	*cmd;
// 	char	len;
// 	char	*args;
// 	int		i;

// 	len = ft_len_first_word(str);
// 	cmd = malloc(sizeof(char) * len);
// 	i = 0;
// 	while (str[i] && str[i] != ' ')
// 	{
// 		cmd[i] = str[i];
// 		i++;
// 	}
// 	cmd[i] = 0;
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char	*cmd1;
	char	*cmd2;

	// char	*arg[] = {NULL};
	// int		id;
	// char	*outfile;
	// char	*test[] = {};
	// int		i;
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
	printf("cmd1 = %s\n", cmd1);
	// i = 0;
	// while (envp[i])
	// 	printf("env = %s\n", envp[i++]);
	// printf("fork\n");
	// if (id != 0)
	// 	(printf("premier process\n"), execve(cmd1, arg, envp), wait(NULL));
	// else
	// 	printf("deuxiemme process\n");
	return (0);
}
