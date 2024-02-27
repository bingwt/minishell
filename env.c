/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:03:20 by btan              #+#    #+#             */
/*   Updated: 2024/02/27 21:17:02 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_envp(void)
{
	char	**env;

	env = ft_calloc(9, sizeof(char *));
	env[0] = ft_strjoin("USER=", getenv("USER"));
	env[1] = ft_strjoin("HOME=", getenv("HOME"));
	env[2] = ft_strjoin("PWD=", getenv("PWD"));
	env[3] = ft_strjoin("DISPLAY=", getenv("DISPLAY"));
	env[4] = ft_strjoin("TERM=", getenv("TERM"));
	env[5] = ft_strjoin("PATH=", getenv("PATH"));
	env[6] = ft_strjoin("DBUS_SESSION_BUS_ADDRESS=", \
	getenv("DBUS_SESSION_BUS_ADDRESS"));
	env[7] = ft_strjoin("OLDPWD=", getenv("OLDPWD"));
	return (env);
}

void	init_envll(t_list **envp)
{
	t_list	*env;

	env = ft_lstnew(ft_strjoin("USER=", getenv("USER")));
	ft_lstadd_back(envp, env);
	env = ft_lstnew(ft_strjoin("HOME=", getenv("HOME")));
	ft_lstadd_back(envp, env);
	env = ft_lstnew(ft_strjoin("PWD=", getenv("PWD")));
	ft_lstadd_back(envp, env);
	env = ft_lstnew(ft_strjoin("DISPLAY=", getenv("DISPLAY")));
	ft_lstadd_back(envp, env);
	env = ft_lstnew(ft_strjoin("TERM=", getenv("TERM")));
	ft_lstadd_back(envp, env);
	env = ft_lstnew(ft_strjoin("PATH=", getenv("PATH")));
	ft_lstadd_back(envp, env);
	env = ft_lstnew(ft_strjoin("DBUS_SESSION_BUS_ADDRESS=", \
	getenv("DBUS_SESSION_BUS_ADDRESS")));
	ft_lstadd_back(envp, env);
	env = ft_lstnew(ft_strjoin("OLDPWD=", getenv("OLDPWD")));
	ft_lstadd_back(envp, env);
}

char	**list_to_array(t_list *lst)
{
	size_t	len;
	char	**arr;
	size_t	i;

	len = ft_lstsize(lst);
	arr = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (i < len)
	{
		arr[i++] = (char *) lst->content;
		lst = lst->next;
	}
	return (arr);
}

char	**ft_strsplit(char *str, char *token)
{
	char	**strs;
	char	*start;
	char	*end;
	size_t	i;
	
	strs = ft_calloc(3, sizeof(char *));
	start = ft_strnstr(str, token, ft_strlen(str));
	end = start + 1;
	i = 0;
	while ((start[i] == token[i]) && i < ft_strlen(token))
	{
		end++;
		i++;
	}
	strs[0] = ft_substr(str, 0, start - str);
	strs[1] = --end;
	return (strs);
}

char	*ft_strre(char *str, char *find, char *replace)
{
	char	**strs;
	char	*temp;
	char	*new;

	strs = ft_strsplit(str, find);
	temp = ft_strjoin(strs[0], replace);
	new = ft_strjoin(temp, strs[1]);
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
	start = ft_strchr(str, '$');
	if (!start)
		return (str);
	end = start + 1;
	while (ft_isalnum(*end))
		end++;
	token = ft_substr(str, start - str, end - start);
	while (lst)
	{
		env = (char *) lst->content;
		if (!ft_strncmp(token + 1, env, ft_strchr(env, '=') - env))
			break ;
		lst = lst->next;
	}
	if (lst) 
		env = env + (end - start);
	else
		env = "";
	env = ft_strre(str, token, env);
	free(token);
	if (ft_strchr(env, '$'))
		env = expand_env(env, envll);
	return (env);
}
