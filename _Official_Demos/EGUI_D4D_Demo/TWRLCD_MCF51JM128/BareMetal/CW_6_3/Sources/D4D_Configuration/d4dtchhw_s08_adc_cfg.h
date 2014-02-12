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
* @file      d4dtchhw_s08_adc_cfg.h
*
* @author    Petr Gargulak
* 
* @version   0.0.1.0
* 
* @date      Aug-6-2012
* 
* @brief     D4D driver - low level driver of ADC and gpio for resistive touch screen 
*            confiduration header file 
*
*******************************************************************************/

#ifndef __D4DTCHHW_S08_ADC_CFG_H
#define __D4DTCHHW_S08_ADC_CFG_H


  /******************************************************************************
  * includes
  ******************************************************************************/
  
  #include "derivative.h"    /* include peripheral declarations and more for S08 and CV1 */ 
 
  /******************************************************************************
  * Constants
  ******************************************************************************/

  // X+ wire definition 
  #define D4DTCH_X_PLUS   6
  #define D4DTCH_X_PLUS_PORT  PTBD  
  #define D4DTCH_X_PLUS_DDR   PTBDD

  #define D4DTCH_X_PLUS_ADCH   6
 // #define D4DTCH_X_PLUS_ADCH_PIN APCTL1_ADPC1
  #define D4DTCH_X_PLUS_ADCH_PIN_ENABLE   APCTL1_ADPC6 = 1;
  #define D4DTCH_X_PLUS_ADCH_PIN_DISABLE  APCTL1_ADPC6 = 0; 

  //#define D4DTCH_INIT_X_PLUS  OUTPUT(D4DTCH_X_PLUS); RESET(D4DTCH_X_PLUS); 
  //#define D4DTCH_RESET_X_PLUS RESET(D4DTCH_X_PLUS);
  //#define D4DTCH_SET_X_PLUS   SET(D4DTCH_X_PLUS);
  
  // X- wire definition 
  #define D4DTCH_X_MINUS  7
  #define D4DTCH_X_MINUS_PORT  PTBD  
  #define D4DTCH_X_MINUS_DDR   PTBDD
  
  //#define D4DTCH_INIT_X_MINUS  OUTPUT(D4DTCH_X_MINUS); RESET(D4DTCH_X_MINUS); 
  //#define D4DTCH_RESET_X_MINUS RESET(D4DTCH_X_MINUS);
  //#define D4DTCH_SET_X_MINUS   SET(D4DTCH_X_MINUS);  
  //#define D4DTCH_X_MINUS_HIGH_Z_ENABLE INPUT(D4DTCH_X_MINUS);
  //#define D4DTCH_X_MINUS_HIGH_Z_DISABLE OUTPUT(D4DTCH_X_MINUS);
  
    // Y+ wire definition 
  #define D4DTCH_Y_PLUS   4
  #define D4DTCH_Y_PLUS_PORT  PTBD  
  #define D4DTCH_Y_PLUS_DDR   PTBDD

  #define D4DTCH_Y_PLUS_ADCH   4
  #define D4DTCH_Y_PLUS_ADCH_PIN_ENABLE   APCTL1_ADPC4 = 1;
  #define D4DTCH_Y_PLUS_ADCH_PIN_DISABLE  APCTL1_ADPC4 = 0;   
  
  //#define D4DTCH_INIT_Y_PLUS  OUTPUT(D4DTCH_Y_PLUS); RESET(D4DTCH_Y_PLUS); 
  //#define D4DTCH_RESET_Y_PLUS RESET(D4DTCH_Y_PLUS);
  //#define D4DTCH_SET_Y_PLUS   SET(D4DTCH_Y_PLUS);
  
    // Y- wire definition 
  #define D4DTCH_Y_MINUS  5
  #define D4DTCH_Y_MINUS_PORT  PTBD  
  #define D4DTCH_Y_MINUS_DDR   PTBDD
  
  //#define D4DTCH_INIT_Y_MINUS  OUTPUT(D4DTCH_Y_MINUS); RESET(D4DTCH_Y_MINUS); 
  //#define D4DTCH_RESET_Y_MINUS RESET(D4DTCH_Y_MINUS);
  //#define D4DTCH_SET_Y_MINUS   SET(D4DTCH_Y_MINUS);  
  //#define D4DTCH_Y_MINUS_HIGH_Z_ENABLE INPUT(D4DTCH_Y_MINUS);
  //#define D4DTCH_Y_MINUS_HIGH_Z_DISABLE OUTPUT(D4DTCH_Y_MINUS);
  


   // definition of calibration cross offset on on screen in pixels
  #define D4DTCH_CALIB_CROSS_OFFSET 30


  // Constant specifying maximum ADC value for a screen touch (=12bits)
  #define D4DTCH_FULL_SCALE           0x0FFF

  // Constants specifying minimum ADC value for a screen touch
  #define D4DTCH_X_TOUCH_MIN              (D4DTCH_FULL_SCALE / 10)
  #define D4DTCH_Y_TOUCH_MIN              (D4DTCH_FULL_SCALE / 10)

  #define D4DTCH_X_TOUCH_OFFMAX           1100//   (D4DTCH_X_TOUCH_MIN * 4 / 3)
  #define D4DTCH_Y_TOUCH_OFFMAX           1100//   (D4DTCH_Y_TOUCH_MIN * 4 / 3)

  // Constants specifying ADC difference for touch screen sample
  //#define D4DTCH_SAMPLE_MARGIN            (D4DTCH_FULL_SCALE / 64)
#endif /* __D4DTCHHW_S08_ADC_CFG_H */