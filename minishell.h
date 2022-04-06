/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/06 18:21:51 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*####################### LIBRARIES #######################*/

# include <stdio.h> 
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/*####################### STRUCTURES #######################*/


typedef struct s_data
{
	int	is_quote;
	int	is_dquote;
}				t_data;


/*####################### PROTOTYPES #######################*/

	/*### PARSING ###*/
char	**get_cmd(char *cmd);

	/*###   EXEC  ###*/
	
	/*###  UTILS  ###*/
int		ft_strlen(char *str);
int		check_pipe(char *cmd);

	/*### CLEANING ###*/
void	free_double_array(char **arr);

#endif