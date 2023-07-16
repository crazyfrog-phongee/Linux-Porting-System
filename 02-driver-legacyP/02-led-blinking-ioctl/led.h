#ifndef LED_H__
#define LED_H__

#define GPIO_0_ADDR_BASE 0x44E07000
#define GPIO_0_ADDR_SIZE (0x44E07FFF - 0x44E07000)
#define GPIO_1_ADDR_BASE 0x4804C000
#define GPIO_1_ADDR_SIZE (0x4804CFFF - 0x4804C000)

#define GPIO_OE_OFFSET 0x134
#define GPIO_CLEARDATAOUT_OFFSET 0x190
#define GPIO_SETDATAOUT_OFFSET 0x194

#define LED_RED 31
#define LED_GREEN 14

#define MAGIC_NUM   100
#define SET_ON_LED _IOW(MAGIC_NUM, '1', int *)
#define SET_OFF_LED _IOW(MAGIC_NUM, '0', int *)
#define SET_MODE_LED _IOW(MAGIC_NUM, '2', led_config_t *)

typedef struct led_config led_config_t;

#endif /* LED_H__ */