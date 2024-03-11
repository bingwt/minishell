/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:03:20 by btan              #+#    #+#             */
/*   Updated: 2024/03/11 20:08:54 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_array(t_list *lst)
{
	size_t	len;
	char	**arr;
	size_t	i;

	if (!lst)
		return (NULL);
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

int	ft_strslen(char **strs)
{
	char	**ptr;

	ptr = strs;
	while (*ptr)
		ptr++;
	return (ptr - strs);
}

void	array_to_list(t_list **lst, char **envp)
{
	t_list	*env;
	size_t	len;

	len = ft_strslen(envp);
	if (!len)
		return ;
	while (len--)
	{
		env = ft_lstnew(ft_strdup(envp[len]));
		ft_lstadd_front(lst, env);
	}
}

char	**ft_strsplit(char *str, char *token)
{
	char	**strs;
	char	*start;
	char	*end;
	size_t	i;
	
	strs = ft_calloc(2, sizeof(char *));
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
	free(strs[0]);
	free(strs);
	return (new);
}

int		s_quote_do_not_expand(char *str)
{
	if (ft_strchr(str, '\''))
		if (ft_strchr(str, '$'))
			return (1);
	return (0);
}

char	*expand_env(char *str, t_list *envll)
{
	t_list	*lst;
	char	*start;
	char	*end;
	char	*token;
	char	*env;
	char	*temp;

	lst = envll;
	start = ft_strchr(str, '$');
	if (!start)
		return (str);
	if (s_quote_do_not_expand(str))
		return (str);
	end = start + 1;
	while (ft_isalnum(*end) || *end == '?')
		end++;
	token = ft_substr(str, start - str, end - start);
	while (lst)
	{
		env = (char *) lst->content;
		temp = ft_substr(env, 0, ft_strchr(env, '=') - env);
		//if (!ft_strncmp(token + 1, env, ft_strchr(env, '=') - env))
		if (!ft_strcmp(token + 1, temp))
		{
			free(temp);
			break ;
		}
		lst = lst->next;
		free(temp);
	}
	if (lst) 
		env = env + (end - start);
	else
	{
		if (!ft_strcmp(token, "$?"))
			env = ft_itoa(get_exit_status(-1));
		else
			env = "";
	}
	env = ft_strre(str, token, env);
	free(token);
	if (ft_strchr(env, '$'))
		env = expand_env(env, envll);
	return (env);
}
