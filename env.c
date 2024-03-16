/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:03:20 by btan              #+#    #+#             */
/*   Updated: 2024/03/17 01:58:27 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_encased(char *str, char token, char cap)
{
	if (ft_strchr(str, cap))
	{
		str = ft_strchr(str, cap);
		if (ft_strchr(str, token))
		{
			str = ft_strchr(str, token);
			if (ft_strchr(str, cap))
				return (1);
		}
	}
	return (0);
}

static t_list	*find_token(t_list *lst, char **env, char *token)
{
	char	*temp;

	while (lst)
	{
		*env = (char *) lst->content;
		temp = ft_substr(*env, 0, ft_strchr(*env, '=') - *env);
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

char	*expand_env(char *str, t_list *envll)
{
	t_list	*lst;
	char	*start;
	char	*end;
	char	*token;
	char	*env;

	lst = envll;
	start = ft_strchr(str, '$');
	if (!start || (is_encased(str, '$', '\'')))
		return (str);
	end = start + 1;
	while (ft_isalnum(*end) || *end == '?')
		end++;
	token = ft_substr(str, start - str, end - start);
	if (find_token(lst, &env, token))
		env = env + (end - start);
	else
		env = "";
	if (!ft_strcmp(token, "$"))
		env = "$";
	if (!ft_strncmp(token, "$?", 2))
	{
		env = ft_itoa(get_exit_status(-1));
		free(token);
		token = ft_strdup("$?");
	}
	env = ft_strre(str, token, env);
	if (ft_strchr(env, '$') && ft_strcmp(token, "$"))
		env = expand_env(env, envll);
	free(token);
	return (env);
}

void	set_shlvl(t_list **envll)
{
	char	*prev;
	char	*new;

	prev = expand_env("$SHLVL", *envll);
	new = ft_itoa(ft_atoi(prev) + 1);
	ft_export(ft_strjoin("exportSHLVL=", new), envll);
	free(prev);
	free(new);
}