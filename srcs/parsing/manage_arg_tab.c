/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:43:20 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/12 17:28:58 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	malloc_arg_tab(t_lex **lexer, char *cmd_line)
{
	int	arg;
	int	i;

	i = -1;
	arg = 0;
	while (cmd_line[++i] && cmd_line[i] != '|')
	{
		manage_quote(cmd_line[i], lexer);
		if (cmd_line[i + 1])
		{
			if ((i == 0 && !is_whitespace(cmd_line[i]))
				|| (is_whitespace(cmd_line[i]) && !is_whitespace(cmd_line[i + 1]))
				&& !(*lexer)->is_quote && !(*lexer)->is_dquote)
				arg++;
		}
	}
	return (arg);
}

void	manage_arg_tab(t_lex **lexer, char *cmd_line, int nb_pipe)
{
	if (syntax_error(cmd_line))
	{
		printf("minishell:	syntax error quote or double quote was not closed\n");
		
	}
		
		malloc_arg_tab(lexer, cmd_line);
}