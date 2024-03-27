/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:55:23 by btan              #+#    #+#             */
/*   Updated: 2024/03/27 15:39:15 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	ft_unset(char *cmd, t_list **envll)
//{
//	t_list	*env;
//	t_list	*temp;
//	char	**args;
//	char	*content;
//	char	*token;
//
//	env = *envll;
//	args = ft_split(cmd, '=');
//	token = args[0];
//	while (env->next)
//	{
//		content = (char *) env->next->content;
//		if (!ft_strncmp(token + 5, content, ft_strchr(content, '=') - content))
//			break ;
//		env = env->next;
//	}
//	free_strs(args);
//	if (env->next)
//	{
//		temp = env->next;
//		env->next = env->next->next;
//		ft_lstdelone(temp, free);
//	}
//	return ;
//}

static t_list	*find_next_token(char *token, t_list *env)
{
	char	*start;
	char	*end;

	while (env->next)
	{
		start = (char *) env->next->content;
		end = ft_strchr(start, '=');
		start = ft_substr(start, 0, end - start);
		if (!ft_strcmp(token, start))
			break ;
		if (start)
			free(start);
		env = env->next;
	}
	if (start)
		free(start);
	return (env);
}

void	unset_var(char *cmd, t_list **envll)
{
	t_list	*env;
	t_list	*temp;
	char	**args;

	env = *envll;
	args = ft_split(cmd, '=');
	env = find_next_token(args[0], env);
	if (env->next)
	{
		temp = env->next;
		env->next = env->next->next;
		ft_lstdelone(temp, free);
		env = env->next;
	}
	return ;
}

void	ft_unset(char **args, t_list **envll)
{
	int	i;

	i = 1;
	if (!args[1])
		return ;
	else
		while (args[i])
			unset_var(args[i++], envll);
}
