/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:07:52 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 19:41:29 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	single_quote_expantion(char *word, t_expand *exp)
{
	int	i;

	i = -1;
	while (word[++i] && word[i] != '\'')
		exp->str[exp->len++] = word[i];
	return (i);
}

int	word_not_found(char *w, t_quote *state)
{
	int	i;

	i = 1;
	if (w[i])
	{
		while (w[i] != '\0' && w[i] != '$')
		{
			if (sign(w[i], state))
				return (i);
			i++;
		}
	}
	return (i);
}

int	put_error_code(t_expand *exp)
{
	int	i;

	i = -1;
	while (g_all.utils->errchar[++i])
		exp->str[exp->len++] = g_all.utils->errchar[i];
	ft_free(g_all.utils->errchar);
	g_all.utils->errchar = NULL;
	exp->found = 1;
	return (2);
}

int	search_word(char *w, t_expand *exp, char *nv, t_quote *state)
{
	int	i;
	int	y;

	i = -1;
	y = 0;
	if (w[1] == '?')
		return (put_error_code(exp));
	i = 0;
	while (w[i++] && nv[y] && w[i] == nv[y])
		y++;
	if ((w[i] == '\0' || w[i] == '$' || sign(w[i], state))
		&& nv[y] && nv[y] == '=')
	{
		exp->found = 1;
		while (nv[++y])
			exp->str[exp->len++] = nv[y];
		return (i);
	}
	return (i);
}

int	basic_expantion(char *w, t_expand *exp, char **nv, t_quote *state)
{
	int	i;
	int	x;
	int	y;

	i = 1;
	x = -1;
	exp->found = 0;
	while (nv[++x])
	{
		y = 0;
		i = 1;
		if (w[i] == '?')
			return (search_word(w, exp, nv[x], state));
		if (w[i] == nv[x][y])
		{
			i = search_word(w, exp, nv[x], state);
			if (exp->found == 1)
				return (i);
		}
	}
	if (exp->found == 0)
		return (word_not_found(w, state));
	return (i);
}
