/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:46:20 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/07 19:12:06 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_path(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
	}
	return (path);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char 	**path;

	i = -1;
	path = get_path(envp);
	if (!access(cmd, F_OK))
		return (cmd);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

pid_t	run(t_token *token, int *fd, int num, t_exec utils)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork ");
		return (0);
	}
	if (pid == 0)
	{
		if (num == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		else if (num == utils.nb_cmd - 1)
		{
			dup2(utils.previous_fd, STDIN_FILENO);
			close(fd[0]);
		}
		else
		{
			dup2(utils.previous_fd, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
		}
		if (execve(get_cmd_path(token->word, utils.envp), get_arg(token), utils.envp) == -1)
		{
			perror("Execve ");
			//exit(clean_pipex(input, 1));
		}
		//close_pipe(input);
		//clean_pipex(input, 0);
	}

	//perror("Command ");
	return (pid);
}

int		nb_cmd(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == 0)
			i++;
		token = token->next;
	}
	return (i);
}
void	exec(t_token *token, char **envp)
{
	int		status;
	pid_t *pid;
	int		i;
	int		fd[2];
	t_exec	utils;

	i = -1;
	utils.nb_cmd = nb_cmd(token);
	utils.envp = envp;
	fd[0] = 0;
	printf("nb = %i path =%s\n", utils.nb_cmd, get_cmd_path(token->word, envp));
	pid = malloc(sizeof(pid_t) * (utils.nb_cmd + 1));
	while (++i < utils.nb_cmd)
	{	
		while (token->type != CMD)
			token = token->next;
		utils.previous_fd = fd[0];
		if (utils.nb_cmd > 1)
			if (pipe(fd) < 0)
				return (perror("Pipe "));
		pid[i] = run(token, fd, i, utils);
		token = token->next;
		close(fd[1]);
		if (utils.previous_fd)
			close(utils.previous_fd);
	}
	i = -1;
	while (++i < utils.nb_cmd)
		waitpid(pid[i], &status, 0);
}