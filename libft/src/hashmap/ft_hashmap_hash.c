/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap_hash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:07:02 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/31 05:07:17 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"

/*
** This is a k=33 implentation of the hashing function called 'djb2'
** 		This is a simple but efficient hashing function with harmonious
** 		repartition and few collisions for what it is.
** This is a string based non-cryptographic function which is good for this
** 		kind of use case.
*/

uint16_t			ft_hash_djb2(const uint8_t *str)
{
	uint16_t	hash;
	uint16_t	c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}
