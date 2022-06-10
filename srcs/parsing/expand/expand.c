/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/10 18:45:42 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	need_expand(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
		if (word[i] == '$')
			return (1);
	return (0);
}

int	search_in_env_len(char *word, char **save_env, t_quote *state, int *len)
{
	int		i;
	int		j;
	int		k;

	j = -1;
	if (state->is_quote == 1 && state->is_dquote == 0)
	{
		while (word[++j] && word[j] != '\'')
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
				while (word[k] && save_env[i][j] && save_env[i][j] != '=' && word[k] == save_env[i][j])
				{
					j++;
					k++;
				}
				if ((word[k] == '\0' || word[k] == '\'' || word[k] == '"') && save_env[i][j] && j != 0 && save_env[i][j] == '=')
				{
					while (save_env[i][++j])
						(*len)++;
					return (k);
				}
			}
		}
	}
	return (0);
}

char	*search_in_env(t_token **to_expand, char **save_env, t_quote *state, char *str)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = -1;
	j = 0;
	while ((*to_expand)->word[++i])
	{
		quoting_state((*to_expand)->word[i], state);
		if ((*to_expand)->word[i] == '$')
		{
			printf("%c\n", (*to_expand)->word[i]);
			if (state->is_quote == 1 && state->is_dquote == 0)
			{
				while ((*to_expand)->word[i] && (*to_expand)->word[i] != '\'')
					str[j++] = (*to_expand)->word[i++];
				i -= 1;
			}
			else
			{
				x = -1;
				i += 1;
				while (save_env[++x])
				{
					y = 0;
					if ((*to_expand)->word[i] == save_env[x][y])
					{
						while ((*to_expand)->word[i] && save_env[x][y] && save_env[x][y] != '=' && (*to_expand)->word[i] == save_env[x][y])
						{
							i++;
							y++;
						}
						if (((*to_expand)->word[i] == '\0' || (*to_expand)->word[i] == '\'' || (*to_expand)->word[i] == '"' || (*to_expand)->word[i] == '$') && save_env[x][y] && y != 0 && save_env[x][y] == '=')
						{
							if (save_env[x][y + 1] == '\0')
								str[j] = '$';
							printf("%s\n", &save_env[x][y]);
							while (save_env[x][++y])
								str[j++] = save_env[x][y];
						}
					}
				}
				i -= 1;
			}
		}
		else
			str[j++] = (*to_expand)->word[i];
	}
	str[j] = '\0';
	return (str);
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
	printf("len -> %i\n", len);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	return (str);
}

void	manage_expantion(t_token **to_expand, t_quote *state, char **env, t_index *index)
{
	(void)index;
	char	*str;
	
	str = malloc_for_expand(to_expand, state, env);
	if (!str)
		return ;
	str = search_in_env(to_expand, env, state, str);
// 	str = malloc_for_expand(to_expand, state, env);
// 	if (!str)
// 		return ;
// 	search_in_env();
// 	index->i = 0;
// 	while ((*to_expand)->word[index->i])
// 	{
// 		quoting_state((*to_expand)->word[index->i], state);
// 		if ((*to_expand)->word[index->i] == '$')
// 		{
// 				i += search_in_env(&str[index->i], &(*to_expand)->word[index->i], env, state, index);
// 				// printf("%i | %c | word -> %c\n", i, str[i - 1], (*to_expand)->word[i]);
// 		}
// 		else
// 		{
// 			str[index->i] = (*to_expand)->word[index->i];
// 			index->i++;
// 		}
// 	}
// 	str[len] = '\0';
	printf("AFTER EXPAND -> [%s]\n", str);
}

void	expand(t_token **lst, t_quote *state, char **env)
{
	char	**save_env;
	t_token	*tmp;
	t_token	*save;
	t_index	*index;

	index = malloc(sizeof(t_index));
	if (!index)
		return ;
	save_env = copy_env(env);
	tmp = (*lst);
	while (tmp)
	{
		save = tmp;
		if (need_expand(tmp->word))
		{
			tmp = tmp->next;
			state->is_quote = 0;
			state->is_dquote = 0;
			manage_expantion(&save, state, save_env, index);
			// search_in_env(&save, save_env, state);
		}
		else
			tmp = tmp->next;
	}
}
