/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_fwup_wrap_com.c
 * Version      : 2.0
 * Description  : Functions for the Firmware update module.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_fwup_wrap_com.h"
/**** Start user code ****/
/**** End user code   ****/

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
/**** Start user code ****/
/**** End user code   ****/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/
/**** Start user code ****/
/**** End user code   ****/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
/**** Start user code ****/
/**** End user code   ****/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
/**** Start user code ****/
/**** End user code   ****/

/*
 * Common functions
 */
/**********************************************************************************************************************
* Function Name: r_fwup_wrap_disable_interrupt
* Description  : wrapper function for disable interrupts
* Arguments    : none
* Return Value : none
**********************************************************************************************************************/
void r_fwup_wrap_disable_interrupt(void)
{
    /**** Start user code ****/
#if defined(__RX)
    R_BSP_InterruptsDisable();
#else
    BSP_DISABLE_INTERRUPT();
#endif
    /**** End user code   ****/
}
/**********************************************************************************************************************
 End of function r_fwup_wrap_disable_interrupt
 *********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: r_fwup_wrap_enable_interrupt
* Description  : wrapper function for enable interrupts
* Arguments    : none
* Return Value : none
**********************************************************************************************************************/
void r_fwup_wrap_enable_interrupt(void)
{
    /**** Start user code ****/
#if defined(__RX)
    R_BSP_InterruptsEnable();
#else
    BSP_ENABLE_INTERRUPT();
#endif
    /**** End user code   ****/
}
/**********************************************************************************************************************
 End of function r_fwup_wrap_enable_interrupt
 *********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: r_fwup_wrap_software_reset
* Description  : wrapper function for execute software reset.
* Arguments    : none
* Return Value : none
**********************************************************************************************************************/
void r_fwup_wrap_software_reset(void)
{
    /**** Start user code ****/

    r_fwup_wrap_disable_interrupt();
    r_fwup_wrap_software_delay(1000, FWUP_DELAY_MILLISECS);

    /* SW Reset */
#if defined(__RX)
    R_BSP_SoftwareReset();
#else
    IAWCTL=0x80;                        // Unauthorized access detection enabled
    *(__far volatile char *)0x00=0x00;  // White at address 0x00
    BSP_NOP();
    while(1);
#endif

    /**** End user code   ****/
}
/**********************************************************************************************************************
 End of function r_fwup_wrap_software_reset
 *********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: r_fwup_wrap_software_delay
* Description  : wrapper function for execute software delay.
* Arguments    : delay
*                units
* Return Value : 0 : success
*                other :error
**********************************************************************************************************************/
uint32_t r_fwup_wrap_software_delay(uint32_t delay, e_fwup_delay_units_t units)
{
    /**** Start user code ****/
#if defined(__RX)
    uint32_t  time_units;

    if (FWUP_DELAY_MICROSECS == units)
    {
        time_units = BSP_DELAY_MICROSECS;
    }
    else if (FWUP_DELAY_MILLISECS == units)
    {
        time_units = BSP_DELAY_MILLISECS;
    }
    else
    {
        time_units = BSP_DELAY_SECS;
    }
    return (uint32_t)R_BSP_SoftwareDelay(delay, (bsp_delay_units_t)time_units);
#else
    uint32_t time;
    uint32_t fclk = 32;

    switch (units)
    {
        case FWUP_DELAY_MICROSECS:
            time = delay;
            fclk = (uint32_t)(fclk / 20U);
            break;
        case FWUP_DELAY_MILLISECS:
            time = (uint32_t)(delay * 100U);
            break;
        case FWUP_DELAY_SECS:
            time = (uint32_t)(delay * 100000U);
            break;
        default:
            break;
    }

    while(0 < time)
    {
        /* Delay 1us */
        for(uint16_t cnt = fclk; 0 < cnt; cnt--)
        {
            BSP_NOP();
            BSP_NOP();
        }
        time--;
    }
    return 0;
#endif
    /**** End user code   ****/
}
/**********************************************************************************************************************
 End of function r_fwup_wrap_software_delay
 *********************************************************************************************************************/
