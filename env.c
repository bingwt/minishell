/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:03:20 by btan              #+#    #+#             */
/*   Updated: 2024/03/12 14:42:57 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	s_quote_do_not_expand(char *str)
{
	if (ft_strchr(str, '\''))
		if (ft_strchr(str, '$'))
			return (1);
	return (0);
}

t_list	*find_token(t_list *lst, char **env, char *token)
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
	if (!start || (s_quote_do_not_expand(str)))
		return (str);
	end = start + 1;
	while (ft_isalnum(*end) || *end == '?')
		end++;
	token = ft_substr(str, start - str, end - start);
	if (find_token(lst, &env, token))
		env = env + (end - start);
	else
		env = "";
	if (!ft_strcmp(token, "$?"))
		env = ft_itoa(get_exit_status(-1));
	env = ft_strre(str, token, env);
	free(token);
	if (ft_strchr(env, '$'))
		env = expand_env(env, envll);
	return (env);
}
