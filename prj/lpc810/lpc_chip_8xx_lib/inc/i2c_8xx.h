/*
 * @brief LPC8xx I2C driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __I2C_8XX_H_
#define __I2C_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CHIP_I2C_8XX CHIP: LPC8xx I2C driver (clock enable/disable only)
 * @ingroup CHIP_8XX_Drivers
 * This driver provides the clock functions needed for I2C support.
 * @{
 */

/**
 * @brief	Initialize I2C Interface
 * @return	Nothing
 * @note	This function enables the I2C clock.
 */
void Chip_I2C_Init(void);

/**
 * @brief	Shutdown I2C Interface
 * @return	Nothing
 * @note	This function disables the I2C clock.
 */
void Chip_I2C_DeInit(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_8XX_H_ */
