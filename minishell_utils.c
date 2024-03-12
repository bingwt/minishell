/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:38:46 by btan              #+#    #+#             */
/*   Updated: 2024/03/12 13:40:19 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strslen(char **strs)
{
	char	**ptr;

	ptr = strs;
	while (*ptr)
		ptr++;
	return (ptr - strs);
}

char	**ft_strsplit(char *str, char *token)
{
	char	**strs;
	char	*start;
	char	*end;
	size_t	i;

	strs = ft_calloc(2, sizeof(char *));
	start = ft_strnstr(str, token, ft_strlen(str));
	if (!start)
	{
		free(strs);
		return (NULL);
	}
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
