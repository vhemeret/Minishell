/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:46:20 by brhajji-          #+#    #+#             */
/*   Updated: 2022/05/11 11:19:47 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t	run(t_token *token, char **envp)
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
		/*if (cmd > 1)
		{
			dup2(input->fd[cmd - 1].fd[0], STDIN_FILENO);
			dup2(input->fd[cmd].fd[1], STDOUT_FILENO);
			close(input->fd[cmd - 1].fd[1]);
			close(input->fd[cmd].fd[0]);
		}*/
		if (execve(token->word, get_arg(token), envp) == -1)
		{
			perror("Execve ");
			//exit(clean_pipex(input, 1));
		}
		//close_pipe(input);
		//clean_pipex(input, 0);
	}

	perror("Command ");
	return (pid);
}

int		nb_cmd(t_token *token)
{
	int	i;

	i = 0;
	while (token->next)
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
	int		nb;
	int		fd[2];

	i = -1;
	nb = nb_cmd(token);
	pid = malloc(sizeof(pid_t) * nb);
	while (++i < nb)
	{
		if (nb > 1)
			if (pipe(fd) < 0)
				return (perror("Pipe "));
		pid[i] = run(token, envp);
		close(fd[0]);
		close(fd[1]);
	}
	while (--i > 0)
		waitpid(pid[i], &status, 0);
}