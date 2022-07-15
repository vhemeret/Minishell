/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:33:41 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/14 04:44:33 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc(char *limiter, t_node *node, int i)
{
	char	*buff;
	char	*num_str;

	num_str = ft_itoa(i);
	node->here_doc = ft_strjoin(".here_doc_tmp", num_str);
	free(num_str);
	node->here_doc_fd = open(node->here_doc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (node->here_doc_fd == -1)
		return ;
	while (1)
	{
		buff = readline("> ");
		if (!ft_strcmp(buff, limiter))
		{
			free(buff);
			return ;
		}
		else
		{
			write(node->here_doc_fd, buff, ft_strlen(buff));
			write(node->here_doc_fd, "\n", 1);
		}
	}
	close(node->here_doc_fd);
	free(buff);
}

void here_doc_init(t_node *node, t_token *token)
{
	int	i;

	i = 1;

	while (token && token->type != PIPE && ++i)
	{
		if (token && token->type == DR_IN && token->next->type == FD)
		{
			if (node->here_doc_fd > 0)
			{
				close(node->here_doc_fd);

				unlink(node->here_doc);
			}
			here_doc(token->next->word, node, i);
		}
		token = token->next;
	}
}