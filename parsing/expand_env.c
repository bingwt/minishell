/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:08:51 by xlow              #+#    #+#             */
/*   Updated: 2024/04/03 18:02:25 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*find_token(t_list *envll, char **new, char *token)
{
	t_list	*lst;
	char	*temp;

	lst = envll;
	while (lst)
	{
		*new = (char *) lst->content;
		temp = ft_substr(*new, 0, ft_strchr(*new, '=') - *new);
		if (!ft_strcmp(token + 1, temp))
		{
			free(temp);
			break ;
		}
		lst = lst->next;
		free(temp);
	}
	return (lst);
}

static char	*assign_new_token(t_string token, t_list *envll)
{
	char	*new_token;

	if (token.i == 2 && ft_isdigit(token.s[1]))
		new_token = "";
	else if (find_token(envll, &new_token, token.s))
		new_token = new_token + token.i;
	else if (!ft_strcmp(token.s, "$"))
		new_token = "$";
	else if (!ft_strncmp(token.s, "$?", 2))
		new_token = ft_itoa(get_exit_status(-1));
	else
		new_token = "";
	return (new_token);
}

static t_string	get_token(t_string token, char **input, t_list *envll)
{
	char	*new_token;

	cmd_assign(&token, **input);
	(*input)++;
	while (ft_isalnum(**input) || **input == '_' || **input == '?')
	{
		if (**input == '?' && token.i == 1)
		{
			cmd_assign(&token, **input);
			(*input)++;
			break ;
		}
		else if (**input == '?')
			break ;
		cmd_assign(&token, **input);
		(*input)++;
		if (ft_isdigit(token.s[1]) && token.i == 2)
			break ;
	}
	new_token = assign_new_token(token, envll);
	free(token.s);
	token.s = ft_strdup(new_token);
	return (token);
}

char	*expand_env(char *input, t_list *envll)
{
	t_string	res;
	t_string	token;

	res.i = 0;
	token.i = 0;
	res.s = ft_calloc(1, 1);
	token.s = ft_calloc(1, 1);
	while (*input)
	{
		quotes(*input, NULL);
		if (quotes('\0', NULL) != 1 && *input == '$')
		{
			token = get_token(token, &input, envll);
			res.s = ft_strjoin_free(res.s, token.s, res.s);
			token.i = 0;
			res.i = ft_strlen(res.s);
		}
		else
		{
			cmd_assign(&res, *input);
			input++;
		}
	}
	free(token.s);
	quotes('\0', "reset");
	return (res.s);
}

void	set_shlvl(t_list **envll)
{
	char	*prev;
	char	*new;
	char	**temp;

	prev = expand_env("$SHLVL", *envll);
	new = ft_itoa(ft_atoi(prev) + 1);
	temp = ft_calloc(3, sizeof(char *));
	temp[0] = "export";
	temp[1] = ft_strjoin("SHLVL=", new);
	ft_export(temp, envll);
	free(prev);
	free(new);
	free(temp[1]);
	free(temp);
}

/*
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	t_list	*envll;
	char	*p;

	envll = NULL;
	array_to_list(&envll, env);
	p = expand_env(argv[1], envll);
	ft_lstclear(&envll, free);
	printf("%s\n", p);
}
*/
