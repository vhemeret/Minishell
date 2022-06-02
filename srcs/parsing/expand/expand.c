/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/31 17:58:32 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// repère si il y a des var a expandre
static int	need_expand(char *word)
{
	int	i;

	i = -1;
	while (word[++i])
		if (word[i] == '$')
			return (1);
	return (0);
}


static void	basic_expantion(t_token **to_expand, char **save_env, t_quote *state)
{
	(void)save_env;
	(void)state;
	printf("basic_expantion -> %s\n", &(*to_expand)->word[0]);
}

static void	squote_expantion(t_token **to_expand, char **save_env, t_quote *state)
{
	(void)save_env;
	(void)state;
	printf("squote_expantion -> %s\n", &(*to_expand)->word[0]);
}

static void	dquote_expantion(t_token **to_expand, char **save_env, t_quote *state)
{
	(void)save_env;
	(void)state;
	printf("dquote_expantion -> %s\n", &(*to_expand)->word[0]);
}

// repere type déxpantion et envoie a la focntion associé
static void type_expantion(t_token **to_expand, char **save_env, t_quote *state)
{
	int	i;

	i = -1;
	while ((*to_expand)->word[++i])
	{
		quoting_state((*to_expand)->word[i], state);
		if ((*to_expand)->word[i] == '$')
		{
			if (state->is_quote == 1 && state->is_dquote == 0)
				squote_expantion(to_expand, save_env, state);
			else if (state->is_dquote == 1)
				dquote_expantion(to_expand, save_env, state);
			else
				basic_expantion(to_expand, save_env, state);
		}	
	}
}

// copie l'environement | cherche le type de l'expantion 
void	expand(t_token **lst, t_quote *state, char **env)
{
	char	**save_env;
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
			type_expantion(&save, save_env, state);
		}
		else
			tmp = tmp->next;
	}
}