#include <string.h>

#include "usart.h"
#include "spi.h"
#include "gpio.h"

#include "ssd1306_oled.h"

HAL_StatusTypeDef OLED_Init(OLED_HandleTypeDef *oled) {
    OLED_Reset(oled);
    OLED_RegInit(oled);
    OLED_Flush(oled);
    return HAL_OK;
}


HAL_StatusTypeDef OLED_RegInit(OLED_HandleTypeDef *oled) {
  OLED_WriteCMD(oled, 0xae);//--turn off oled panel
  OLED_WriteCMD(oled, 0x00);//---set low column address
  OLED_WriteCMD(oled, 0x10);//---set high column address
  OLED_WriteCMD(oled, 0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WriteCMD(oled, 0x81);//--set contrast control register
  OLED_WriteCMD(oled, 0xcf); // Set SEG Output Current Brightness
  OLED_WriteCMD(oled, 0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  OLED_WriteCMD(oled, 0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  OLED_WriteCMD(oled, 0xa6);//--set normal display
  OLED_WriteCMD(oled, 0xa8);//--set multiplex ratio(1 to 64)
  OLED_WriteCMD(oled, 0x3f);//--1/64 duty
  OLED_WriteCMD(oled, 0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WriteCMD(oled, 0x00);//-not offset
  OLED_WriteCMD(oled, 0xd5);//--set display clock divide ratio/oscillator frequency
  OLED_WriteCMD(oled, 0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  OLED_WriteCMD(oled, 0xd9);//--set pre-charge period
  OLED_WriteCMD(oled, 0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WriteCMD(oled, 0xda);//--set com pins hardware configuration
  OLED_WriteCMD(oled, 0x12);
  OLED_WriteCMD(oled, 0xdb);//--set vcomh
  OLED_WriteCMD(oled, 0x40);//Set VCOM Deselect Level
  OLED_WriteCMD(oled, 0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_WriteCMD(oled, 0x00);//
  OLED_WriteCMD(oled, 0x8d);//--set Charge Pump enable/disable
  OLED_WriteCMD(oled, 0x14);//--set(0x10) disable
  OLED_WriteCMD(oled, 0xa4);// Disable Entire Display On (0xa4/0xa5)
  OLED_WriteCMD(oled, 0xa7);// Disable Inverse Display On (0xa6/a7) 
  OLED_WriteCMD(oled, 0xaf);//--turn on oled panel

  return HAL_OK;
}

HAL_StatusTypeDef OLED_Reset(OLED_HandleTypeDef *oled) {
#ifdef OLED_HARD_RESET
    HAL_GPIO_WritePin(oled->RES_Port, oled->RES_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(oled->RES_Port, oled->RES_Pin, GPIO_PIN_SET);
#endif

    // Not implemented
    return HAL_OK;
}

HAL_StatusTypeDef OLED_Flush(OLED_HandleTypeDef *oled) {
    OLED_SetDATAPtr(oled, 0, 127, 0, 7);
    memset(oled->Framebuffer, 0x00, 1024);
    for(uint16_t i = 0; i < 1024; i++) {
        OLED_WriteDATA(oled, 0x00);
    }
    return HAL_OK;
}

HAL_StatusTypeDef OLED_UploadBuffer(OLED_HandleTypeDef *oled, uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2) {
    uint8_t y1_page = y1 / 8;
    uint8_t y2_page = y2 / 8;
    
    OLED_SetDATAPtr(oled, x1, x2, y1_page, y2_page);
    for(uint8_t p = y1_page; p <= y2_page; p++) {
        for(uint8_t k = x1; k <= x2; k++) {
            uint16_t i = p * 128 + k;
            uint8_t pxdata = 0x00;
            for(uint8_t j = 0; j < 8; j++) {
                        //                    |                 FB BYTE INDEX                |    |    LSBit First          |
                pxdata |= ((oled->Framebuffer[(16 * (i / 128) * 8 + (j * 16) + (i % 128) / 8)] >> (7 - (i % 8))) & 0x01) << j;
            }
            OLED_WriteDATA(oled, pxdata);
        }
    }
    return HAL_OK;
}

HAL_StatusTypeDef OLED_SetDATAPtr(OLED_HandleTypeDef *oled, uint8_t x1, uint8_t x2, uint8_t y1_page, uint8_t y2_page) {
    OLED_WriteCMD(oled, 0x21); // Set column address;
    OLED_WriteCMD(oled, x1); // 0
    OLED_WriteCMD(oled, x2); // 127
    OLED_WriteCMD(oled, 0x22); // Set page address;
    OLED_WriteCMD(oled, y1_page); // 0
    OLED_WriteCMD(oled, y2_page); // 7
    return HAL_OK;
}

HAL_StatusTypeDef OLED_WriteCMD(OLED_HandleTypeDef *oled, uint8_t command) {
    HAL_GPIO_WritePin(oled->CS_Port, oled->CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(oled->DC_Port, oled->DC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(oled->Interface, &command, 0x01, 1000);
    HAL_GPIO_WritePin(oled->CS_Port, oled->CS_Pin, GPIO_PIN_SET);
    return HAL_OK;
}

HAL_StatusTypeDef OLED_WriteDATA(OLED_HandleTypeDef *oled, uint8_t data) {
    HAL_GPIO_WritePin(oled->CS_Port, oled->CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(oled->DC_Port, oled->DC_Pin, GPIO_PIN_SET);
    HAL_SPI_Transmit(oled->Interface, &data, 0x01, 1000);
    HAL_GPIO_WritePin(oled->CS_Port, oled->CS_Pin, GPIO_PIN_SET);
    return HAL_OK;
}

HAL_StatusTypeDef OLED_WriteBatchDATA(OLED_HandleTypeDef *oled, uint8_t *data, uint16_t length) {
    HAL_GPIO_WritePin(oled->CS_Port, oled->CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(oled->DC_Port, oled->DC_Pin, GPIO_PIN_SET);
    HAL_SPI_Transmit(oled->Interface, data, length, 1000);
    HAL_GPIO_WritePin(oled->CS_Port, oled->CS_Pin, GPIO_PIN_SET);
    return HAL_OK;
}