#ifndef __SSD1306_OLED_H
#define __SSD1306_OLED_H

#include "ssd1306_oled_conf.h"

typedef struct {
    SPI_HandleTypeDef *Interface;
    GPIO_TypeDef *CS_Port;
    uint16_t CS_Pin;
    GPIO_TypeDef *DC_Port;
    uint16_t DC_Pin;
    GPIO_TypeDef *RES_Port;
    uint16_t RES_Pin;
    uint8_t Framebuffer[1024];
    HAL_LockTypeDef Lock;
} OLED_HandleTypeDef;

HAL_StatusTypeDef OLED_Init(OLED_HandleTypeDef *oled);
HAL_StatusTypeDef OLED_RegInit(OLED_HandleTypeDef *oled);
HAL_StatusTypeDef OLED_Reset(OLED_HandleTypeDef *oled);
HAL_StatusTypeDef OLED_Flush(OLED_HandleTypeDef *oled);
HAL_StatusTypeDef OLED_UploadBuffer(OLED_HandleTypeDef *oled, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
HAL_StatusTypeDef OLED_SetDATAPtr(OLED_HandleTypeDef *oled, uint8_t x1, uint8_t x2, uint8_t y1_page, uint8_t y2_page);
HAL_StatusTypeDef OLED_WriteCMD(OLED_HandleTypeDef *oled, uint8_t command);
HAL_StatusTypeDef OLED_WriteDATA(OLED_HandleTypeDef *oled, uint8_t data);
HAL_StatusTypeDef OLED_WriteBatchDATA(OLED_HandleTypeDef *oled, uint8_t *data, uint16_t length);

#endif