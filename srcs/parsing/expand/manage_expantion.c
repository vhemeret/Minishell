/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expantion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 05:46:07 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 19:41:51 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	type_expantion(t_token **expnd, t_quote *st, char **nv, t_expand *exp)
{
	int	i;

	i = -1;
	while ((*expnd)->word[++i])
	{
		quoting_state((*expnd)->word[i], st);
		if ((*expnd)->word[i] == '$')
		{
			if ((*expnd)->word[i + 1] == '\0'
				|| sign((*expnd)->word[i + 1], st))
				exp->str[exp->len++] = (*expnd)->word[i];
			else if ((*expnd)->word[i + 1] && isdigits((*expnd)->word[i + 1]))
				i++;
			else if (st->is_quote == 1 && st->sq_first == 1)
				i += single_quote_expantion(&(*expnd)->word[i], exp) - 1;
			else
				i += basic_expantion(&(*expnd)->word[i], exp, nv, st) - 1;
		}
		else
			exp->str[exp->len++] = (*expnd)->word[i];
	}
}

void	len_for_expand(t_token **exp, t_quote *st, char **env, int *len)
{
	int	j;

	j = 0;
	while ((*exp)->word[j])
	{
		quoting_state((*exp)->word[j], st);
		if ((*exp)->word[j] == '$')
		{
			if ((*exp)->word[j + 1] && (*exp)->word[j + 1] == '?')
			{
				(*len) += ft_strlen(g_all.utils->errchar);
				j += 2;
			}
			else
				j += search_in_env_len(&(*exp)->word[j], env, st, len);
			if (st->found == 0 && (*exp)->word[j] && sign((*exp)->word[j], st))
				(*len)++;
		}
		else
		{
			(*len)++;
			j++;
		}
	}
}

char	*malloc_for_expand(t_token **exp, t_quote *st, char **env)
{
	int		len;
	char	*str;

	len = 0;
	st->found = 0;
	if ((*exp)->word[0] && (*exp)->word[0] == '$' && !(*exp)->word[1])
		len++;
	len_for_expand(exp, st, env, &len);
	str = ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	return (str);
}

void	manage_expantion(t_token **expnd, t_quote *st, char **nv, t_expand *exp)
{	
	char	**expanded;

	exp->len = 0;
	g_all.utils->errchar = ft_itoa(g_all.utils->err);
	exp->str = malloc_for_expand(expnd, st, nv);
	if (!exp->str)
		return ;
	st->is_quote = 0;
	st->is_dquote = 0;
	type_expantion(expnd, st, nv, exp);
	exp->str[exp->len] = '\0';
	if (exp->need_expand == 1 && exp->quote == 0)
		expanded = split_word(exp->str, st);
	else
	{
		(*expnd)->word = remove_quote(exp->str, st);
		return ;
	}
	ft_free(exp->str);
	exp->str = NULL;
	replace_old_node(expnd, expanded);
}
