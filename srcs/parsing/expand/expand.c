/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/17 23:18:12 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	need_expand(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
		if (word[i] == '$' || word[i] == '"' || word[i] == '\'')
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
				if ((word[k] == '\0' || word[k] == '\'' || word[k] == '"' || word[k] == '$') && save_env[i][j] && j != 0 && save_env[i][j] == '=')
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

int	single_quote_expantion(char *word, t_expand *exp)
{
	int	i;

	i = -1;
	while (word[++i] && word[i] != '\'')
		exp->str[exp->len++] = word[i];
	return (i);
}

int	basic_expantion(char *w, t_expand *exp, char **nv)
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
			if ((w[i] == '\0' || w[i] == '\'' || w[i] == '$'|| w[i] == '"')
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
			while (w[i] != '\0' && w[i] != '\'' && w[i] != '"' && w[i] != '$')
				i++;
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

void	 add_back_new_node(char **to_insert, t_token *back, t_token *next, int len)
{
	int		i;
	t_token	*tmp;
	
	i = 0;
	while (++i < len)
	{
		tmp = malloc(sizeof(t_token) * (1));
		if (!tmp)
			return ;
		if (back)
			back->next = tmp;
		if (next)
			next->back = tmp;
		tmp->back = back;
		tmp->next = next;
		tmp->type = ARG;
		tmp->word = ft_strdup(to_insert[i]);
		back = tmp;
	}
}

void	insert_new_node(char **to_insert, t_token *back, t_token *next, int len)
{
	t_token	*tmp;

	printf("ici\n");
	tmp = malloc(sizeof(t_token) * (1));
	if (!tmp)
		return ;
	if (back)
	{
		back->next = tmp;
		if (back->type == CMD)
			tmp->type = ARG;
		else
			tmp->type = CMD;
	}
	else
		tmp->type = CMD;
	if (next)
		next->back = tmp;
	tmp->next = next;
	tmp->back = back;
	printf("%s\n", next->word);
	tmp->word = ft_strdup(to_insert[0]);
	printf("%s\n", tmp->word);
	back = tmp;
	if (len > 1)
		add_back_new_node(to_insert, back, next, len);
}

void	replace_old_node(t_token **old_node, char **to_insert)
{
	int	len;
	t_token	*back;
	t_token	*next;

	len = len_darr(to_insert);
	back = (*old_node)->back;
	next = (*old_node)->next;
	if ((*old_node)->nb_words == 1)
	{
		free((*old_node)->word);
		(*old_node)->word = ft_strdup(to_insert[0]);
		if (len > 1)
		{
			back = (*old_node);
			add_back_new_node(to_insert, back, next, len);
		}
		return ;
	}
	else
	{
		free((*old_node)->word);
		// (*old_node)->word = NULL;
		// free((*old_node));
		// (*old_node) = NULL;
		(*old_node)->word = ft_strdup(to_insert[0]);
		insert_new_node(to_insert, back, next, len);
	}
}

void	manage_expantion(t_token **to_expand, t_quote *state, char **env, t_expand *exp)
{	
	int		i;
	char	**expanded;

	i = -1;
	exp->len = 0;
	exp->str = malloc_for_expand(to_expand, state, env);
	if (!exp->str)
		return ;
	while ((*to_expand)->word[++i])
	{
		quoting_state((*to_expand)->word[i], state);
		if ((*to_expand)->word[i] == '$')
		{
			if (state->is_quote == 1 && state->is_dquote == 0)
				i += single_quote_expantion(&(*to_expand)->word[i], exp) - 1;
			else
				i += basic_expantion(&(*to_expand)->word[i], exp, env) - 1;
		}
		else
			exp->str[exp->len++] = (*to_expand)->word[i];
	}
	exp->str[exp->len] = '\0';
	expanded = split_word(exp->str, state);
	free(exp->str);
	exp->str = NULL;
	replace_old_node(to_expand, expanded);
}

int	quoting_check(t_token **to_check, t_quote *state)
{
	int	need_expand;
	char **arr;
	int	quote;
	int	i;

	need_expand = 0;
	quote = 0;
	i = -1;
	while ((*to_check)->word[++i])
	{
		if ((*to_check)->word[i] == '$')
			need_expand = 1;
		if ((*to_check)->word[i] == '"' || (*to_check)->word[i] == '\'')
			quote = 1;
	}
	if (need_expand == 1)
		return (1);
	else if (need_expand == 0 && quote == 1)
	{
		arr = split_word((*to_check)->word, state);
		replace_old_node(to_check, arr);
	}
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
		if (need_expand(tmp->word))
		{
			tmp = tmp->next;
			state->is_quote = 0;
			state->is_dquote = 0;
			if (quoting_check(&save, state))
				manage_expantion(&save, state, save_env, exp);
		}
		else
			tmp = tmp->next;
	}
	tmp = (*lst);
	char	*types[8] = {"CMD", "ARG", "R_IN", "R_OUT", "DR_IN", "DR_OUT", "FD", "PIPE"};
	while (tmp)
	{
		printf("\033[31;01m\t[%s]\033[00m \033[32;01m|\033[00m \033[33;01m[%s]\033[00m\n", tmp->word, types[tmp->type]);
		tmp = tmp->next;
	}
	free(exp);
	exp = NULL;
}
