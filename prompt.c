/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:59:25 by btan              #+#    #+#             */
/*   Updated: 2024/02/14 17:44:15 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hostname(void)
{
	int		fd;
	char	*hostname;
	char	*ptr;

	fd = open("/etc/hostname", O_RDONLY);
	hostname = ft_calloc(1025, 1);
	if (!hostname)
		return (NULL);
	hostname[1024] = '\0';
	read(fd, hostname, 1024);
	ptr = hostname;
	while (*ptr)
	{
		if (*ptr == '\n')
			*ptr = '\0';
		ptr++;
	}
	close(fd);
	return (hostname);
}

void	prompt(void)
{
	char	*user;
	char	*hostname;
	char	*pwd;
	char	*home;

	user = getenv("USER");
	hostname = get_hostname();
	pwd = ft_pwd();
	home = getenv("HOME");
	printf("%s@%s:", user, hostname);
	if (!strncmp(home, pwd, ft_strlen(home)))
		printf("~%s$ ", pwd + ft_strlen(home));
	else
		printf("%s$ ", pwd);
	free(hostname);
	free(pwd);
}
