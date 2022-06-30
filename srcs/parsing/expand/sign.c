/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:07:52 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/30 04:01:38 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//si sign : : = % ^ + ~ / renvoyer tel quel
//ne pas expendre lorsque chiffre apres le dollard

#include "../../../minishell.h"

int	sign(char c, t_quote *st)
{
	if (c)
	{
		if (c == ':' || c == '=' || c == '%' || c == '^' || c == '+' || c == '~'
			|| c == '/' || c == '?' || c == ' '
			|| ((c == '"' || c == '\'') && st->is_dquote == 1)
			|| c == ']' || c == '@')
			return (1);
	}
	return (0);
}

int	isdigits(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
