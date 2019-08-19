/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 12:17:45 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/18 11:22:44 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <curses.h>
# include "corewar.h"

/*
**	GLOBAL VIEWER MACROS
**	VISU_WIDTH 256 | VISU_HEIGHT 68 -> ARENA 64
*/

# define			VISU_WIDTH		(256)
# define			VISU_HEIGHT		(68)
# define			VISU_TOP_B		(0)
# define			VISU_LEFT_B		(0)
# define			VISU_BOT_B		(VISU_HEIGHT - 1)
# define			VISU_RIGHT_B	(VISU_WIDTH - 1)
# define			VISU_VS			(VISU_WIDTH - 60)

# define			VISU_INFOS		(VISU_VS + 3)
# define			VISU_HEADER		(VISU_TOP_B + 4)
# define			VISU_WARRIOR	(VISU_TOP_B + 12)
# define			VISU_NB_WINFO	(4)
# define			VISU_INFO_MID	((VISU_VS + VISU_RIGHT_B) / 2)
# define			VISU_DBG_INFO	(VISU_WARRIOR + 5 + (1 + VISU_NB_WINFO) * 4)

# define			VISU_CLR_W1		(COR_ARN_W1_CLAIM)
# define			VISU_CLR_W2		(COR_ARN_W2_CLAIM)
# define			VISU_CLR_W3		(COR_ARN_W3_CLAIM)
# define			VISU_CLR_W4		(COR_ARN_W4_CLAIM)

# define			VISU_GREEN		(VISU_CLR_W1)
# define			VISU_BLUE		(VISU_CLR_W2)
# define			VISU_RED		(VISU_CLR_W3)
# define			VISU_CYAN		(VISU_CLR_W4)


# define			VISU_ARENA_TB	(VISU_TOP_B + 2)
# define			VISU_ARENA_LB	(VISU_LEFT_B + 3)
# define			VISU_ARENA_BB	(VISU_BOT_B - 2)
# define			VISU_ARENA_RB	(VISU_VS - 3)
# define			VISU_ARENA_WDTH	(64)
//# define			VISU_ARENA_WDTH	((VISU_ARENA_RB - 4) / 3)

# define			VISU_RUNNING	(true)
# define			VISU_PAUSED		(false)
# define			VISU_CPS_MAX	(151)

/*
**	VIEWER UPDATE FUNCTIONS
*/

void				visu_update(void);
void				cps_max(void);

void				visu_cps(void);
void				visu_borders(void);
void				visu_legend(void);
void				visu_state(void);
bool				visu_get_key(void);
void				visu_clock(void);
void				visu_processes(void);
void				visu_arena(void);
void				visu_end_wait(void);
void				visu_warrior(void);
void				visu_live(void);
 void				visu_debug(void);

#endif
