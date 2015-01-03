/*
 * @brief LPC8xx SPI driver
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

#ifndef __SPI_8XX_H_
#define __SPI_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SPI_8XX CHIP: LPC8xx SPI driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */
/**
 * @brief SPI register block structure
 */
typedef struct {					/*!< SPI Structure */
	__IO uint32_t  CFG;				/*!< SPI Configuration register*/
	__IO uint32_t  DLY;				/*!< SPI Delay register*/
	__IO uint32_t  STAT;			/*!< SPI Status. register*/
	__IO uint32_t  INTENSET;		/*!< SPI Interrupt Enable.Set register*/
	__O  uint32_t  INTENCLR;		/*!< SPI Interrupt Enable Clear. register*/
	__I  uint32_t  RXDAT;			/*!< SPI Receive Data register*/
	__IO uint32_t  TXDATCTL;		/*!< SPI Transmit Data with Control register*/
	__IO uint32_t  TXDAT;			/*!< SPI Transmit Data register*/
	__IO uint32_t  TXCTRL;			/*!< SPI Transmit Control register*/
	__IO uint32_t  DIV;				/*!< SPI clock Divider register*/
	__I  uint32_t  INTSTAT;			/*!< SPI Interrupt Status register*/
} LPC_SPI_T;

/**
 * Macro defines for SPI Configuration register
 */
/* SPI CFG Register BitMask */
#define SPI_CFG_BITMASK     ((uint32_t) 0x1BD)
/** SPI enable  */
#define SPI_CFG_SPI_EN      ((uint32_t) (1 << 0))
/** SPI Slave Mode Select */
#define SPI_CFG_SLAVE_EN   ((uint32_t) 0)
/** SPI Master Mode Select */
#define SPI_CFG_MASTER_EN   ((uint32_t) (1 << 2))
/** SPI MSB First mode enable */
#define SPI_CFG_MSB_FIRST_EN   ((uint32_t) 0)	/*Data will be transmitted and received in standard order (MSB first).*/
/** SPI LSB First mode enable */
#define SPI_CFG_LSB_FIRST_EN   ((uint32_t) (1 << 3))/*Data will be transmitted and received in reverse order (LSB first).*/
/** SPI Clock Phase Select*/
#define SPI_CFG_CPHA_FIRST   ((uint32_t) (0))	/*Capture data on the first edge, Change data on the following edge*/
#define SPI_CFG_CPHA_SECOND  ((uint32_t) (1 << 4))	/*Change data on the first edge, Capture data on the following edge*/
/** SPI Clock Polarity Select*/
#define SPI_CFG_CPOL_LO     ((uint32_t) (0))	/* The rest state of the clock (between frames) is low.*/
#define SPI_CFG_CPOL_HI     ((uint32_t) (1 << 5))	/* The rest state of the clock (between frames) is high.*/
/** SPI control 1 loopback mode enable  */
#define SPI_CFG_LBM_EN      ((uint32_t) (1 << 7))
/** SPI SSEL Polarity Select*/
#define SPI_CFG_SPOL_LO     ((uint32_t) (0))		/* SSEL is active Low */
#define SPI_CFG_SPOL_HI     ((uint32_t) (1 << 8))	/* SSEL is active High */

/**
 * Macro defines for SPI Delay register
 */
/** SPI DLY Register Mask	*/
#define  SPI_DLY_BITMASK        ((uint32_t) 0xFFFF)
/** Controls the amount of time between SSEL assertion and the beginning of a data frame.	*/
#define  SPI_DLY_PRE_DELAY(n)        ((uint32_t) ((n) & 0x0F))				/* Time Unit: SPI clock time */
/** Controls the amount of time between the end of a data frame and SSEL deassertion.	*/
#define  SPI_DLY_POST_DELAY(n)       ((uint32_t) (((n) & 0x0F) << 4))		/* Time Unit: SPI clock time */
/** Controls the minimum amount of time between adjacent data frames.	*/
#define  SPI_DLY_FRAME_DELAY(n)      ((uint32_t) (((n) & 0x0F) << 8))		/* Time Unit: SPI clock time */
/** Controls the minimum amount of time that the SSEL is deasserted between transfers.	*/
#define  SPI_DLY_TRANSFER_DELAY(n)   ((uint32_t) (((n) & 0x0F) << 12))	/* Time Unit: SPI clock time */

/**
 * Macro defines for SPI Status register
 */
/* SPI STAT Register BitMask */
#define SPI_STAT_BITMASK        ((uint32_t) 0x1FF)
/* Receiver Ready Flag */
#define SPI_STAT_RXRDY          ((uint32_t) (1 << 0))	/* Data is ready for read */
/* Transmitter Ready Flag */
#define SPI_STAT_TXRDY          ((uint32_t) (1 << 1))	/* Data may be written to transmit buffer */
/* Receiver Overrun interrupt flag */
#define SPI_STAT_RXOV           ((uint32_t) (1 << 2))	/* Data comes while receiver buffer is in used */
/* Transmitter Underrun interrupt flag (In Slave Mode only) */
#define SPI_STAT_TXUR           ((uint32_t) (1 << 3))	/* There is no data to be sent in the next input clock */
/* Slave Select Assert */
#define SPI_STAT_SSA            ((uint32_t) (1 << 4))	/* There is SSEL transition from deasserted to asserted */
/* Slave Select Deassert */
#define SPI_STAT_SSD            ((uint32_t) (1 << 5))	/* There is SSEL transition from asserted to deasserted */
/* Stalled status flag */
#define SPI_STAT_STALLED        ((uint32_t) (1 << 6))	/* SPI is currently in a stall condition. */
/* End Transfer flag. */
#define SPI_STAT_EOT            ((uint32_t) (1 << 7))	/* The current frame is the last frame of the current  transfer. */
/* Idle status flag. */
#define SPI_STAT_LE         ((uint32_t) (1 << 8))	/* SPI master function is fully idle. */

/* Clear RXOV Flag */
#define SPI_STAT_CLR_RXOV       ((uint32_t) (1 << 2))
/* Clear TXUR Flag */
#define SPI_STAT_CLR_TXUR       ((uint32_t) (1 << 3))
/* Clear SSA Flag */
#define SPI_STAT_CLR_SSA        ((uint32_t) (1 << 4))
/* Clear SSD Flag */
#define SPI_STAT_CLR_SSD        ((uint32_t) (1 << 5))
/*Force an end to the current transfer */
#define SPI_STAT_FORCE_EOT      ((uint32_t) (1 << 7))

/**
 * Macro defines for SPI Interrupt Enable read and Set register
 */
/* SPI INTENSET Register BitMask */
#define SPI_INTENSET_BITMASK    ((uint32_t) 0x3F)
/** Enable Interrupt when receiver data is available */
#define SPI_INTENSET_RXDYEN     ((uint32_t) (1 << 0))
/** Enable Interrupt when the transmitter holding register is available. */
#define SPI_INTENSET_TXDYEN     ((uint32_t) (1 << 1))
/**  Enable Interrupt when a receiver overrun occurs */
#define SPI_INTENSET_RXOVEN     ((uint32_t) (1 << 2))
/**  Enable Interrupt when a transmitter underrun occurs (In Slave Mode Only)*/
#define SPI_INTENSET_TXUREN     ((uint32_t) (1 << 3))
/**  Enable Interrupt when the Slave Select is asserted.*/
#define SPI_INTENSET_SSAEN      ((uint32_t) (1 << 2))
/**  Enable Interrupt when the Slave Select is deasserted..*/
#define SPI_INTENSET_SSDEN      ((uint32_t) (1 << 2))

/**
 * Macro defines for SPI Interrupt Enable Clear register
 */
/* SPI INTENCLR Register BitMask */
#define SPI_INTENCLR_BITMASK    ((uint32_t) 0x3F)
/** Disable Interrupt when receiver data is available */
#define SPI_INTENCLR_RXDYEN     ((uint32_t) (1 << 0))
/** Disable Interrupt when the transmitter holding register is available. */
#define SPI_INTENCLR_TXDYEN     ((uint32_t) (1 << 1))
/** Disable Interrupt when a receiver overrun occurs */
#define SPI_INTENCLR_RXOVEN     ((uint32_t) (1 << 2))
/** Disable Interrupt when a transmitter underrun occurs (In Slave Mode Only)*/
#define SPI_INTENCLR_TXUREN     ((uint32_t) (1 << 3))
/** Disable Interrupt when the Slave Select is asserted.*/
#define SPI_INTENCLR_SSAEN      ((uint32_t) (1 << 2))
/** Disable Interrupt when the Slave Select is deasserted..*/
#define SPI_INTENCLR_SSDEN      ((uint32_t) (1 << 2))

/**
 * Macro defines for SPI Receiver Data register
 */
/* SPI RXDAT Register BitMask */
#define SPI_RXDAT_BITMASK       ((uint32_t) 0x11FFFF)
/** Receiver Data  */
#define SPI_RXDAT_DATA(n)       ((uint32_t) ((n) & 0xFFFF))
/** The state of SSEL pin  */
#define SPI_RXDAT_RXSSELN_ACTIVE    ((uint32_t) 0)		/* SSEL is in active state */
#define SPI_RXDAT_RXSSELN_INACTIVE  ((uint32_t) (1 << 16))	/* SSEL is in inactive state */
/** Start of Transfer flag  */
#define SPI_RXDAT_SOT           ((uint32_t) (1 << 20))	/* This is the first frame received after SSEL is asserted */

/**
 * Macro defines for SPI Transmitter Data and Control register
 */
/* SPI TXDATCTL Register BitMask */
#define SPI_TXDATCTL_BITMASK    ((uint32_t) 0xF71FFFF)
/* SPI Transmit Data */
#define SPI_TXDATCTL_DATA(n)    ((uint32_t) ((n) & 0xFFFF))
/*Assert/Deassert SSL pin*/
#define SPI_TXDATCTL_ASSERT_SSEL    ((uint32_t) 0)
#define SPI_TXDATCTL_DEASSERT_SSEL  ((uint32_t) (1 << 16))
/** End of Transfer flag (TRANSFER_DELAY is applied after sending the current frame)  */
#define SPI_TXDATCTL_EOT            ((uint32_t) (1 << 20))	/* This is the last frame of the current transfer */
/** End of Frame flag (FRAME_DELAY is applied after sending the current part) */
#define SPI_TXDATCTL_EOF            ((uint32_t) (1 << 21))	/* This is the last part of the current frame */
/** Receive Ignore Flag */
#define SPI_TXDATCTL_RXIGNORE       ((uint32_t) (1 << 22))	/* Received data is ignored */
/** Receive Ignore Flag */
#define SPI_TXDATCTL_FLEN(n)        ((uint32_t) (((n) & 0x0F) << 24))	/* Frame Length -1 */

/**
 * Macro defines for SPI Transmitter Data Register
 */
/* SPI Transmit Data */
#define SPI_TXDAT_DATA(n)   ((uint32_t) ((n) & 0xFFFF))

/**
 * Macro defines for SPI Transmitter Control register
 */
/* SPI TXDATCTL Register BitMask */
#define SPI_TXCTL_BITMASK   ((uint32_t) 0xF71FF00)
/*Assert/Deassert SSL pin*/
#define SPI_TXCTL_ASSERT_SSEL   ((uint32_t) 0)
#define SPI_TXCTL_DEASSERT_SSEL ((uint32_t) (1 << 16))
/** End of Transfer flag (TRANSFER_DELAY is applied after sending the current frame)  */
#define SPI_TXCTL_EOT           ((uint32_t) (1 << 20))	/* This is the last frame of the current transfer */
/** End of Frame flag (FRAME_DELAY is applied after sending the current part) */
#define SPI_TXCTL_EOF           ((uint32_t) (1 << 21))	/* This is the last part of the current frame */
/** Receive Ignore Flag */
#define SPI_TXCTL_RXIGNORE      ((uint32_t) (1 << 22))	/* Received data is ignored */
/** Receive Ignore Flag */
#define SPI_TXCTL_FLEN(n)       ((uint32_t) (((n) & 0x0F) << 24))	/* Frame Length -1 */

/**
 * Macro defines for SPI Divider register
 */
/** Rate divider value  (In Master Mode only)*/
#define SPI_DIV_VAL(n)          ((uint32_t) ((n) & 0xFFFF))	/* SPI_CLK = PCLK/(DIV_VAL+1)*/

/**
 * Macro defines for SPI Interrupt Status register
 */
/* SPI INTSTAT Register Bitmask */
#define SPI_INTSTAT_BITMASK     ((uint32_t) 0x3F)
/* Receiver Ready Flag */
#define SPI_INTSTAT_RXRDY           ((uint32_t) (1 << 0))	/* Data is ready for read */
/* Transmitter Ready Flag */
#define SPI_INTSTAT_TXRDY           ((uint32_t) (1 << 1))	/* Data may be written to transmit buffer */
/* Receiver Overrun interrupt flag */
#define SPI_INTSTAT_RXOV            ((uint32_t) (1 << 2))	/* Data comes while receiver buffer is in used */
/* Transmitter Underrun interrupt flag (In Slave Mode only) */
#define SPI_INTSTAT_TXUR            ((uint32_t) (1 << 3))	/* There is no data to be sent in the next input clock */
/* Slave Select Assert */
#define SPI_INTSTAT_SSA         ((uint32_t) (1 << 4))	/* There is SSEL transition from deasserted to asserted */
/* Slave Select Deassert */
#define SPI_INTSTAT_SSD         ((uint32_t) (1 << 5))	/* There is SSEL transition from asserted to deasserted */

/** @brief SPI Mode*/
typedef enum {
	SPI_MODE_MASTER = SPI_CFG_MASTER_EN,		/* Master Mode */
	SPI_MODE_SLAVE = SPI_CFG_SLAVE_EN,			/* Slave Mode */
} SPI_MODE_T;

/** @brief SPI Clock Mode*/
typedef enum IP_SPI_CLOCK_MODE {
	SPI_CLOCK_CPHA0_CPOL0 = SPI_CFG_CPOL_LO | SPI_CFG_CPHA_FIRST,		/**< CPHA = 0, CPOL = 0 */
	SPI_CLOCK_CPHA0_CPOL1 = SPI_CFG_CPOL_HI | SPI_CFG_CPHA_FIRST,		/**< CPHA = 0, CPOL = 1 */
	SPI_CLOCK_CPHA1_CPOL0 = SPI_CFG_CPOL_LO | SPI_CFG_CPHA_SECOND,			/**< CPHA = 1, CPOL = 0 */
	SPI_CLOCK_CPHA1_CPOL1 = SPI_CFG_CPOL_HI | SPI_CFG_CPHA_SECOND,			/**< CPHA = 1, CPOL = 1 */
	SPI_CLOCK_MODE0 = SPI_CLOCK_CPHA0_CPOL0,/**< alias */
	SPI_CLOCK_MODE1 = SPI_CLOCK_CPHA1_CPOL0,/**< alias */
	SPI_CLOCK_MODE2 = SPI_CLOCK_CPHA0_CPOL1,/**< alias */
	SPI_CLOCK_MODE3 = SPI_CLOCK_CPHA1_CPOL1,/**< alias */
} SPI_CLOCK_MODE_T;

/** @brief SPI Data Order Mode*/
typedef enum IP_SPI_DATA_ORDER {
	SPI_DATA_MSB_FIRST = SPI_CFG_MSB_FIRST_EN,			/* Standard Order */
	SPI_DATA_LSB_FIRST = SPI_CFG_LSB_FIRST_EN,			/* Reverse Order */
} SPI_DATA_ORDER_T;

/** @brief SPI SSEL Polarity definition*/
typedef enum IP_SPI_SSEL_POL {
	SPI_SSEL_ACTIVE_LO = SPI_CFG_SPOL_LO,			/* SSEL is active Low*/
	SPI_SSEL_ACTIVE_HI = SPI_CFG_SPOL_HI,			/* SSEL is active  High */
} SPI_SSEL_POL_T;

/**
 * @brief SPI Configure Struct
 */
typedef struct {
	SPI_MODE_T             Mode;			/* Mode Select */
	SPI_CLOCK_MODE_T       ClockMode;		/* CPHA CPOL Select */
	SPI_DATA_ORDER_T       DataOrder;		/* MSB/LSB First */
	SPI_SSEL_POL_T         SSELPol;		/* SSEL Polarity Select */
	uint16_t                ClkDiv;			/* SPI Clock Divider Value */
} SPI_CONFIG_T;

/**
 * @brief SPI Delay Configure Struct
 */
typedef struct {
	uint8_t     PreDelay;				/* Pre-delay value in SPI clock time */
	uint8_t     PostDelay;				/* Post-delay value in SPI clock time */
	uint8_t     FrameDelay;				/* Delay value between frames of a transfer in SPI clock time */
	uint8_t     TransferDelay;			/* Delay value between transfers in SPI clock time */
} SPI_DELAY_CONFIG_T;

/**
 * @brief SPI data setup structure
 */
typedef struct {
	uint16_t  *pTx;	/**< Pointer to data buffer*/
	uint32_t  TxCnt;/* Transmit Counter */
	uint16_t  *pRx;	/**< Pointer to data buffer*/
	uint32_t  RxCnt;/* Transmit Counter */
	uint32_t  Length;	/**< Data Length*/
	uint16_t  DataSize;	/** < The size of a frame (1-16)*/
} SPI_DATA_SETUP_T;

/**
 * @brief   Initialize the SPI
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	pConfig			: SPI Configuration
 * @return	Nothing
 */
void Chip_SPI_Init(LPC_SPI_T *pSPI, SPI_CONFIG_T *pConfig);

/**
 * @brief	Calculate the divider for SPI clock
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	bitRate	: Expected clock rate
 * @return	Divider value
 */
uint32_t Chip_SPI_CalClkRateDivider(LPC_SPI_T *pSPI, uint32_t bitRate);

/**
 * @brief	Config SPI Delay parameters
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	pConfig	: SPI Delay Configure Struct
 * @return	 Nothing
 * @note	The SPI controller is disabled
 */
void Chip_SPI_DelayConfig(LPC_SPI_T *pSPI, SPI_DELAY_CONFIG_T *pConfig);

/**
 * @brief	Disable SPI operation
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	The SPI controller is disabled
 */
void Chip_SPI_DeInit(LPC_SPI_T *pSPI);

/**
 * @brief   Enable/Disable SPI interrupt
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	IntMask		: Interrupt mask
 * @param	NewState		: ENABLE or DISABLE interrupt
 * @return	Nothing
 */
void Chip_SPI_Int_Cmd(LPC_SPI_T *pSPI, uint32_t IntMask, FunctionalState NewState);

/**
 * @brief	Enable SPI peripheral
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_Enable(LPC_SPI_T *pSPI)
{
	pSPI->CFG |= SPI_CFG_SPI_EN;
}

/**
 * @brief	Disable SPI peripheral
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_Disable(LPC_SPI_T *pSPI)
{
	pSPI->CFG &= (~SPI_CFG_SPI_EN) & SPI_CFG_BITMASK;
}

/**
 * @brief	Enable loopback mode
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	Serial input is taken from the serial output (MOSI or MISO) rather
 * than the serial input pin
 */
STATIC INLINE void Chip_SPI_EnableLoopBack(LPC_SPI_T *pSPI)
{
	pSPI->CFG |= SPI_CFG_LBM_EN;
}

/**
 * @brief	Disable loopback mode
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @return	Nothing
 * @note	Serial input is taken from the serial output (MOSI or MISO) rather
 * than the serial input pin
 */
STATIC INLINE void Chip_SPI_DisableLoopBack(LPC_SPI_T *pSPI)
{
	pSPI->CFG &= (~SPI_CFG_LBM_EN) & SPI_CFG_BITMASK;
}

/**
 * @brief	Get the current status of SPI controller
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @return	SPI Status (Or-ed bit value of SPI_STAT_*)
 */
STATIC INLINE uint32_t Chip_SPI_GetStatus(LPC_SPI_T *pSPI)
{
	return pSPI->STAT;
}

/**
 * @brief	Clear SPI status
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	Flag	: Clear Flag (Or-ed bit value of SPI_STAT_CLR_*)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_ClearStatus(LPC_SPI_T *pSPI, uint32_t Flag)
{
	pSPI->STAT |= Flag;
}

/**
 * @brief	Set control information including SSEL, EOT, EOF RXIGNORE and FLEN
 * @param	pSPI	: The base of SPI peripheral on the chip
 * @param	Flen	: Data size (1-16)
 * @param	Flag	: Flag control (Or-ed values of SPI_TXCTL_*)
 * @note	The control information has no effect unless data is later written to TXDAT
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SetControlInfo(LPC_SPI_T *pSPI, uint8_t Flen, uint32_t Flag)
{
	pSPI->TXCTRL = Flag | SPI_TXDATCTL_FLEN(Flen - 1);
}

/**
 * @brief	 Send the first Frame of a transfer (Rx Ignore)
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @param	DataSize	:  Data Size (1-16)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendFirstFrame_RxIgnore(LPC_SPI_T *pSPI, uint16_t Data, uint8_t DataSize)
{
	pSPI->TXDATCTL = SPI_TXDATCTL_ASSERT_SSEL | SPI_TXDATCTL_EOF | SPI_TXDATCTL_RXIGNORE | SPI_TXDATCTL_FLEN(
		DataSize - 1) | SPI_TXDATCTL_DATA(Data);
}

/**
 * @brief	 Send the first Frame of a transfer
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @param	DataSize	:  Data Size (1-16)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendFirstFrame(LPC_SPI_T *pSPI, uint16_t Data, uint8_t DataSize)
{
	pSPI->TXDATCTL = SPI_TXDATCTL_ASSERT_SSEL | SPI_TXDATCTL_EOF | SPI_TXDATCTL_FLEN(DataSize - 1) | SPI_TXDATCTL_DATA(
		Data);
}

/**
 * @brief	 Send the middle Frame of a transfer
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendMidFrame(LPC_SPI_T *pSPI, uint16_t Data)
{
	pSPI->TXDAT = SPI_TXDAT_DATA(Data);
}

/**
 * @brief	 Send the last Frame of a transfer (Rx Ignore)
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @param	DataSize	:  Data Size (1-16)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendLastFrame_RxIgnore(LPC_SPI_T *pSPI, uint16_t Data, uint8_t DataSize)
{
	pSPI->TXDATCTL = SPI_TXDATCTL_ASSERT_SSEL | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT | SPI_TXDATCTL_RXIGNORE |
					 SPI_TXDATCTL_FLEN(DataSize - 1) | SPI_TXDATCTL_DATA(Data);
}

/**
 * @brief	 Send the last Frame of a transfer
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @param	Data	:  Transmit data
 * @param	DataSize	:  Data Size (1-16)
 * @return	Nothing
 */
STATIC INLINE void Chip_SPI_SendLastFrame(LPC_SPI_T *pSPI, uint16_t Data, uint8_t DataSize)
{
	pSPI->TXDATCTL = SPI_TXDATCTL_ASSERT_SSEL | SPI_TXDATCTL_EOF | SPI_TXDATCTL_EOT |
					 SPI_TXDATCTL_FLEN(DataSize - 1) | SPI_TXDATCTL_DATA(Data);
}

/**
 * @brief	 Read data received
 * @param	pSPI		: The base of SPI peripheral on the chip
 * @return	Receive data
 */
STATIC INLINE uint16_t Chip_SPI_ReceiveFrame(LPC_SPI_T *pSPI)
{
	return SPI_RXDAT_DATA(pSPI->RXDAT);
}

/**
 * @brief   SPI Interrupt Read/Write
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	xf_setup		: Pointer to a SPI_DATA_SETUP_T structure that contains specified
 *                          information about transmit/receive data	configuration
 * @return	SUCCESS or ERROR
 */
Status Chip_SPI_Int_RWFrames(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *xf_setup);

/**
 * @brief   SPI Polling Read/Write in blocking mode
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	pXfSetup		: Pointer to a SPI_DATA_SETUP_T structure that contains specified
 *                          information about transmit/receive data	configuration
 * @return	Actual data length has been transferred
 * @note
 * This function can be used in both master and slave mode. It starts with writing phase and after that,
 * a reading phase is generated to read any data available in RX_FIFO. All needed information is prepared
 * through xf_setup param.
 */
uint32_t Chip_SPI_RWFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup);

/**
 * @brief   SPI Polling Write in blocking mode
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	pXfSetup			:Pointer to a SPI_DATA_SETUP_T structure that contains specified
 *                          information about transmit/receive data	configuration
 * @return	Actual data length has been transferred
 * @note
 * This function can be used in both master and slave mode. First, a writing operation will send
 * the needed data. After that, a dummy reading operation is generated to clear data buffer
 */
uint32_t Chip_SPI_WriteFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup);

/**
 * @brief   SPI Polling Read in blocking mode
 * @param	pSPI			: The base SPI peripheral on the chip
 * @param	pXfSetup			:Pointer to a SPI_DATA_SETUP_T structure that contains specified
 *                          information about transmit/receive data	configuration
 * @return	Actual data length has been read
 * @note
 * This function can be used in both master and slave mode. First, a writing operation will send
 * the needed data. After that, a dummy reading operation is generated to clear data buffer
 */
uint32_t Chip_SPI_ReadFrames_Blocking(LPC_SPI_T *pSPI, SPI_DATA_SETUP_T *pXfSetup);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_8XX_H_ */
