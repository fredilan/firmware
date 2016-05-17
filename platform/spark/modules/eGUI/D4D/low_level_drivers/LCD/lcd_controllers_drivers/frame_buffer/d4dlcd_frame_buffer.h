/**************************************************************************
*
* Copyright 2014 by Petr Gargulak. eGUI Community.
* Copyright 2009-2013 by Petr Gargulak. Freescale Semiconductor, Inc.
*
***************************************************************************
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License Version 3
* or later (the "LGPL").
*
* As a special exception, the copyright holders of the eGUI project give you
* permission to link the eGUI sources with independent modules to produce an
* executable, regardless of the license terms of these independent modules,
* and to copy and distribute the resulting executable under terms of your
* choice, provided that you also meet, for each linked independent module,
* the terms and conditions of the license of that module.
* An independent module is a module which is not derived from or based
* on this library.
* If you modify the eGUI sources, you may extend this exception
* to your version of the eGUI sources, but you are not obligated
* to do so. If you do not wish to do so, delete this
* exception statement from your version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* You should have received a copy of the GNU General Public License
* and the GNU Lesser General Public License along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************//*!
*
* @file      d4dlcd_frame_buffer.h
*
* @author     Petr Gargulak
*
* @version   0.0.2.0
*
* @date      Aug-30-2010
*
* @brief     D4D driver - frame_buffer lcd driver function header file
*
*******************************************************************************/

#ifndef __D4DLCD_FRAMEBUFFER_H
#define __D4DLCD_FRAMEBUFFER_H

  #if (D4D_MK_STR(D4D_LLD_LCD) == d4dlcd_frame_buffer_ID)

    /******************************************************************************
    * Includes
    ******************************************************************************/
    //#include "d4dlcd_frame_buffer_cfg.h"

    /******************************************************************************
    * Constants
    ******************************************************************************/

   	#ifndef D4DLCDHWFB_DIRECT_MEM_ACCESS
   		#define D4DLCDHWFB_DIRECT_MEM_ACCESS 0
   	#endif
    /******************************************************************************
    * Types
    ******************************************************************************/

    /******************************************************************************
    * Macros
    ******************************************************************************/

    /******************************************************************************
    * Global variables
    ******************************************************************************/

		#ifdef D4D_LLD_LCD_HW
		  extern const D4DLCDHWFB_FUNCTIONS D4D_LLD_LCD_HW;
		#endif

		  typedef struct WriteRegion {
			unsigned long win_cur_addr;
			uint16_t win_cur_w;
			uint16_t win_cur_h;

			uint16_t win_x;
			uint16_t win_y;
			uint16_t win_width;
			uint16_t win_height;
			uint16_t max_width, max_height;
		  } WriteRegion;

		  extern WriteRegion writeRegion;

    /******************************************************************************
    * Global functions
    ******************************************************************************/

  #endif
#endif /* __D4DLCD_FRAMEBUFFER_H */










