/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/05/20 19:07:12 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*ret;
	(void)	av;

	if (ac != 1)
	{
		printf("Error:	to many arguments.\n");
		return (1);
	}
	while (1)
	{
		ret = readline("\033[0;35mminishell\033[0m\033[0;32m$>\033[0m ");
		if (ft_strlen(ret) != 0)
		{
			manage_cmd(ret, env);
			if (ret && *ret)
				add_history(ret);
			free(ret);
		}
	}
	return (0);
}
