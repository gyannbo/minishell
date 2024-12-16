/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:18:41 by msloot            #+#    #+#             */
/*   Updated: 2024/12/16 23:01:11 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# define BIN_NAME	"minishell: "

# define EX_ERR	!EX_OK

# include "../libft/inc/libft.h"

# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sysexits.h>


typedef struct s_skip_tok
{
	bool	end;
	bool	skip;
	char	*s;
}t_skip_tok;

typedef struct s_tab_redpip
{
	int			i;
	bool	valid;
	t_skip_tok *tab;
}t_tab_redpip;

typedef struct s_other
{
	size_t	i;
	bool	end;
	bool	betw_q;
	int		y;
}t_other;

typedef struct s_quote
{
	int		x;
	int		y;
	int		z;
	bool	two_type;
	int		count[50];
	char	type;
	char	first_type;
	int		*tab;
	int		q_before_tok;
	int		has_b_tok;
	int		decr_tab;
	int		pos;
	size_t	new_tok_size;
	int		count_next_quote;
	int		temp_c_n_quote;
}t_quote;

typedef struct s_values
{
	int		isquote;
	int		redpip_counter;
	char	**env;
	char	*cmd_str;
	char	*cmd_str_b;
	char	*abs_path_bin;
	char	**expand_pointer;
	char	**split_s;
	char	**tokenized_str;
	int		prev_ret_val;
	int		db_var_count;
	bool	just_a_check;
}t_values;

typedef struct s_var
{
	bool		sec_valid_q;
	int			temp;
	char		temp_type;
	int			temp_z;
	t_values	*v;
}t_var;

typedef struct s_has_type
{
	size_t	i;
	bool	flag;
	int		temp_z;
	int		temp_value;
	int		*q_cnter;	
}t_has_type;

typedef struct s_copy_outside
{
	size_t	i;
	int		y;
	bool	betw_q;
	bool	end;
	bool	sec_valid_q;
	int		temp;
	char	temp_type;
	int		temp_z;
	int		x;
	char	*new_tok;
}t_copy_outside;

typedef struct s_next_i
{
	size_t	i;
	size_t	size;
	char	type;
	size_t	temp;
	int		ret;
}t_next_i;

// parsing //
bool	handle_cmd_str(t_values *values);
bool	parse(t_values *values);
bool	check_quote(t_values *v, char *s);

// expand //
bool	expand(t_values *v);
char	*get_var(char *s, size_t *size);
bool	put_in_string(char **s, char *var, size_t *pos, int s_n_var);
size_t	get_len_till_eq(char *s);
int		do_retval(t_values *v, char *s, size_t *i);
bool	do_put_in_string(t_values *v, char *var, size_t *i, int size_name_var);
char	*get_expand(char *s);
bool	check_var_exist(t_values *v, char *var, size_t *index);
bool	cut_dollar(t_values *v, size_t *i);
bool	do_expand(t_values *v, char *s, size_t *i);

// redir and pipes //
bool	redpip_token_counter(t_values *values);
void	quote_redpip(char *s, size_t *index);
bool	is_redir(t_values *v, char *s, size_t *step);
int		is_redpip(char c);
bool	redir_case_equal(t_values *v, char*s, size_t *step);
bool	redir_case_r_n_s(t_values *v, char *s, size_t *step);

// quote parsing //
bool	quote_parsing(t_values *values, int	*tab);
bool	check_quote(t_values *v, char *s);
bool	if_pass_check(char c, int *tab, t_quote *q);
int		next_pos(t_values *v, t_quote *q, int x, int y);
size_t	get_right_pos(t_values *v, int *count, char type);
size_t	get_next_i(t_values *v, size_t c_nxt_q, size_t *cal_r_s, t_quote *q);
void	manage_count(t_values *v, t_quote *q);
void	increment_q_counter_w_tab(int *counter, t_quote *q);
void	manage_tab(t_quote *q);
void	before_tok(t_quote *q, size_t *i, int *quote_counter, char *s);
void	skip_non_v_quote(char *s, int *tmp_value, int *q_counter, size_t *i);

// quote resolving //
bool	do_quotes(t_values *values);
bool	manage_q_tok(t_values *v, t_quote *q);
void	copy_in_tok(t_values *v, char *s, int x, t_quote *q);
void	manage_rest_tok(t_values *v, char *new_tok, t_quote *q);

// quote expand //
bool	quote_expand(t_values *v);
void	check_for_invalid_envvar(t_values *v, size_t *i, size_t *i_tab);
int		d_manage_quote(t_values *v, size_t *i, size_t *i_tab);
void	check_special_char(t_values *v, size_t *i, int *tab);
bool	do_quote_expand(t_values *v, int *tab);
void	quote_redpip_tab_amt(char *s, size_t *index, size_t *tab_amt);
void	check_for_singles(t_values *v, size_t *i, size_t *i_tab, int **tab);
char	*get_prev_name(t_values *v);

// tokenise redpip //
bool	tokenise_redpip(t_values *v);
bool	tab_redir_case_equal(char*s, size_t *step, t_tab_redpip *tab_redpip);
bool	tab_redir_case_r_n_s(char *s, size_t *step, t_tab_redpip *tab_redpip);
bool	tab_quote_redpip(t_values *v, char *s, size_t *index, t_tab_redpip *tab_redpip);
int		tab_is_redpip_valid(char *s, size_t *step, t_tab_redpip *tab_redpip);
bool	allocate_string(char *s, int amount, t_tab_redpip *tab_redpip);
bool	tab_is_redir(char *s, size_t *step, t_tab_redpip *tab_redpip);

//directory functions //
char	*search_for_dir(t_values *values, char	**env_paths, char *executable);
char	*check(t_values *values, char *path);

// get_path_utils //
bool	compare_exec_to_entry(char *executable, char *entry, DIR *directory);
void	free_cut_n_close_dir(char **cut, DIR *directory);
bool	separate(char ***result, char *executable, int temp);
char	*set_ret_val(t_values *values);
char	*is_dir(t_values *values, char *path);
void	handl_z(int x);

// path_splitting //
char	*get_abs_path(t_values *values);

// signals //
int		set_sig_handler(void);

// exec //
int		exec(t_values *values);
bool	exec_builtin(t_values *v);

// builtins //
int		builtin(size_t argc, char **argv, char **envp);
int		echo(size_t argc, char **argv, char **envp);
int		cd(size_t argc, char **argv, char **envp);
int		env(char **envp);
int		pwd(void);

// error_msg //
void	error(const char *err_src, const char *msg);

// norm //
int		next_q_exist(t_quote *q);
int		y_eq_pos(t_quote *q, t_var *var, t_other *other);
int		next_pos(t_values *v, t_quote *q, int x, int y);
int		at_begin(t_quote *q, char *s);
int		if_pos(t_quote *q, t_copy_outside *data);
int		if_type_is_i(t_values *v, t_next_i *d, size_t *c_n_q, size_t *c_r_s);
void	set_variables(t_values *v, t_quote *q, t_var *var, t_other *other);
void	when_eq_type(char type, size_t *sec_q, int *count);
void	temp_at_return(t_quote *q, t_var *var);
void	type_n_sec_valid_true(t_quote *q, t_var *var, t_other *other, int x);
void	do_loop(t_quote *q, t_var *var, t_other *other, int x);
void	at_exit_free_useless(t_values *v, t_quote *q, int l_v_t, char *n_tok);
void	set_struct(t_has_type *data, t_quote *q, int *q_cnter);
void	if_type(t_quote *q, char *s, size_t i, char *type);
void	do_loop_has_type(t_quote *q, t_has_type *data, char *s, char *type);
void	eq_type_n_next_q(t_values *v, t_quote *q, char *type, size_t *i);
void	init_struct(t_copy_outside *data, t_quote *q, char *new_tok, int x);
void	untemp_at_exit(t_quote *q, t_copy_outside *d, size_t *c_right_size);
void	if_betw_q_false(t_values *v, t_quote *q, t_copy_outside *data);
void	if_t_sec_valid(t_values *v, t_quote *q, t_copy_outside *d, size_t *c);
void	init_struct_next_i(t_values *v, t_next_i *data, t_quote *q);

#endif
