/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:22:13 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/18 04:20:58 by vahemere         ###   ########.fr       */
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

void clean(t_exec *utils)
{
	if (utils->node)
	{
		ft_free_node(utils->node);
		utils->node = NULL;
	}
	if (utils->token_tmp)
	{
		ft_free_token(utils->token_tmp);
	}
}
t_token	*cleaning_parsing_error(t_quote *state, char **env)
{
	if (state)
	{
		free(state);
		state = NULL;
	}
	free_double_array(env);
	return (NULL);
}

void	cleaning_parsing(t_expand *exp, t_quote *state, char **env)
{	
	free(exp);
	exp = NULL;
	free(state);
	state = NULL;
	free_double_array(env);
}
