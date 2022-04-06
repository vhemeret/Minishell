/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/06 18:32:44 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd_test(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		printf("cmd[%i]\t==>\t%s\n", i, cmd[i]);
	printf("\n\n");
}

int	main(int ac, char **av, char **env)
{
	char	*ret;
	char	**cmd;
	int		i;
	(void)	av;
	(void)	env;

	i = -1;
	if (ac != 1)
		return (1);
	while (1)
	{
		ret = readline("\033[0;35mMinishell\033[0m\033[0;32m$>\033[0m ");
		if (ft_strlen(ret) != 0)
		{
			printf("%s\n", ret);
			while (ret[++i])
			{
				if (ret[i] != '|')
				{
					cmd = get_cmd(&ret[i]);
					print_cmd_test(cmd);
					free_double_array(cmd);
					while (ret[i] && ret[i + 1] != '|')
						i++;
				}
			}
		}
		free(ret);
	}
	return (0);
}