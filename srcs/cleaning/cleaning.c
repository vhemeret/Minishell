/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:22:13 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/22 13:27:27 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_double_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

int	print_and_free(char *str, t_token **lst)
{
	t_token	*tmp;
	
	if (str)
		dprintf(2, "%s\n", str);
	while (tmp)
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp->word);
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

void	ft_free_node(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node;
		node = node->next;
		if (tmp->here_doc)
			free(tmp->here_doc);
		free(tmp);
		tmp = NULL;
	}
}


void	ft_free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->word)
			free(tmp->word);
		free(tmp);
		tmp = NULL;
	}
}