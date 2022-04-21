/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/20 05:05:55 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	nb_words(char *cmd_line, t_quote *state)
{
	int	i;
	int	words;

	i = -1;
	words = 0;
	while (cmd_line[++i])
	{
		quoting_state(cmd_line[i], state);
		if (sp_word(cmd_line, i, state) || pipe_word(cmd_line, i, state)
			|| redir_word(cmd_line, i, state)
			|| (cmd_line[i] == '"' && state->is_dquote == 1)
			|| (cmd_line[i] == '\'' && state->is_quote == 1))
		{
			if (cmd_line[i] == '<' && cmd_line[i + 1] && cmd_line[i + 1] == '<')
				while (cmd_line[i + 1] && cmd_line[i + 1] == '<')
					i++;
			else if (cmd_line[i] == '>' && cmd_line[i + 1] && cmd_line[i + 1] == '>')
				while (cmd_line[i + 1] && cmd_line[i + 1] == '>')
					i++;
			else if (cmd_line[i] == '\'' && state->is_quote == 1)
				i += next_squote(&cmd_line[i]);
			else if (cmd_line[i] == '"' && state->is_dquote == 1)
				i += next_dquote(&cmd_line[i]);
			words++;
		}
	}
	return (words);
}

// static char	*put_words_into_tabs(char *cmd_line, t_cmd **cmd, int nb_pipe)
// {
	// char *words;
	// 
// }

void	manage_cmd(char *cmd_line)
{
	t_quote	*state;

	// char	**words;
	// int		tab_index;

	// tab_index = 0;
	state = malloc(sizeof(t_quote));
	if (!state)
		return ;
	state->is_dquote = 0;
	state->is_quote = 0;
	printf("nb words:\t%i\n", nb_words(cmd_line, state));
	//words = malloc(sizeof(char *) * (nb_words(cmd_line, state) + 1));
	//if (!words)
	//	return ;
}
