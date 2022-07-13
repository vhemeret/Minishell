/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 02:04:19 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/12 02:33:06 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo(t_token *token, t_exec *utils)
{
	char	**args;
	int		nb_arg;
	int		n;
	int		i;

	n = 0;
	(void)(utils);
	nb_arg = get_nb_arg(token);
	if (nb_arg <= 1)
	{
		printf("\n");
		return (0);		
	}
	args = get_arg(token);
	if (!strcmp(args[1], "-n"))
		n = 1;
	i = n;
	while (++i < nb_arg)
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		else if (n && i == nb_arg - 1 && *(args[i] + ft_strlen(args[i]) - 1) != '\n')
			printf("%%");
	}
	if (!n)
		printf("\n");
	return (0);
}