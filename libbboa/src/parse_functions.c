/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 21:15:56 by mbeilles          #+#    #+#             */
/*   Updated: 2019/04/22 14:52:11 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "hashmap.h"
#include "bboa.h"
#include "libft.h"

t_arg_token		bboa_parse_number(char *v)
{
	return ((t_arg_token){
			.number_token = {
				.type = BBOA_AT_NUMBER,
				.data = NULL,
				.number = ft_strtod(v, &v)
			}});
}

t_arg_token		bboa_parse_boolean(char *v)
{
	bool		b;

	return ((t_arg_token){
			.bool_token = {
				.type = BBOA_AT_BOOLEAN,
				.data = NULL,
				.boolean = ft_strtob(v, NULL, NULL)
			}});
}

t_arg_token		bboa_parse_void(char *v)
{
	return ((t_arg_token){.none_token = {
			.type = BBOA_AT_NONE,
			.data = v
		}});
}

t_arg_token		bboa_parse_string(char *v)
{
	return ((t_arg_token){.string_token = {
			.type = BBOA_AT_STRING,
			.data = NULL,
			.string = v,
			.len = ft_strlen(v)
		}});
}
