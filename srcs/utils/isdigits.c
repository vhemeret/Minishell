/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:srcs/utils/len_darr.c
/*   len_darr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:30:51 by vahemere          #+#    #+#             */
/*   Updated: 2022/06/22 14:24:13 by vahemere         ###   ########.fr       */
========
/*   isdigits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:33:46 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/01 02:34:11 by vahemere         ###   ########.fr       */
>>>>>>>> 9c2f618873acfc99cbd6b8344dbba68cf862ad5e:srcs/utils/isdigits.c
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

<<<<<<<< HEAD:srcs/utils/len_darr.c
int	len_darr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
========
int	isdigits(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
>>>>>>>> 9c2f618873acfc99cbd6b8344dbba68cf862ad5e:srcs/utils/isdigits.c
}
