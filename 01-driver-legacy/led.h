#ifndef LED_H__
#define LED_H__

#define GPIO_0_ADDR_BASE 0x44E07000
#define GPIO_0_ADDR_SIZE (0x44E07FFF - 0x44E07000)
#define GPIO_1_ADDR_BASE 0x4804C000
#define GPIO_1_ADDR_SIZE (0x4804CFFF - 0x4804C000)

#define GPIO_OE_OFFSET 0x134
#define GPIO_CLEARDATAOUT_OFFSET 0x190
#define GPIO_SETDATAOUT_OFFSET 0x194

#define LED_RED (1 << 31)
#define LED_GREEN (1 << 14)

#endif /* LED_H__ */