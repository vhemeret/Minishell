/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:08:27 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/12 16:09:18 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	manage_quote(char c, t_lex **lexer)
{
	if (c == '\'')
	{
			if ((*lexer)->is_quote == 0)
				(*lexer)->is_quote = 1;
			else
				(*lexer)->is_quote = 0;
	}
	else if (c == '\"')
	{
		if ((*lexer)->is_dquote == 0)
			(*lexer)->is_dquote = 1;
		else
			(*lexer)->is_dquote = 0;
	}
}
