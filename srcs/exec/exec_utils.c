/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:04:55 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/13 21:32:48 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int		get_nb_arg(t_token *token)
{
	int	i;

	i = 1;
	while (token && token->type != PIPE)
	{
		if (token->type == ARG)
			i++;
		token = token->next;
	}
	return (i);
}

char	**get_arg(t_token *token)
{
	char	**arg;
	int		nb_arg;
	int		i;

	i = 0;
	nb_arg = get_nb_arg(token);
	arg = malloc(sizeof(char *) * (nb_arg + 1));
	*arg = token->word;
	while (token && token->type != ARG && token->type != PIPE)
		token = token->next;
	while (++i < nb_arg && token->type == ARG)
	{
		arg[i] = token->word;
		//printf("%s\n", token->word);
		token = token->next;
	}
	arg[i] = NULL;
	return (arg);
}

void	set_r_in(t_node *node, t_token *token)
{
	//printf ("fd set in = %i, name = %s\n", node->here_doc_fd, node->here_doc);
	node->in = -1;
	while (token && token->type != PIPE)
	{
		if (token && token->type == R_IN && token->next->type == FD)
		{
			if (node->in > 0)
				close(node->in);
			if (!access(token->next->word, F_OK))
				node->in = open(token->next->word, O_RDONLY);
			else
			{
				node->in = -2;
				perror(token->next->word);
			}
		}
		if (token && token->type == DR_IN && token->next->type == FD)
		{
			if (node->in > 0)
				close(node->in);
			node->in = open(node->here_doc, O_RDONLY);
			node->here_doc_fd = node->in;
		}
		token = token->next;
	}
	//printf (" fd in = %i\n", node->in);
}

void	set_r_out(t_node *node, t_token *token)
{
	t_token *tmp;

	node->out = -1;
	tmp = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == DR_OUT || token->type == R_OUT)
			tmp = token;
		if (token->type == DR_OUT && node->in != -2)
		{
			if (node->out > 0)
				close (node->out);
			node->out = open(token->next->word, O_CREAT | O_RDWR | O_APPEND, 0644);
		}
		else if (token->type == R_OUT && node->in != -2)
		{
			if (node->out > 0)
				close (node->out);
			node->out = open(token->next->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		token = token->next;
	}
	if (tmp && (tmp->type == DR_OUT || tmp->type == R_OUT) && tmp->next)
		if (node->out == -1 && node->in != -2)
			perror("Outfile :");
}

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
		if (ft_strlen(envp[i]) >=5  && envp[i][0] == 'P' && envp[i][1] == 'A' 
			&& envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
		{
			path = ft_split(envp[i] + 5, ':');
			return (path);
		}
	}
	return (path);
}