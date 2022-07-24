/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahemere <vahemere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:41 by vahemere          #+#    #+#             */
/*   Updated: 2022/07/23 20:03:55 by vahemere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*####################### LIBRARIES #######################*/

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <limits.h>

/*####################### STRUCTURES #######################*/

extern struct s_all	g_all;

typedef struct s_mem
{
	struct s_mem	*next;
	void			*addr;
}				t_mem;

typedef struct s_exec
{
	char			**envp;
	struct s_env	*envp_lst;
	int				nb_node;
	int				err;
	char			*errchar;
	int				nb_cmd;
	int				on_here_doc;
	int				can_run;
	int				previous_fd;
	struct s_node	*node;
	struct s_node	*node_tmp;
	struct s_token	*token_tmp;
}			t_exec;

typedef struct s_all
{
	t_mem	*g_mem;
	t_exec	*utils;
}				t_all;

typedef struct s_node
{
	int				in;
	int				out;
	int				here_doc_fd;
	char			*here_doc;
	int				has_cmd;
	int				num;
	struct s_node	*next;
}			t_node;

typedef struct s_env
{
	char			*content;
	int				type;
	struct s_env	*next;
}			t_env;

typedef enum s_type
{
	CMD,
	ARG,
	R_IN,
	R_OUT,
	DR_OUT,
	DR_IN,
	FD,
	LIMITOR,
	PIPE,
}			t_type;

typedef struct s_quote
{
	int	is_quote;
	int	is_dquote;
	int	sq_first;
	int	found;
}				t_quote;

typedef struct s_expand
{
	char	*str;
	int		len;
	int		found;
	int		need_expand;
	int		quote;
	int		i;
}				t_expand;

typedef struct s_token
{
	char			*word;
	int				index;
	int				nb_words;
	struct s_token	*next;
	struct s_token	*back;
	enum s_type		type;
}				t_token;

/*####################### PROTOTYPES #######################*/

/*### SIGNAL ###*/

void	handle_sig(void);
void	ctrl_c_here(int sig);
void	ctrl_c(int test);
void	init_all(void);

/*### PARSING ###*/

int		is_word(char *cmd, int i, t_quote *state);
int		end_word(char *cmd, int i, t_quote *state);
/* step token */
void	tokenizer(char **cmd, t_token **lst, int len);
int		is_drout(t_token *tmp);
int		is_drin(t_token *tmp);
int		is_outfile_drout(t_token *save);
int		is_limitor(t_token *save);
int		is_type(t_token *tmp);
/* check_syntax */
int		first_check(char *cmd);
int		check_quote(char *cmd_line, t_quote *state);
int		syntax_check(t_token **lst);
int		print_message(int error);
int		print_message_and_cleaning(int error, t_token **lst);

/* step split */
t_token	*manage_cmd(char *cmd_line, char **env);
int		nb_words(char *cmd, t_quote *state);
int		sep_word(char c);
char	*put_redir_in_tab(char *cmd_line, int *i, char *words);
char	*put_sqword_in_tab(char *cmd_line, int *i, t_quote *state, char *words);
char	*put_dqword_in_tab(char *cmd_line, int *i, t_quote *state, char *words);
char	*put_word_in_tab(char *cmd_line, int *i, t_quote *state, char *words);
char	*put_pipe_in_tab(char *cmd_line, int *i, char *words);
/* expand */
void	expand(t_token **lst, t_quote *state, char **env);
int		search_in_env_len(char *word, char **env, t_quote *state, int *len);
char	*malloc_for_expand(t_token **to_expand, t_quote *state, char **env);
char	*remove_quote(char *old, t_quote *state);
int		sign(char c, t_quote *st);
void	manage_expantion(t_token **expn, t_quote *st, char **nv, t_expand *exp);
int		single_quote_expantion(char *word, t_expand *exp);
int		basic_expantion(char *w, t_expand *exp, char **nv, t_quote *state);
char	**split_word(char *word, t_quote *state);
void	replace_old_node(t_token **old_node, char **to_insert);

	/*###   EXEC  ###*/

char	**get_arg(t_token *token);
void	exec(t_token *token);
void	set_r_in(t_node	*node, t_token *token);
void	set_r_out(t_node *node, t_token *token);
char	**get_path(char **envp);
t_exec	*init_exec(char **envp);
int		nb_cmd(t_token *token);
void	here_doc_init(t_node *node, t_token *token);
t_token	*go_next(t_token *token);
int		get_nb_arg(t_token *token);
void	refresh(t_token *token, t_exec *utils);
t_env	*edit_var_lst(t_exec *utils, char *var, int join);
int		nb_node(t_token *token);
t_node	*ft_lstadd_back(t_node *lst, t_node *new);
void	handle_r_in(t_exec utils, int num);
void	handle_r_out(t_exec utils, int *fd, int num);
int		check_path_exec(char *word, t_exec utils);
char	*get_cmd_path(char *cmd, char **envp);
int		run_built_on_fork(t_token *tk, t_exec *utils);
int		launch_all(int *fd, int *x, pid_t *pid, t_token *token);
pid_t	run(t_token *tk, int *fd, int num, t_exec utils);

	/*###   BUILT IN  ###*/

int		env(t_exec *utils);
int		pwd(char **envp);
int		cd(char *path, t_exec *utils);
int		export(char *var, t_exec **utils);
int		unset(char *var, t_exec *utils);
int		echo(t_token *token);
void	ft_exit(t_exec *utils);
int		manage_built_in1(t_token *token);
int		manage_built_in2(t_token *token);
int		manage_built_in3(t_token *token, t_exec *utils);
int		manage_built_in4(t_token *token);
char	**lst_to_char(t_env *lst);
int		export_run(char *var, t_exec **utils, t_env *tmp, int i);
t_env	*init_lst_env(char **envp, t_exec *utils);
char	**lst_to_char(t_env *lst);
t_env	*ft_envadd_back(t_env *lst, t_env *new);
int		init_env(t_exec *utils, char **envp);
int		manage_built_in(t_token *token, t_exec *utils);
int		is_built_in(t_token *token);
int		pos_equal(char *str);
char	**lst_to_char_env(t_env *lst);
void	print_tab(char **tab);
char	**sort_tab(char **tab, int size);
int		size_tab(char **tab);
void	no_fork(t_token *token, t_exec *utils);
void	free_env(char **envp, int size);
int		check_parsing(char *str);
char	*plus_egale(char *str, char *var, int egale);
t_env	*ft_new_env(char *content);

	/*###  UTILS  ###*/

char	*ft_strdup(char *str);
int		ft_strlen(char *str);
void	quoting_state(char c, t_quote *state);
int		next_dquote(char *cmd);
int		next_squote(char *cmd);
int		next_dquote_len(char *cmd, int i, t_quote *state);
int		next_squote_len(char *cmd, int i, t_quote *state);
int		is_whitespace(char c);
int		pipe_word(char *cmd, int i, t_quote *state);
int		redir_word(char *cmd, int i, t_quote *state);
char	**copy_env(char **env);
char	*ft_strcpy(char *src);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);
int		len_darr(char **arr);
int		isdigits(char c);
int		is_last(t_token *token);
int		ft_atoi(char *str);
void	*ft_malloc(size_t size);
void	ft_free(void *addr);
void	ft_free_all(void);

	/*### CLEANING ###*/
void	free_double_array(char **arr);
int		print_and_free(char *str, t_token **lst);
void	ft_free_node(t_node *node);
void	ft_free_token(t_token *token);
void	clean(t_exec *utils);
void	cleaning_parsing(t_expand *exp, t_quote *state);
t_token	*cleaning_parsing_error(t_quote *state);

#endif
