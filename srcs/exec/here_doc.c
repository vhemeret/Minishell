/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:33:41 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 19:40:29 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc_run(char *limiter, t_node *node, char *buff)
{
	int		x;

	x = dup(0);
	while (1 && g_all.utils->can_run == 1)
	{
		buff = readline("> ");
		if (!buff && g_all.utils->can_run != 0)
		{
			write(2, "warning: here-document delimited by end-of-file.\n", 49);
			break ;
		}
		if (g_all.utils->can_run == 0)
		{
			dup2(x, 0);
			break ;
		}
		if (!ft_strcmp(buff, limiter))
			break ;
		else
		{
			write(node->here_doc_fd, buff, ft_strlen(buff));
			write(node->here_doc_fd, "\n", 1);
		}
	}
}

void	here_doc(char *limiter, t_node *node, int i)
{
	char	*buff;
	char	*num_str;

	buff = NULL;
	num_str = ft_itoa(i);
	node->here_doc = ft_strjoin(".here_doc_tmp", num_str);
	ft_free(num_str);
	node->here_doc_fd = open(node->here_doc, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (node->here_doc_fd == -1)
		return ;
	here_doc_run(limiter, node, buff);
	ft_free(buff);
}

void	here_doc_init(t_node *node, t_token *tk)
{
	int	i;

	i = 1;
	g_all.utils->on_here_doc = 1;
	handle_sig();
	while (tk && tk->type != PIPE && ++i && g_all.utils->can_run == 1)
	{
		if (tk && tk->type == DR_IN && tk->next && tk->next->type == LIMITOR)
		{
			if (node->here_doc_fd > 0)
			{
				close(node->here_doc_fd);
				unlink(node->here_doc);
			}
			here_doc(tk->next->word, node, i);
		}
		tk = tk->next;
	}
	g_all.utils->on_here_doc = 0;
	handle_sig();
}
