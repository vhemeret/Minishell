/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/04 04:19:02 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//repère si il y a des var a expandre
static int	need_expand(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
		if (word[i] == '$')
			return (1);
	return (0);
}

int	search_in_env_len(char *word, char **save_env, t_quote *state)
{
	int		i;
	int		j;
	int		k;
	int		len;

	i = -1;
	if (state->is_quote == 1 && state->is_dquote == 0)
	{
		while (word[++i] && word[i] != '\'')
			len++;
		return (len);
	}
	else
	{
		while (save_env[++i])
		{
			j = 0;
			k = 1;
			if (word[k] == save_env[j])
			{
				while (word[k++] && save_env[j] && save_env[j] != '=' && word[k] == save_env[j])
					j++;
				if ((word[k] == '\0' || word[k] == '\'' || word[k] == '"') && save_env[j] && j != 0 && save_env[j] == '=')
				{
					if (save_env[++j] == '\0')
						return (1);
					while (save_env[++j])
						len++;
					return (len);
				}
			}
		}
	}
	return (0);
}

int	search_in_env(char **str, char *word, char *save_env, t_quote *state)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	if (state->is_quote == 1 && state->is_dquote == 0)
	{
		while (word[++i] && word[i] != '\'')
			*str[i] = word[i];
		return (i);
	}
	else
	{
		while (save_env[++i])
		{
			j = 0;
			k = 1;
			if (word[k] == save_env[j])
			{
				while (word[k++] && save_env[j] && save_env[j] != '=' && word[k] == save_env[j])
					j++;
				if ((word[k] == '\0' || word[k] == '\'' || word[k] == '"') && save_env[j] && j != 0 && save_env[j] == '=')
				{
					if (save_env[++j] == '\0')
					{
						*str[i] = '$';
						return (i + 1);
					}
					while (save_env[++j])
						*str[i++] = save_env[j];
					return (i);
				}
			}
		}
	}
	return (0);
}

void	test(t_token **to_expand, t_quote *state, char **env)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	i = -1;
	while ((*to_expand)->word[++i])
	{
		quoting_state((*to_expand)->word[i], state);
		if ((*to_expand)->word[i] == '$')
				len += search_in_env_len(&(*to_expand)->word[i], env, state);
		else
			len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return ;
	i = -1;
	while ((*to_expand)->word[++i])
	{
		quoting_state((*to_expand)->word[i], state);
		if ((*to_expand)->word[i] == '$')
				i += search_in_env(&str[i], &(*to_expand)->word[i], env, state) - 1;
		else
			str[i] = (*to_expand)->word[i];
	}
	str[i] = '\0';
	printf("AFTER EXPAND -> [%s]\n", str);
}

// copie l'environement | cherche le type de l'expantion 
void	expand(t_token **lst, t_quote *state, char **env)
{
	char	**save_env;
	char	**tab;
	t_token	*tmp;
	t_token	*save;

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
			test(&save, state, save_env);
		}
		else
			tmp = tmp->next;
	}
}
