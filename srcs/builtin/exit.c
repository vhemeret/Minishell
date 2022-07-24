/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:47:02 by brhajji-          #+#    #+#             */
/*   Updated: 2022/07/23 16:54:25 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_atoi(char *str)
{
	unsigned int	i;
	int				signe;
	int				result;

	signe = 1;
	i = 0;
	result = 0;
	while (str[i] == 9 || (str[i] >= 10 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	i--;
	while (str[++i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if (signe > 0 && i >= 25)
			return (-1);
		else if (signe < 0 && i >= 26)
			return (0);
	}
	return (result * signe);
}

void	ft_exit(t_exec *utils)
{
	int	x;

	x = utils->err;
	clean(utils);
	ft_free_all();
	exit(x);
}
