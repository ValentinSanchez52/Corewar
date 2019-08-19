/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:48:03 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 19:13:38 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "print.h"

void				print_vm(t_print msg)
{
	msg.flags.debug = g_vm.flags.debug;
	print(msg);
}
