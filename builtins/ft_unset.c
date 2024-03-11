/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:55:23 by btan              #+#    #+#             */
/*   Updated: 2024/03/12 01:20:00 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *cmd, t_list **envll)
{
	t_list	*env;
	t_list	*temp;
	char	**args;
	char	*content;
	char	*token;

	env = *envll;
	args = ft_split(cmd, '=');
	token = args[0];
	while (env->next)
	{
		content = (char *) env->next->content;
		if (!ft_strncmp(token + 5, content, ft_strchr(content, '=') - content))
			break ;
		env = env->next;
	}
	free_strs(args);
	if (env->next)
	{
		temp = env->next;
		env->next = env->next->next;
		ft_lstdelone(temp, free);
	}
	return ;
}
