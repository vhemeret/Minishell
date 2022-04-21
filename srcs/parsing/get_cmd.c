/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:23:06 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/14 13:37:52 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*until_pipe(char *cmd_line)
{
	int	i;

	i = 0;
	if (cmd_line)
	{
		while (cmd_line[i])
		{
			if (cmd_line[i + 1] && cmd_line[i] == '|')
				return (&cmd_line[i + 1]);
		}
	}
	return (NULL);
}

static void	init_node_lexer(char *cmd_line, t_lex **lexer, int nb_pipe)
{
	(*lexer)->cmd;
	
	if (nb_pipe = 0)
	{
		(*lexer)->is_quote = 0;
		(*lexer)->is_dquote = 0;
		manage_arg_tab(lexer, cmd_line);
		// remplir les args
		// init le reste
	}
	else
	{
		(*lexer)->is_quote = 0;
		(*lexer)->is_dquote = 0;
		manage_arg_tab(lexer, cmd_line);
	}
}

static void	create_node(char *cmd_line, t_lex **lexer, int nb_pipe)
{
	t_lex *tmp;
	int		i;

	i = -1;
	tmp = (*lexer);
	while (++i < nb_pipe + 1)
	{
		tmp->next = malloc(sizeof(t_lex));
		if (!tmp->next)
			return (NULL);
		tmp = tmp->next;
		if (i == 0)
			init_node_lexer(cmd_line, &tmp, nb_pipe);
		else
		{
			cmd_line = until_pipe(cmd_line);
			init_node_lexer(cmd_line, &tmp, nb_pipe);
		}
	}
	tmp->next = NULL;
}

void	get_cmd(char *cmd_line, t_lex **lexer)
{
	int		nb_pipe;
	t_lex	*tmp;
	
	nb_pipe = check_pipe(cmd_line);
	*lexer = malloc(sizeof(t_lex));
	if (!lexer)
		return ;
	if (nb_pipe == 0)
	{
		(*lexer)->next = NULL;
		init_node_lexer(cmd_line, lexer, nb_pipe);
		return ;
	}
	else
		create_node(cmd_line, lexer, nb_pipe);	
}
