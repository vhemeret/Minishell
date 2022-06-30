/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 04:59:57 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/30 06:15:56 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// static int	len_squote_expantion(char *w, int *l)
// {
// 	int		j;

// 	j = 0;
// 	while (w[j++] && w[j] != '\'')
// 		(*l)++;
// 	return (j);
// }

// static int	check_if_var_found(char c, t_quote *st, char nv, int j)
// {
// 	if ((c == '\0' || sign(c, st) || c == '$') && nv && j != 0 && nv == '=')
// 		return (1);
// 	return (0);
// }

// static int	len_dquote_expantion(char *w, int *l, char **nv, t_quote *st)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = -1;
// 	while (nv[++i])
// 	{
// 		j = 0;
// 		k = 1;
// 		if (w[k] == nv[i][j])
// 		{
// 			while (w[k] && nv[i][j] && nv[i][j] != '=' && w[k] == nv[i][j])
// 			{
// 				j++;
// 				k++;
// 			}
// 			if (check_if_var_found(w[k], st, nv[i][j], j))
// 			{
// 				while (nv[i][++j])
// 					(*l)++;
// 				return (k);
// 			}
// 		}
// 	}
// 	return (0);
// }

// int	search_in_env_len(char *w, char **nv, t_quote *st, int *l)
// {
// 	if (st->is_quote == 1 && st->is_dquote == 0)
// 		return (len_squote_expantion(w, l));
// 	else
// 		return (len_dquote_expantion(w, l, nv, st));
// 	return (0);
// }

int	search_in_env_len(char *word, char **save_env, t_quote *state, int *len)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	if (state->is_quote == 1 && state->is_dquote == 0)
	{
		while (word[j++] && word[j] != '\'')
			(*len)++;
		return (j);
	}
	else
	{
		i = -1;
		while (save_env[++i])
		{
			j = 0;
			k = 1;
			if (word[k] == save_env[i][j])
			{
				while (word[k] && save_env[i][j]
					&& save_env[i][j] != '=' && word[k] == save_env[i][j])
				{
					j++;
					k++;
				}
				if ((word[k] == '\0' || sign(word[k], state)
						|| word[k] == '$') && save_env[i][j]
					&& j != 0 && save_env[i][j] == '=')
				{
					while (save_env[i][++j])
						(*len)++;
					return (k);
				}
			}
		}
	}
	return (k);
}
