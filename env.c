/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:03:20 by btan              #+#    #+#             */
/*   Updated: 2024/03/19 17:07:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_squote(char *str)
{
	// char	*start;
	char	*end;
	while (*str)
	{
		if (*str == '$' && *(str + 1) != '\0')
			break ;
		if (*str == '"')
		{
			end = ft_strchr(str + 1, '"');
			if (ft_strchr(str, '$') < end)
				str = ft_strchr(str, '$');
			break;
		}
		if (*str == '\'')
			str = ft_strchr(str + 1, '\'');
		if (!str || !*str)
			break ;
		str++;
	}
	return (str);
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

char	*replace_token(char *str, char *find, char *replace)
{
	char	*start;
	char	*new;
	char	*temp;

	start = skip_squote(str);
	if (!start || !*start)
		return (str);
	new = ft_substr(str, 0, start - str);
	temp = ft_strjoin(new, replace);
	free(new);
	new = ft_strjoin(temp, start + ft_strlen(find));
	free(temp);
	return (new);
}

char	*expand_env(char *str, t_list *envll)
{
	t_list	*lst;
	char	*start;
	char	*end;
	char	*token;
	char	*env;

	lst = envll;
	start = skip_squote(str);
	if (!start || !*start)
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
	env = replace_token(str, token, env);
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