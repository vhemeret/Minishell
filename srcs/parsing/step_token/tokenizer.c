/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 03:18:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/22 23:39:13 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	type_of_word2(t_token *tmp, t_token *first, t_token *save)
{
	if (tmp->word[0] == '<' || tmp->word[0] == '>')
		tmp->type = is_type(tmp);
	else
	{
		if (is_outfile_drout(save))
			tmp->type = FD;
		else if (is_limitor(save))
			tmp->type = LIMITOR;
		else if (save->type == R_IN)
			tmp->type = FD;
		else if (save->type == R_OUT)
			tmp->type = FD;
		else if ((save->type == FD || save->type == LIMITOR)
			&& (!tmp->next || tmp->next->word[0] == '|' || tmp->next))
		{
			if (first->type != CMD)
				tmp->type = CMD;
			else
				tmp->type = ARG;
		}
		else
			tmp->type = ARG;
	}
}

void	type_of_word(t_token **lst)
{
	t_token	*tmp;
	t_token	*save;
	t_token	*first;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->index == 1)
			first = tmp;
		if (tmp->index == 1 && tmp->word[0] != '<' && tmp->word[0] != '>')
			tmp->type = CMD;
		else if (tmp->index == 0)
			tmp->type = PIPE;
		else
			type_of_word2(tmp, first, save);
		save = tmp;
		tmp = tmp->next;
	}
}

void	put_index_node(t_token **lst)
{
	int		i;
	t_token	*tmp;

	i = 1;
	tmp = (*lst);
	while (tmp)
	{
		if (tmp->word[0] == '|')
			i = 0;
		tmp->index = i;
		tmp->type = -1;
		tmp = tmp->next;
		i++;
	}
}

void	add_back_node(t_token **lst, char **cmd, int words, int len)
{
	int		i;
	t_token	*tmp;
	t_token	*save;

	i = 1;
	tmp = (*lst);
	save = (*lst);
	(*lst)->back = NULL;
	while (i < len)
	{
		tmp->next = ft_malloc(sizeof(t_token) * (1));
		if (!(*lst)->next)
			return ;
		tmp = tmp->next;
		tmp->back = save;
		save = save->next;
		tmp->word = ft_strdup(cmd[i]);
		tmp->nb_words = words;
		i++;
	}
	tmp->next = NULL;
}

void	tokenizer(char **cmd, t_token **lst, int words)
{
	int		i;
	int		len;

	i = 0;
	while (cmd[i])
		i++;
	len = i;
	(*lst) = ft_malloc(sizeof(t_token) * (1));
	if (!lst)
		return ;
	(*lst)->word = ft_strdup(cmd[0]);
	(*lst)->nb_words = words;
	if (len == 1)
	{
		(*lst)->next = NULL;
		(*lst)->back = NULL;
	}
	else
		add_back_node(lst, cmd, words, len);
	free_double_array(cmd);
	put_index_node(lst);
	type_of_word(lst);
}
