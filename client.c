/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:01:18 by tnard             #+#    #+#             */
/*   Updated: 2022/02/16 10:59:18 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft/libft.h"

int		g_result = 0;

static void	ft_kill(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	ft_usage(void)
{
	ft_putstr_fd("usage: ./client [pid] [message]\n", 2);
	return (1);
}

static void	action(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		if (received != g_result)
		{
			ft_putstr_fd("Error : ", 1);
			ft_putnbr_fd(received, 1);
			ft_putchar_fd('/', 1);
			ft_putnbr_fd(g_result, 1);
			ft_putchar_fd('\n', 1);
			exit(1);
		}
		exit(0);
	}
}

int	ft_int_len(int x)
{
	int	y;

	y = 0;
	if (x > 0)
	{
		if (x > 9)
			y += ft_int_len(x / 10);
		y++;
	}
	return (y);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2])
		|| (int)ft_strlen(argv[1]) != ft_int_len(ft_atoi(argv[1])))
		return (ft_usage());
	g_result = ft_strlen(argv[2]);
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	ft_kill(ft_atoi(argv[1]), argv[2]);
	while (42)
		pause();
	return (0);
}
