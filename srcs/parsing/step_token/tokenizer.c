/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 03:18:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/16 18:58:42 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	type_of_word(t_token **lst)
{
	t_token	*tmp;
	t_token	*save;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->index == 1 && tmp->word[0] != '<' && tmp->word[0] != '>')
			tmp->type = 0;
		else if (tmp->index == 0)
			tmp->type = 10;
		else
		{
			if (tmp->word[0] == '<' || tmp->word[0] == '>')
				tmp->type = is_type(tmp);
			else
			{
				if (is_outfile_drout(save))
					tmp->type = 9;
				else if (is_limitor(save))
					tmp->type = 8;
				else if (save->type == 2)
					tmp->type = 6;
				else if (save->type == 3)
					tmp->type = 7;
				else if (save->type == 6 && tmp->next->word[0] == '|')
					tmp->type = 0;
				else
					tmp->type = 1;
			}
		}
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

void	tokenizer(char **cmd)
{
	int		i;
	int		len;
	t_token	*lst;
	t_token *tmp;

	i = 0;
	while (cmd[i])
		i++;
	len = i;
	lst = malloc(sizeof(t_token) * (1));
	if (!lst)
		return ;
	lst->word = ft_strdup(cmd[0]);
	if (len == 1)
		lst->next = NULL;
	else
	{
		i = 1;
		tmp = lst;
		while (i < len)
		{
			tmp->next = malloc(sizeof(t_token) * (1));
			if (!lst->next)
				return ;
			tmp = tmp->next;
			tmp->word = ft_strdup(cmd[i]);
			i++;
		}
		tmp->next = NULL;
	}
	free_double_array(cmd);
	put_index_node(&lst);
	type_of_word(&lst);
	tmp = lst;
	char	*types[11] = {"CMD", "ARG", "R_IN", "R_OUT", "DR_IN", "DR_OUT", "INFILE", "OUTFILE", "LIMITOR", "OUTFILE_DROUT", "PIPE"};
	while (tmp)
	{
		printf("\033[31;01m\t[%s]\033[00m \033[32;01m|\033[00m \033[33;01m[%s]\033[00m\n", tmp->word, types[tmp->type]);
		tmp = tmp->next;
	}
}
