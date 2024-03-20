/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:03:20 by btan              #+#    #+#             */
/*   Updated: 2024/03/20 22:26:00 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_squote(char *str)
{
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
			else
				str = ft_strchr(str, '\0');
			break ;
		}
		if (*str == '\'')
			str = ft_strchr(str + 1, '\'');
		if (!str || !*str)
			break ;
		str++;
	}
	return (str);
}

//static t_list	*find_token(t_list *lst, char **env, char *token)
//{
//	char	*temp;
//
//	while (lst)
//	{
//		*env = (char *) lst->content;
//		temp = ft_substr(*env, 0, ft_strchr(*env, '=') - *env);
//		if (!ft_strcmp(token + 1, temp))
//		{
//			free(temp);
//			break ;
//		}
//		lst = lst->next;
//		free(temp);
//	}
//	return (lst);
//}

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
	char	*temp;

	lst = envll;
	temp = str;
	while (*temp)
	{
		if (*temp == '$')
		{
			printf("%s,\n", temp);
			while (ft_isalnum(*temp) || *end == '?')
				temp++;	
			printf("%s,\n", temp);
		}
		temp++;
	}
	return (str);
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
