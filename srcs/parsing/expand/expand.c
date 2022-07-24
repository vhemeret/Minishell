/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/22 23:39:13 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	sign(char c, t_quote *st)
{
	(void)st;
	if (c)
	{
		if (c == ':' || c == '=' || c == '%' || c == '^' || c == '+' || c == '~'
			|| c == '/' || c == ' '
			|| ((c == '"' || c == '\''))
			|| c == ']' || c == '@')
			return (1);
	}
	return (0);
}

static int	check(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
		if (word[i] == '$' || word[i] == '"' || word [i] == '\'')
			return (1);
	return (0);
}

int	need_expand_or_rm_quote(t_token **to_check, t_quote *state, t_expand *exp)
{
	int		i;

	exp->need_expand = 0;
	exp->quote = 0;
	i = -1;
	while ((*to_check)->word[++i])
	{
		if ((*to_check)->type == LIMITOR)
			return (0);
		if ((*to_check)->word[i] == '$')
			exp->need_expand = 1;
		if ((*to_check)->word[i] == '"' || (*to_check)->word[i] == '\'')
			exp->quote = 1;
	}
	if (exp->need_expand == 0 && exp->quote == 1)
		(*to_check)->word = remove_quote((*to_check)->word, state);
	else
		return (1);
	return (0);
}

void	expand(t_token **lst, t_quote *state, char **env)
{
	t_token		*tmp;
	t_token		*save;
	t_expand	*exp;

	exp = ft_malloc(sizeof(t_expand));
	if (!exp)
		return ;
	tmp = (*lst);
	while (tmp)
	{
		save = tmp;
		if (check(tmp->word))
		{
			tmp = tmp->next;
			state->is_quote = 0;
			state->is_dquote = 0;
			if (need_expand_or_rm_quote(&save, state, exp))
				manage_expantion(&save, state, env, exp);
		}
		else
			tmp = tmp->next;
	}
	cleaning_parsing(exp, state);
}
