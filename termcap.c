/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:27:35 by btan              #+#    #+#             */
/*   Updated: 2024/02/21 15:59:56 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_mode(int fd, struct termios *term)
{
	printf("Terminal attributes for %d\n", fd);
	if (tcgetattr(fd, term))
		perror("tcgetattr() error");
	if (term->c_iflag & ICANON)
		printf("Interactive mode\n");
	else
		printf("Non-interactive mode\n");	
	if (term->c_iflag & ECHO)
		printf("ECHO enabled\n");
	else
		printf("ECHO disabled\n");	
}

int	main(void)
{
	char	*buffer;
	struct termios	term;

	while (1)
	{
		buffer = readline("prompt> ");
		if (!ft_strncmp(buffer, "mode", 4))
			print_mode(0, &term);
		if (!ft_strncmp(buffer, "set", 3))
			tcsetattr(0, TCSANOW, &term);
		if (!ft_strncmp(buffer, "exit", 4))
				exit(0);
		free(buffer);
	}
}
