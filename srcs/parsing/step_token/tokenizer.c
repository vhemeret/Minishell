/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 03:18:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/04 19:22:30 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// void	type_of_word(t_token **lst)
// {
// 	t_token	*tmp;
// 	int		pipe;

// 	tmp = (*lst);
// 	pipe = 0;
// 	while (tmp)
// 	{
		
// 	}
	
// }

void	put_word_index(t_token **tmp, char *str)
{
	static int	i = 1;

	if (str[0] == '|')
		i = 0;
	(*tmp)->word = ft_strdup(str);
	(*tmp)->index = i;
	i++;
	if ((*tmp)->next == NULL)
		i = 0;
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
	put_word_index(&lst, cmd[0]);
	if (len == 1)
		lst->next = NULL;
	else
	{
		printf("%i\n", len);
		i = 1;
		tmp = lst;
		while (i < len)
		{
			tmp->next = malloc(sizeof(t_token) * (1));
			if (!lst->next)
				return ;
			tmp = tmp->next;
			put_word_index(&tmp, cmd[i]);
			//tmp->word = ft_strdup(cmd[i]);
			i++;
		}
		tmp->next = NULL;
	}
	tmp = lst;
	free_double_array(cmd);
	while (tmp)
	{
		printf("word -> %s | index -> %i\n", tmp->word, tmp->index);
		tmp = tmp->next;
	}
	//type_of_word(&lst);
}