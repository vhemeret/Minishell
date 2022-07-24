/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 04:59:57 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/18 02:04:49 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	len_squote_expantion(char *w, int *l)
{
	int		i;

	i = -1;
	while (w[i++] && w[i] != '\'')
		(*l)++;
	return (i);
}

static int	len_expantion(char *w, int *len, char *nv, t_quote *st)
{
	int			i;
	int			y;

	i = 0;
	y = 0;
	while (w[i++] && nv[y] && nv[y] != '=' && w[i] == nv[y])
		y++;
	if ((w[i] == '\0' || sign(w[i], st) || w[i] == '$') && nv[y]
		&& y != 0 && nv[y] == '=')
	{
		st->found = 1;
		while (nv[++y])
			(*len)++;
		return (i);
	}
	return (i);
}

int	search_in_env_len(char *w, char **nv, t_quote *st, int *len)
{
	int			x;
	int			y;
	int			i;

	st->found = 0;
	if (st->is_quote == 1 && st->is_dquote == 0)
		return (len_squote_expantion(w, len));
	else
	{
		x = -1;
		while (nv[++x])
		{
			y = 0;
			i = 1;
			if (w[i] == nv[x][y])
			{
				i = len_expantion(w, len, nv[x], st);
				if (st->found == 1)
					return (i);
			}
		}
	}
	return (i);
}
