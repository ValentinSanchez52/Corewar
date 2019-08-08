/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_uuid_generate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 16:22:32 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/08 16:26:58 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uuid/uuid.h>

/*
** Generates a uuid in a string passed in args of length 36 + 1 (`\0`)
*/

void				str_uuid_generate(char *uuid)
{
	uuid_t binuuid;

	uuid_generate_random(binuuid);
	uuid_unparse_lower(binuuid, uuid);
}
