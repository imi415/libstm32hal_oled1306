MODULE_DIR=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

C_SOURCES += $(MODULE_DIR)/Src/user_oled_12864.c

C_INCLUDES += -I$(MODULE_DIR)/Inc
