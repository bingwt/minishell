/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:59:43 by btan              #+#    #+#             */
/*   Updated: 2024/04/07 18:13:40 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd(void)
{
	char	*path;


	path = malloc(PATH_MAX + 1 * (sizeof(char)));
	if (!path)
		return (NULL);
	path[PATH_MAX] = '\0';
	getcwd(path, PATH_MAX);
	return (path);
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = get_cwd();
	printf("%s\n", cwd);
	get_exit_status(unshift_exitcode(0));
	free(cwd);
}
