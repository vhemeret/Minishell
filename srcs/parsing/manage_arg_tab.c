/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:43:20 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/14 11:43:35 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	malloc_tab(t_lex **lexer, char *cmd_line)
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

static int	malloc_arg_tab(t_lex **lexer, char *cmd_line)
{
	int	i;
	int	j;
	int	tab_index;

	i = -1;
	j = 0;
	tab_index = 0;
	while (cmd_line[++i] && cmd_line[i] != '|')
	{
		manage_quote(cmd_line[i], lexer);
		if ((i == 0 && !is_whitespace(cmd_line[i]))
			|| (is_whitespace(cmd_line[i]) && !is_whitespace(cmd_line[i + 1]))
			&& !(*lexer)->is_quote && !(*lexer)->is_dquote)
			j++;
	}
	return (j);
}

static void	put_arg_into_tab(t_lex **lexer, char *cmd_line)
{
	
}

void	manage_arg_tab(t_lex **lexer, char *cmd_line, int nb_pipe)
{
	int	size;
	
	size = malloc_tab(lexer, cmd_line);
	if ((*lexer)->is_quote == 1 || (*lexer)->is_dquote == 1)
	{
		//
		return ;
	}
	(*lexer)->args = malloc(sizeof(char *) * (size + 1));
	if (!(*lexer)->args)
		return ;
	put_arg_into_tab(lexer, cmd_line);
}