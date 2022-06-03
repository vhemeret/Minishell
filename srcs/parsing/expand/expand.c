/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:31:55 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/03 16:55:21 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// //repère si il y a des var a expandre
// static int	need_expand(char *word)
// {
// 	int	i;

// 	i = -1;
// 	while (word[++i])
// 		if (word[i] == '$')
// 			return (1);
// 	return (0);
// }

// // coupe uniquement la variable a expend
// char	*cut_var(char *word, t_quote *state)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*var;

// 	i = 0;
// 	while (word[i] && word[i] != '$')
// 		i++;
// 	j = i;
// 	while (word[j] && (word[j] != '"' || word[j] != '\'' || word[j] != '$' || word[j] != ' '))
// 		j++;
// 	var = malloc(sizeof(char) * ((j - i) + 1));
// 	if (!var)
// 		return (NULL);
// 	k = 0;
// 	j = i;
// 	while (word[j] && (word[j] != '"' || word[j] != '\'' || word[j] != '$' || word[j] != ' '))
// 		var[k++] = word[j++];
// 	var[k] = '\0';
// 	return (var);
// }

// // retourne une variable expand
// char	*search_in_env(char *word, char *save_env, t_quote *state)
// {
// 	int		i;
// 	int		j;
// 	char	*var;
// 	char	*ret;

// 	i = -1;
// 	var = cut_var(word, state);
// 	while (save_env[++i])
// 	{
// 		j = 0;
// 		if (var[j] = save_env[j])
// 		{
// 			while (var[j] && save_env[j] && save_env[j] != '=' && var[j] == save_env[j])
// 				j++;
// 			if (var[j] == '\0' && save_env[j] && j != 0 && save_env[j] == '=')
// 				ret = ft_strcpy(&save_env[j + 1]);
// 		}
// 	}
// 	free(var);
// 	var = NULL;
// 	return (ret);
// }



// // copie l'environement | cherche le type de l'expantion 
// void	expand(t_token **lst, t_quote *state, char **env)
// {
// 	char	**save_env;
// 	char	**tab;
// 	t_token	*tmp;
// 	t_token	*save;

// 	save_env = copy_env(env);
// 	tmp = (*lst);
// 	while (tmp)
// 	{
// 		save = tmp;
// 		if (need_expand(tmp->word))
// 		{
			
// 			tmp = tmp->next;
// 			state->is_quote = 0;
// 			state->is_dquote = 0;
// 			// replace(&save, save_env, state);
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// }
