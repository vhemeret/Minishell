/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/01 02:42:26 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	check(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
		if (word[i] == '$' || word[i] == '"' || word [i] == '\'')
			return (1);
	return (0);
}

void	manage_expantion(t_token **expnd, t_quote *st, char **nv, t_expand *exp)
{	
	int		i;
	char	**expanded;

	i = -1;
	exp->len = 0;
	exp->str = malloc_for_expand(expnd, st, nv);
	if (!exp->str)
		return ;
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
		{
			exp->str[exp->len++] = (*expnd)->word[i];
		}
	}
	exp->str[exp->len] = '\0';
	if (exp->need_expand == 1 && exp->quote == 0)
		expanded = split_word(exp->str, st);
	else
	{
		(*expnd)->word = remove_quote(exp->str, st);
		return ;
	}
	free(exp->str);
	exp->str = NULL;
	replace_old_node(expnd, expanded);
}

int	need_expand_or_rm_quote(t_token **to_check, t_quote *state, t_expand *exp)
{
	int		i;

	exp->need_expand = 0;
	exp->quote = 0;
	i = -1;
	while ((*to_check)->word[++i])
	{
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
	char		**save_env;
	t_token		*tmp;
	t_token		*save;
	t_expand	*exp;

	exp = malloc(sizeof(t_expand));
	if (!exp)
		return ;
	save_env = copy_env(env);
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
				manage_expantion(&save, state, save_env, exp);
		}
		else
			tmp = tmp->next;
	}
	tmp = (*lst);
	free(exp);
	exp = NULL;
	tmp = (*lst);
}
