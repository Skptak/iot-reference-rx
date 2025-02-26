/***********************************************************************************************************************
  * Copyright 2023 Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef FRTOS_CONFIG_RM_LITTLEFS_FLASH_CONFIG_H_
#define FRTOS_CONFIG_RM_LITTLEFS_FLASH_CONFIG_H_

#define LFS_FLASH_READ_SIZE				(1)
#define LFS_FLASH_PROGRAM_SIZE			(4)
#define LFS_FLASH_BLOCK_SIZE			(128)
#define LFS_FLASH_BLOCK_COUNT			(70)
#define RM_LITTLEFS_FLASH_DATA_START	FLASH_DF_BLOCK_0  //START block is fixed at FLASH_DF_BLOCK_0 in this version

#if (LFS_FLASH_BLOCK_COUNT * LFS_FLASH_BLOCK_SIZE) > BSP_DATA_FLASH_SIZE_BYTES
#error "Entered block count is too big!"
#elif ( LFS_FLASH_BLOCK_COUNT < 70 )
#error "Entered block count is too small!"
#endif

#endif /* FRTOS_CONFIG_RM_LITTLEFS_FLASH_CONFIG_H_ */
