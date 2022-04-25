/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/04/25 10:53:46 by vahemere         ###   ########.fr       */
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

enum type
{
	CMD, // cmd
	ARG, // argument
	R_IN, // <
	R_OUT, // >
	DR_OUT, // >>
	DR_IN, // << (HERE_DOC)
	INFILE,	// word following <
	OUTFILE, // word following >
	LIMITOR, // word following <<
	OUTFILE_DROUT, // word following >>
};

typedef struct s_quote
{
	int	is_quote;
	int	is_dquote;
}	t_quote;

/*####################### PROTOTYPES #######################*/

	/*### PARSING ###*/
void	manage_cmd(char *cmd_line);
int		pars_cmd_line(char *cmd_line);

	/*###   EXEC  ###*/

	/*###  UTILS  ###*/
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
void	quoting_state(char c, t_quote *state);
int		next_dquote(char *cmd);
int		next_squote(char *cmd);
int		next_dquote_len(char *cmd);
int		next_squote_len(char *cmd);
int		is_whitespace(char c);
int		sp_word(char *cmd, int i, t_quote *state);
int		pipe_word(char *cmd, int i, t_quote *state);
int		redir_word(char *cmd, int i, t_quote *state);

	/*### CLEANING ###*/
void	free_double_array(char **arr);

#endif