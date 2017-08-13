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
  uint8_t Flag;
  OLED_StateTypeDef State;
  HAL_LockTypeDef Lock;
} OLED_HandleTypeDef;

typedef enum
{
  OLED_STATE_RESET = 0x00U;
  OLED_STATE_READY = 0x01U;
  OLED_STATE_BUSY = 0x02U;
  OLED_STATE_BUSY_TX = 0x04U;
  OLED_STATE_BUSY_RX = 0x08U;
} OLED_StateTypeDef;

void OLED_Init(void);
void OLED_Position_Set(uint8_t posX, uint8_t posY);
void OLED_Fill(uint8_t fillData);
void OLED_Clear(void);
void OLED_Power(uint8_t powerState);
void OLED_String_Display(uint8_t posX, uint8_t posY, char * buf);
HAL_StatusTypeDef OLED_WriteCommand(OLED_HandleTypeDef * oled, uint8_t cmd);
HAL_StatusTypeDef OLED_WriteData(OLED_HandleTypeDef * oled, uint8_t data);

HAL_StatusTypeDef OLED_WaitOnFlagUntilTimeout(OLED_HandleTypeDef * oled, uint8_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t TickStart);

#endif

