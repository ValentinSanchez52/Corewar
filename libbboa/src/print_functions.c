/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:34:20 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/04 20:44:33 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "bboa.h"
#include "libft.h"

t_bboa_error g_bboa_error = (t_bboa_error){
	.state = BBOA_RS_NONE,
	.level = BBOA_ERR_INFO,
	.match = "none",
	.message = "unset",
	.argument = "none",
};

/*
**	This function print an error message according to an error given
**		in argument.
**	It contains 2 lookup tables for the state and the level of the error.
**
**	This is used for generic error printing that can happend but you can use
**		your own.
**	If you return something other than `BBOA_RS_OK` in your callback hook,
**		the parsing will stop at that point and display an error.
*/

static const char *const		get_header(t_bboa_error_level level)
{
	static const char *const	headers[BBOA_ERR_MAX_LEVEL] = {
		[BBOA_ERR_INFO] = "\e[0;37m[\e[1;34mi\e[0;37m]\e[0m",
		[BBOA_ERR_WARN] = "\e[0;37m[\e[1;33m!\e[0;37m]\e[0m",
		[BBOA_ERR_CRIT] = "\e[0;37m[\e[1;31mx\e[0;37m]\e[0m"
	};

	return (headers[level]);
}

static const char *const		get_template(t_bboa_state state)
{
	static const char *const	templates[BBOA_RS_MAX_STATE] = {
		[BBOA_RS_NONE] = "How did you get there?",
		[BBOA_RS_OK] = "There is no error, why are you printing?",
		[BBOA_RS_DISPLAY_USAGE] = "Displaying usage",
		[BBOA_RS_UNKNOWN_OPT] = "Unknown option",
		[BBOA_RS_NO_ARG] = "No argmument",
		[BBOA_RS_NOT_ENOUGH_ARGS] = "Not enough arguments",
		[BBOA_RS_GENERIC_ERROR] = "An error has occured",
		[BBOA_RS_TYPE_MISMATCH] = "Type mismatch",
		[BBOA_RS_MULTIPLE_REFS] = "Multiple references to option"
	};

	return (templates[state]);
}

void							bboa_print_error(t_bboa_error error)
{
	char						*msg;

	if (error.message && error.match && error.argument)
		msg = ft_strajoin(10, get_header(error.level), " ",
				get_template(error.state), " on \e[33m'\e[1;33m", error.match,
				"\e[0;33m'\e[0m at '\e[34m", error.argument, "\e[0m'\n", error.message,
				"\n");
	else if (error.message && error.match)
		msg = ft_strajoin(8, get_header(error.level), " ",
				get_template(error.state), " on \e[33m'\e[1;33m", error.match,
				"\e[0;33m'\e[0m\n", error.message, "\n");
	else if (error.message)
		msg = ft_strajoin(6, get_header(error.level), " ",
				get_template(error.state), ".\n", error.message, "\n");
	else
		msg = ft_strajoin(4, get_header(error.level), " ",
				get_template(error.state), ".\n");
	if (msg && (write(1, msg, ft_strlen(msg)) || 1))
		free(msg);
	if (error.destructor)
		error.destructor(error);
	if (error.level > BBOA_RS_OK || error.state == BBOA_RS_DISPLAY_USAGE)
		exit(error.state == BBOA_RS_DISPLAY_USAGE ? 0 : EXIT_FAILURE);
}
