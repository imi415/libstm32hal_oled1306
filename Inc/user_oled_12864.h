#ifndef __USER_12864_H
#define __USER_12864_H

#define OLED_SLAVE_ADDR 0x78
#define OLED_I2C_INTERFACE hi2c1

#define OLED_MAX_TIMEOUT_TICKS 1000

#define OLED_FLAG_TRANSMIT_COMPLETE 0x01
#define OLED_FLAG_RECEIVE_COMPLETE 0x02

#define __OLED_GET_FLAG(oled, flag) (oled -> Flag & flag)

typedef struct
{
  I2C_InitTypeDef * Interface;
  uint8_t SlaveAddress;
  uint32_t MaxTimeoutTicks;
} OLED_InitTypeDef;

typedef struct
{
  OLED_InitTypeDef Init;
  uint8_t Brightness;

  OLED_Status_TypeDef State;
  uint8_t Flag;
  HAL_LockTypeDef Lock;
}

typedef enum
{
  OLED_STATE_TRANSMIT_COMPLETE;
  OLED_STATE_RECEIVE_COMPLETE;
  OLED_STATE_READY = 0U;
  OLED_STATE_BUSY;
} OLED_StatusTypeDef;

void OLED_Init(void);
void OLED_Position_Set(uint8_t posX, uint8_t posY);
void OLED_Fill(uint8_t fillData);
void OLED_Clear(void);
void OLED_Power(uint8_t powerState);
void OLED_String_Display(uint8_t posX, uint8_t posY, char * buf);
void OLED_Write_Command(uint8_t cmd);
void OLED_Write_Data(uint8_t data);

#endif

