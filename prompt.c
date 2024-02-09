/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:59:25 by btan              #+#    #+#             */
/*   Updated: 2024/02/09 15:35:21 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*user;
	char	*pwd;
	char	*home;
	
	user = getenv("USER");
	pwd = ft_pwd();
	home = getenv("HOME");
	printf("%s:", user);
	if (!strncmp(home, pwd, ft_strlen(home)))
		printf("~%s$ ", pwd + ft_strlen(home));
	else
		printf("%s$ ", pwd);
	free(pwd);
}
