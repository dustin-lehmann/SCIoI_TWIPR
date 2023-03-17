/*
 * firmware_defs.h
 *
 *  Created on: 16 Mar 2023
 *      Author: lehmann_workstation
 */

#ifndef FIRMWARE_DEFS_H_
#define FIRMWARE_DEFS_H_

#include "core.h"

extern DMA_HandleTypeDef hdma_memtomem_dma2_stream0;
#define TWIPR_FIRMWARE_SAMPLE_DMA_STREAM &hdma_memtomem_dma2_stream0




#define TWIPR_FIRMWARE_REGISTER_MAP_GENERAL 0x01
#define TWIPR_FIRMWARE_REGISTER_MAP_CONTROL 0x02

#endif /* FIRMWARE_DEFS_H_ */

