/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 02:04:19 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/19 00:20:53 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_flag(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] && av[i][j] == '-')
		{
			if (av[i][j + 1])
				j++;
			while (av[i][j] && av[i][j] == 'n' && av[i][j] != ' ')
				j++;
			if (av[i][j] != '\0')
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

void	print_echo(int i, int nb_arg, int n, char **args)
{
	while (i < nb_arg)
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		else if (n && i == nb_arg - 1
			&& *(args[i] + ft_strlen(args[i]) - 1) != '\n')
			printf("%%");
		i++;
	}
	if (!n)
		printf("\n");
}

int	echo(t_token *token)
{
	char	**args;
	int		nb_arg;
	int		n;
	int		i;

	n = 0;
	nb_arg = get_nb_arg(token);
	if (nb_arg <= 1)
	{
		printf("\n");
		return (0);
	}
	args = get_arg(token);
	i = check_flag(args);
	if (i > 1)
		n = 1;
	print_echo(i, nb_arg, n, args);
	return (0);
}
