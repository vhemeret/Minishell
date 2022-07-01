/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:07:52 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/01 02:42:51 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	sign(char c, t_quote *st)
{
	if (c)
	{
		if (c == ':' || c == '=' || c == '%' || c == '^' || c == '+' || c == '~'
			|| c == '/' || c == '?' || c == ' '
			|| ((c == '"' || c == '\'') && st->is_dquote == 1)
			|| c == ']' || c == '@')
			return (1);
	}
	return (0);
}

int	single_quote_expantion(char *word, t_expand *exp)
{
	int	i;

	i = -1;
	while (word[++i] && word[i] != '\'')
		exp->str[exp->len++] = word[i];
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
		if (w[i] == nv[x][y])
		{
			while (w[i] && nv[x][y] && w[i] == nv[x][y])
			{
				i++;
				y++;
			}
			if ((w[i] == '\0' || w[i] == '$' || sign(w[i], state))
				&& nv[x][y] && nv[x][y] == '=')
			{
				exp->found = 1;
				while (nv[x][++y])
					exp->str[exp->len++] = nv[x][y];
				return (i);
			}
		}
	}
	if (exp->found == 0)
	{
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
	}
	return (i);
}

char	*malloc_for_expand(t_token **to_expand, t_quote *state, char **env)
{
	int		j;
	int		len;
	char	*str;

	j = 0;
	len = 0;
	while ((*to_expand)->word[j])
	{
		quoting_state((*to_expand)->word[j], state);
		if ((*to_expand)->word[j] == '$')
			j += search_in_env_len(&(*to_expand)->word[j], env, state, &len);
		else
		{
			len++;
			j++;
		}
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	return (str);
}
