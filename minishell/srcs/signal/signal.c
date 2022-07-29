/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:46:55 by albaur            #+#    #+#             */
/*   Updated: 2022/07/26 15:26:47 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_toggle(int n)
{
	if (n == 0)
	{
		sig_wait(SIGINT, sig_handler);
		sig_ignore(SIGQUIT);
	}
	else if (n == 1)
	{
		sig_wait(SIGINT, sig_int_nl);
		sig_wait(SIGQUIT, sig_handler);
	}
	else if (n == 2)
	{
		sig_ignore(SIGINT);
		sig_ignore(SIGQUIT);
		init_mode(1);
		return ;
	}
	else if (n == 3)
	{
		sig_wait(SIGINT, here_doc_sig_handler);
		sig_ignore(SIGQUIT);
		init_mode(0);
		return ;
	}
	init_mode(n);
}

void	sig_wait(int sig, void (*hdlr)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = hdlr;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, sig);
	if (sigaction(sig, &sa, NULL))
		perror("sigaction");
}

void	sig_ignore(int sig)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, sig);
	if (sigaction(sig, &sa, NULL))
		perror("sigaction");
}
