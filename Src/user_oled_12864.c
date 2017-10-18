#include "i2c.h"
#include "user_board.h"
#include "user_oled_12864.h"

const unsigned char fontArray[][6] =
{
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x2f, 0x00, 0x00},
  {0x00, 0x00, 0x07, 0x00, 0x07, 0x00},
  {0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14},
  {0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12},
  {0x00, 0x23, 0x13, 0x08, 0x64, 0x62},
  {0x00, 0x36, 0x49, 0x55, 0x22, 0x50},
  {0x00, 0x00, 0x05, 0x03, 0x00, 0x00},
  {0x00, 0x00, 0x1c, 0x22, 0x41, 0x00},
  {0x00, 0x00, 0x41, 0x22, 0x1c, 0x00},
  {0x00, 0x14, 0x08, 0x3E, 0x08, 0x14},
  {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08},
  {0x00, 0x00, 0x00, 0xA0, 0x60, 0x00},
  {0x00, 0x08, 0x08, 0x08, 0x08, 0x08},
  {0x00, 0x00, 0x60, 0x60, 0x00, 0x00},
  {0x00, 0x20, 0x10, 0x08, 0x04, 0x02},
  {0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E},
  {0x00, 0x00, 0x42, 0x7F, 0x40, 0x00},
  {0x00, 0x42, 0x61, 0x51, 0x49, 0x46},
  {0x00, 0x21, 0x41, 0x45, 0x4B, 0x31},
  {0x00, 0x18, 0x14, 0x12, 0x7F, 0x10},
  {0x00, 0x27, 0x45, 0x45, 0x45, 0x39},
  {0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30},
  {0x00, 0x01, 0x71, 0x09, 0x05, 0x03},
  {0x00, 0x36, 0x49, 0x49, 0x49, 0x36},
  {0x00, 0x06, 0x49, 0x49, 0x29, 0x1E},
  {0x00, 0x00, 0x36, 0x36, 0x00, 0x00},
  {0x00, 0x00, 0x56, 0x36, 0x00, 0x00},
  {0x00, 0x08, 0x14, 0x22, 0x41, 0x00},
  {0x00, 0x14, 0x14, 0x14, 0x14, 0x14},
  {0x00, 0x00, 0x41, 0x22, 0x14, 0x08},
  {0x00, 0x02, 0x01, 0x51, 0x09, 0x06},
  {0x00, 0x32, 0x49, 0x59, 0x51, 0x3E},
  {0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C},
  {0x00, 0x7F, 0x49, 0x49, 0x49, 0x36},
  {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22},
  {0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C},
  {0x00, 0x7F, 0x49, 0x49, 0x49, 0x41},
  {0x00, 0x7F, 0x09, 0x09, 0x09, 0x01},
  {0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A},
  {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F},
  {0x00, 0x00, 0x41, 0x7F, 0x41, 0x00},
  {0x00, 0x20, 0x40, 0x41, 0x3F, 0x01},
  {0x00, 0x7F, 0x08, 0x14, 0x22, 0x41},
  {0x00, 0x7F, 0x40, 0x40, 0x40, 0x40},
  {0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F},
  {0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F},
  {0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E},
  {0x00, 0x7F, 0x09, 0x09, 0x09, 0x06},
  {0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E},
  {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46},
  {0x00, 0x46, 0x49, 0x49, 0x49, 0x31},
  {0x00, 0x01, 0x01, 0x7F, 0x01, 0x01},
  {0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F},
  {0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F},
  {0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F},
  {0x00, 0x63, 0x14, 0x08, 0x14, 0x63},
  {0x00, 0x07, 0x08, 0x70, 0x08, 0x07},
  {0x00, 0x61, 0x51, 0x49, 0x45, 0x43},
  {0x00, 0x00, 0x7F, 0x41, 0x41, 0x00},
  {0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55},
  {0x00, 0x00, 0x41, 0x41, 0x7F, 0x00},
  {0x00, 0x04, 0x02, 0x01, 0x02, 0x04},
  {0x00, 0x40, 0x40, 0x40, 0x40, 0x40},
  {0x00, 0x00, 0x01, 0x02, 0x04, 0x00},
  {0x00, 0x20, 0x54, 0x54, 0x54, 0x78},
  {0x00, 0x7F, 0x48, 0x44, 0x44, 0x38},
  {0x00, 0x38, 0x44, 0x44, 0x44, 0x20},
  {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F},
  {0x00, 0x38, 0x54, 0x54, 0x54, 0x18},
  {0x00, 0x08, 0x7E, 0x09, 0x01, 0x02},
  {0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C},
  {0x00, 0x7F, 0x08, 0x04, 0x04, 0x78},
  {0x00, 0x00, 0x44, 0x7D, 0x40, 0x00},
  {0x00, 0x40, 0x80, 0x84, 0x7D, 0x00},
  {0x00, 0x7F, 0x10, 0x28, 0x44, 0x00},
  {0x00, 0x00, 0x41, 0x7F, 0x40, 0x00},
  {0x00, 0x7C, 0x04, 0x18, 0x04, 0x78},
  {0x00, 0x7C, 0x08, 0x04, 0x04, 0x78},
  {0x00, 0x38, 0x44, 0x44, 0x44, 0x38},
  {0x00, 0xFC, 0x24, 0x24, 0x24, 0x18},
  {0x00, 0x18, 0x24, 0x24, 0x18, 0xFC},
  {0x00, 0x7C, 0x08, 0x04, 0x04, 0x08},
  {0x00, 0x48, 0x54, 0x54, 0x54, 0x20},
  {0x00, 0x04, 0x3F, 0x44, 0x40, 0x20},
  {0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C},
  {0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C},
  {0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C},
  {0x00, 0x44, 0x28, 0x10, 0x28, 0x44},
  {0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C},
  {0x00, 0x44, 0x64, 0x54, 0x4C, 0x44},
  {0x14, 0x14, 0x14, 0x14, 0x14, 0x14}
};

void OLED_Init(OLED_HandleTypeDef * oled) {
  oled -> Lock = 0;
  oled -> TxFlag = 0;
  HAL_Delay(100);
  // Notice: I have no SSD1307 datasheet so far, and these are magic for now.
  OLED_Write_Command(oled, 0xAE);
  OLED_Write_Command(oled, 0x20);
  OLED_Write_Command(oled, 0x10);
  OLED_Write_Command(oled, 0xB0);
  OLED_Write_Command(oled, 0xC8);
  OLED_Write_Command(oled, 0x00);
  OLED_Write_Command(oled, 0x10);
  OLED_Write_Command(oled, 0x40);
  OLED_Write_Command(oled, 0x81);
  OLED_Write_Command(oled, 0xFF);
  OLED_Write_Command(oled, 0xA1);
  OLED_Write_Command(oled, 0xA6);
  OLED_Write_Command(oled, 0xA8);
  OLED_Write_Command(oled, 0x3F);
  OLED_Write_Command(oled, 0xA4);
  OLED_Write_Command(oled, 0xD3);
  OLED_Write_Command(oled, 0x00);
  OLED_Write_Command(oled, 0xD5);
  OLED_Write_Command(oled, 0xF0);
  OLED_Write_Command(oled, 0xD9);
  OLED_Write_Command(oled, 0x22);
  OLED_Write_Command(oled, 0xDA);
  OLED_Write_Command(oled, 0x12);
  OLED_Write_Command(oled, 0xDB);
  OLED_Write_Command(oled, 0x20);
  OLED_Write_Command(oled, 0x8D);
  OLED_Write_Command(oled, 0x14);
  OLED_Write_Command(oled, 0xAF);
}

void OLED_Position_Set(OLED_HandleTypeDef * oled, uint8_t posX, uint8_t posY){
  OLED_Write_Command(oled, 0xB0 + posY);
  OLED_Write_Command(oled, ((posX & 0xF0) >> 0x04) | 0x10);
  OLED_Write_Command(oled, (posX & 0x0F) | 0x01);
}

void OLED_Fill(OLED_HandleTypeDef * oled, uint8_t fillData) {
  for (uint8_t i = 0; i < 8; i ++) {
    OLED_Write_Command(oled, 0xB0 + i);
    OLED_Write_Command(oled, 0x00);
    OLED_Write_Command(oled, 0x10);
    for (uint8_t j = 0; j < 128; j ++) {
      OLED_Write_Data(oled, fillData);
    }
  }
}

void OLED_Clear(OLED_HandleTypeDef * oled) {
  OLED_Fill(oled, 0x00);
}

void OLED_Power(OLED_HandleTypeDef * oled, uint8_t powerState) {
  OLED_Write_Command(oled, 0x8D);

  switch (powerState) {
    case 1:
      OLED_Write_Command(oled, 0x14);
      OLED_Write_Command(oled, 0xAF);
      break;
    case 0:
      OLED_Write_Command(oled, 0x10);
      OLED_Write_Command(oled, 0xAE);
      break;
  }
}

void OLED_String_Display(OLED_HandleTypeDef * oled, uint8_t posX, uint8_t posY, char * buf) {
  uint8_t i = 0;
  while (buf[i] != '\0') {
    uint8_t ch = buf[i] - 32;
    if (posX > 126) {
      posX = 0;
      posY ++;
    }
    OLED_Position_Set(oled, posX, posY);
    for (uint8_t j = 0; j < 6; j ++) {
      OLED_Write_Data(oled, fontArray[ch][j]);
    }
    posX += 6;
    i ++;
  }
}

HAL_StatusTypeDef OLED_Write_Command(OLED_HandleTypeDef * oled, uint8_t cmd) {
  __HAL_LOCK(oled);
  uint8_t buf[2] = {0x00, cmd};
  HAL_I2C_Master_Transmit_DMA(&OLED_I2C_INTERFACE, OLED_SLAVE_ADDR, buf, 0x02);
  uint32_t tickStart = HAL_GetTick();
  while (!oled -> TxFlag) {
    if ((HAL_GetTick() - tickStart) > OLED_MAX_TIMEOUT_TICKS) {
      return HAL_TIMEOUT; // Oops!
    }
  }
  oled -> TxFlag = 0;
  __HAL_UNLOCK(oled);
  return HAL_OK;
}

HAL_StatusTypeDef OLED_Write_Data(OLED_HandleTypeDef * oled, uint8_t data) {
  __HAL_LOCK(oled);
  uint8_t buf[2] = {0x40, data};
  HAL_I2C_Master_Transmit_DMA(&OLED_I2C_INTERFACE, OLED_SLAVE_ADDR, buf, 0x02);
  uint32_t tickStart = HAL_GetTick();
  while (!oled -> TxFlag) {
    if ((HAL_GetTick() - tickStart) > OLED_MAX_TIMEOUT_TICKS) {
      return HAL_TIMEOUT; // Oops!
    }
  }
  oled -> TxFlag = 0;
  __HAL_UNLOCK(oled);
  return HAL_OK;
}
