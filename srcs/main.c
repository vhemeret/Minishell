/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:25 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/10 18:14:43 by vahemere         ###   ########.fr       */
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
	t_lex	*lexer;
	(void)	av;
	(void)	env;

	if (ac != 1)
		return (1);
	while (1)
	{
		ret = readline("\033[0;35mMinishell\033[0m\033[0;32m$>\033[0m ");
		if (ft_strlen(ret) != 0)
		{
			get_cmd(ret, &lexer);
		}
		free(ret);
	}
	return (0);
}