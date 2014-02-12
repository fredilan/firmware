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
* @file      d4dtch_cr_touch.h
*
* @author     Petr Gargulak
* 
* @version   0.0.3.0
* 
* @date      Dec-7-2011
* 
* @brief     D4D driver - cr_touch touch screen driver function header file 
*
*******************************************************************************/

#ifndef __D4DTCH_CR_TOUCH_H
#define __D4DTCH_CR_TOUCH_H

  #if (D4D_MK_STR(D4D_LLD_TCH) == d4dtch_cr_touch_ID)

    /******************************************************************************
    * Includes
    ******************************************************************************/
    #include "d4dtch_cr_touch_cfg.h"

    /******************************************************************************
    * Constants
    ******************************************************************************/
    #define CRTCH_STATUS      0x00 
    #define CRTCH_STATUS1     0x01
    #define CRTCH_STATUS2     0x02
    #define CRTCH_X           0x03
    #define CRTCH_Y           0x05
    #define CRTCH_PRESS       0x07
    #define CRTCH_FIFO_ST     0x09 
    #define CRTCH_FIFO_X      0x0A
    #define CRTCH_FIFO_Y      0x0C
    #define CRTCH_FIFO_PRESS  0x0E
    #define CRTCH_UART_BAUD   0x10

    #define CRTCH_RES_CFG     0x40


    #define CRTCH_STATUS1_RTST_MASK         0x80
    #define CRTCH_STATUS1_RTSRDY_MASK       0x01

    #define CRTCH_RES_CFG_RTPRESEN_MASK     0x80
    
    #define CRTCH_STATUS2_RTSD_MASK     0x03



    /****** Algorithm constants/macros *****/
    
    #ifndef D4DTCH_FULL_SCALE
      #define D4DTCH_FULL_SCALE           0x0FFF
    #endif 
                         
    #ifndef D4DTCH_X_TOUCH_MIN
      #define D4DTCH_X_TOUCH_MIN              (D4DTCH_FULL_SCALE / 10)
    #endif
   
    #ifndef D4DTCH_Y_TOUCH_MIN
      #define D4DTCH_Y_TOUCH_MIN              (D4DTCH_FULL_SCALE / 10)
    #endif
   
    #ifndef D4DTCH_X_TOUCH_OFFMAX
      #define D4DTCH_X_TOUCH_OFFMAX           (D4DTCH_X_TOUCH_MIN * 4 / 2)
    #endif
   
    #ifndef D4DTCH_Y_TOUCH_OFFMAX
      #define D4DTCH_Y_TOUCH_OFFMAX           (D4DTCH_Y_TOUCH_MIN * 4 / 2)
    #endif
   
    #ifndef D4DTCH_SAMPLE_MARGIN
      #define D4DTCH_SAMPLE_MARGIN            (D4DTCH_FULL_SCALE / 256)
    #endif


    #ifndef D4DTCH_IIC_BAUDRATE
      #define D4DTCH_IIC_BAUDRATE           400000
    #endif 
    
    #ifndef D4DTCH_IIC_ADDRESS
      #define D4DTCH_IIC_ADDRESS           0x49
    #endif 
    
    #ifndef D4DTCH_INVERSE_X
      #define D4DTCH_INVERSE_X               0
    #endif

    #ifndef D4DTCH_INVERSE_Y
      #define D4DTCH_INVERSE_Y               0
    #endif

    #ifndef D4DTCH_SWAP_AXES   
      #define D4DTCH_SWAP_AXES               0
    #endif

    #ifndef D4D_LLD_TCH_HW_CRTOUCH
      #define D4D_LLD_TCH_HW_CRTOUCH d4dtchhw_crtouch_iicBareMetal
    #endif

    /******************************************************************************
    * Macros 
    ******************************************************************************/


    #if D4DTCH_INVERSE_X != 0
      #define D4DTCH_INVERSE_X_INT D4DTCH_FULL_SCALE
    #endif
  
    #if D4DTCH_INVERSE_Y != 0
      #define D4DTCH_INVERSE_Y_INT D4DTCH_FULL_SCALE
    #endif

    /******************************************************************************
    * Types
    ******************************************************************************/
#pragma pack (push)
#pragma pack (1)    

    typedef struct
    {
      Byte status1;
      Byte status2;
      Word X;
      Word Y;
    }CRTOUCH_RES_SIMPLE;
#pragma pack (pop)

    typedef struct D4DTCHHWCRTOUCH_FUNCTIONS_S
    {
      unsigned char (*D4DTCHHWCRTOUCH_Init)(void);
      unsigned char (*D4DTCHHWCRTOUCH_DeInit)(void);
      void (*D4DTCHHWCRTOUCH_SetAddress)(unsigned char);
      signed long (*D4DTCHHWCRTOUCH_SetBaudRate)(unsigned long baudRate);
      unsigned char (*D4DTCHHWCRTOUCH_MultiReadBytes)(unsigned char regAddr, unsigned char* pBuffer, unsigned char cnt);
      unsigned char (*D4DTCHHWCRTOUCH_MultiWriteBytes)(unsigned char regAddr, unsigned char* pBuffer, unsigned char cnt);            
      unsigned char COMM_OK;
    }D4DTCHHWCRTOUCH_FUNCTIONS;
      
    /******************************************************************************
    * Global variables
    ******************************************************************************/
    
    extern const D4DTCHHWCRTOUCH_FUNCTIONS D4D_LLD_TCH_HW_CRTOUCH;
    
    /******************************************************************************
    * Global functions
    ******************************************************************************/

  #endif
#endif /* __D4DTCH_CR_TOUCH_H */










