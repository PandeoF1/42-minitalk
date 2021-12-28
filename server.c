/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:03:15 by tnard             #+#    #+#             */
/*   Updated: 2021/12/12 05:34:43 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

static void	action(int sig, siginfo_t *info, void *truc)
{
	static int				i = 0;
	static unsigned char	c = 0;

	(void)truc;
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
			return ((void)kill(info->si_pid, SIGUSR2));
		ft_putchar_fd(c, 1);
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
	else
		c = c << 1;
}

int	main(void)
{
	struct sigaction	s_signal;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_signal.sa_sigaction = action;
	s_signal.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_signal, 0);
	sigaction(SIGUSR2, &s_signal, 0);
	while (42)
		pause();
	return (0);
}
