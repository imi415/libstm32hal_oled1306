#ifndef __USER_12864_H
#define __USER_12864_H

#define OLED_MAX_TIMEOUT_TICKS 1000

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  I2C_HandleTypeDef * Instance;
  uint8_t Address;
  HAL_LockTypeDef Lock;
  uint8_t TxFlag;
} OLED_HandleTypeDef;

void OLED_Init(OLED_HandleTypeDef * oled, I2C_HandleTypeDef * hi2c, uint8_t addr);
void OLED_Position_Set(OLED_HandleTypeDef * oled, uint8_t posX, uint8_t posY);
void OLED_Fill(OLED_HandleTypeDef * oled, uint8_t fillData);
void OLED_Clear(OLED_HandleTypeDef * oled);
void OLED_Power(OLED_HandleTypeDef * oled, uint8_t powerState);
void OLED_String_Display(OLED_HandleTypeDef * oled, uint8_t posX, uint8_t posY, char * buf);
HAL_StatusTypeDef OLED_Write_Command(OLED_HandleTypeDef * oled, uint8_t cmd);
HAL_StatusTypeDef OLED_Write_Data(OLED_HandleTypeDef * oled, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif
