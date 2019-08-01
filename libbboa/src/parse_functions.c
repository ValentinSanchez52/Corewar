/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 21:15:56 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/01 06:03:10 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "hashmap.h"
#include "bboa.h"
#include "libft.h"

t_arg_token		bboa_parse_double(char *v)
{
	char		*s;
	double		d;

	s = ft_strskip(v, &ft_isspace);
	d = ft_strtod(s, &v);
	if (ft_isdouble(s))
		return ((t_arg_token){
				.double_token = {
					.type = BBOA_AT_DOUBLE,
					.data = NULL,
					.number = d
				}});
	else
		return ((t_arg_token){
				.double_token = {
					.type = BBOA_AT_DOUBLE,
					.data = NULL,
					.number = NAN
				}});
}

t_arg_token		bboa_parse_integer(char *v)
{
	char		*s;
	long long	i;
	int			len[2];

	s = ft_strskip(v, &ft_isspace);
	i = ft_strtol(s, &v, 10);
	v = ft_ltostr(i, 10, false);
	len[0] = 0;
	len[1] = ft_strlen(v);
	while (s[len[0]])
		len[0]++;
	if (ft_islong(s) && ft_strnequ(s, v, len[0] < len[1] ? len[0] : len[1]))
		return ((t_arg_token){
				.integer_token = {
					.type = BBOA_AT_INTEGER,
					.data = NULL,
					.number = i
				}});
	else
		return ((t_arg_token){
				.integer_token = {
					.type = BBOA_AT_INTEGER,
					.data = NULL,
					.invalid = true
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
