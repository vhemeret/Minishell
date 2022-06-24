/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:43:02 by brhajji-          #+#    #+#             */
/*   Updated: 2022/06/16 15:43:09 by brhajji-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*convert(int n, int taille, int signe)
{
	char			*str;
	unsigned int	x;

	str = malloc(sizeof(char) * (taille + 1));
	if (!str)
		return (NULL);
	if (signe)
	{
		*str = '-';
		x = -n;
	}
	else
		x = n;
	str[taille] = '\0';
	taille--;
	while (taille >= signe)
	{
		str[taille] = (x % 10) + 48;
		x = x / 10;
		taille--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		taille;
	int		temp;
	int		signe;

	taille = 0;
	signe = 0;
	if (n < 0)
	{
		taille++;
		signe++;
	}
	temp = n;
	while (temp != 0)
	{
		temp = temp / 10;
		taille++;
	}
	if (n == 0)
		taille++;
	return (convert(n, taille, signe));
}