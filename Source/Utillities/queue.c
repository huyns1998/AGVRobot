/******************************************************************************
 *
 * Copyright (c) 2020
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description: Ring buffer queue
 *
 * Author: HoangNH
 *
 * Bug Fixes: Fix buffer overflow. Thanks to Mr.Thien reported.
 *
 * Last Changed By:  $Author: hoangnh $
 * Revision:         $Revision: 1.2 $
 * Last Changed:     $Date: 7/6/2020 $
 *
 ******************************************************************************/

 /******************************************************************************/
 /*                              INCLUDE FILES                                 */
 /******************************************************************************/
#include "queue.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/
/**
 * @func   bufInit
 * @brief  Initializes the FIFO structure
 * @param  pBuffer: Data to be pushed into the FIFO
 * @param  pQueue: Pointer to the FIFO object
 * @param  sizeofElement: Size of a element in the buffer
 * @param  numberOfElement: Size of the buffer
 * @retval None
 */
void
bufInit(
    buffqueue_p pQueue
) {
    pQueue->wHeadIndex = 0;
    pQueue->wTailIndex = 0;
    pQueue->wCountElement = 0;

    memset(pQueue->buffer, 0, QUEUE_BUFFER_SIZE);
}

/**
 * @func   bufNumItems
 * @brief  Returns the number of items in a ring buffer
 * @param  pQueue: The buffer for which the number of items should be returned
 * @return The number of items in the ring buffer
 */
uint16_t
bufNumItems(
    buffqueue_p pQueue
) {
    return pQueue->wCountElement;
}

/**
 * @func   bufIsEmpty
 * @brief  Returns whether a ring buffer is empty
 * @param buffer The buffer for which it should be returned whether it is empty
 * @return 1 if empty; 0 otherwise
 */
uint8_t
bufIsEmpty(
    buffqueue_p pQueue
) {
    return (pQueue->wCountElement == 0) ? 1 : 0;
}

/**
 * @func   bufEnDat
 * @brief  Pushes data to the FIFO
 * @param  pQueue: Pointer to the FIFO object
 * @param  pReceiverData: Received data to be pushed into the FIFO
 * @retval ERR_OK or ERR_BUF_FUL
 */
uint8_t
bufEnDat(
    buffqueue_p pQueue,
    uint8_t* pReceiverData,
    uint8_t sizeofReceiverData
) {
    uint8_t i;

    /* Place data in buffer */
    for (i = 0; i < sizeofReceiverData; i++) {
        pQueue->buffer[pQueue->wHeadIndex] = pReceiverData[i];
        pQueue->wHeadIndex = ((pQueue->wHeadIndex + 1) & (QUEUE_BUFFER_SIZE - 1));
        pQueue->wCountElement++;
    }

    if (pQueue->wCountElement > (QUEUE_BUFFER_SIZE / sizeof(uint8_t))) {
        /* Is going to overwrite the oldest byte */
        /* Increase tail index */
        pQueue->wCountElement = (QUEUE_BUFFER_SIZE / sizeof(uint8_t));
        pQueue->wTailIndex = (pQueue->wTailIndex + sizeofReceiverData) & (QUEUE_BUFFER_SIZE - 1);
    }

    return ERR_OK;
}

/**
 * @func   bufDeDat
 * @brief  Pops data from the FIFO
 * @param  pQueue: Pointer to the FIFO object
 * @param  pBuffer: Data in the FIFO popped into the buffer
 * @retval ERR_OK or ERR_BUF_EMPTY
 */
uint8_t
bufDeDat(
    buffqueue_p pQueue,
    uint8_t* pBuffer,
    uint8_t sizeofBuffer
) {
    uint8_t i;

    if (bufIsEmpty(pQueue)) {
        /* No items */
        return ERR_BUF_EMPTY;
    }

    for (i = 0; i < sizeofBuffer; i++) {
        pBuffer[i] = pQueue->buffer[pQueue->wTailIndex];
        pQueue->wTailIndex = ((pQueue->wTailIndex + 1) & (QUEUE_BUFFER_SIZE - 1));
        pQueue->wCountElement--;
    }

    return ERR_OK;
}

/* END FILE */
