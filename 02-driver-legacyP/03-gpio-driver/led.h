#ifndef LED_H__
#define LED_H__

typedef unsigned int uint32_t;

/**
 * @brief GPIO Init structure definition
 */
typedef struct
{
    uint32_t Pin; /*!< Specifies the GPIO pins to be configured.
                       This parameter can be any value of @ref GPIO_pins_define */

    uint32_t Mode; /*!< Specifies the operating mode for the selected pins.
                        This parameter can be a value of @ref GPIO_mode_define */

    uint32_t Pull; /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                        This parameter can be a value of @ref GPIO_pull_define */

    uint32_t Speed; /*!< Specifies the speed for the selected pins.
                         This parameter can be a value of @ref GPIO_speed_define */
} GPIO_InitTypeDef;

/**
 * @brief GPIO Bank Init structure definition
 */
typedef struct
{
    GPIO_InitTypeDef GPIO_Num[32];
    uint32_t __iomem *base_addr;
} GPIOBank_TypeDef;

/**
 * @brief  GPIO Bit SET and Bit RESET enumeration
 */
typedef enum
{
    GPIO_PIN_RESET = 0u,
    GPIO_PIN_SET
} GPIO_PinState;

/* Exported constants --------------------------------------------------------*/
#define GPIO_BANK_0 0x0
#define GPIO_BANK_1 0x1
#define GPIO_BANK_2 0x2
#define GPIO_BANK_3 0x3

/**
 * @brief General Purpose I/O
 */
#define GPIO_ADDR_SIZE (0x44E07FFF - 0x44E07000)
#define GPIO_OE_OFFSET 0x134
#define GPIO_CLEARDATAOUT_OFFSET 0x190
#define GPIO_SETDATAOUT_OFFSET 0x194

/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
 * @{
 */

/** @defgroup GPIO_pins_define GPIO pins define
 * @{
 */
#define GPIO_PIN_0 ((uint32_t)0x00000001)  /* Pin 0 selected    */
#define GPIO_PIN_1 ((uint32_t)0x00000002)  /* Pin 1 selected    */
#define GPIO_PIN_2 ((uint32_t)0x00000004)  /* Pin 2 selected    */
#define GPIO_PIN_3 ((uint32_t)0x00000008)  /* Pin 3 selected    */
#define GPIO_PIN_4 ((uint32_t)0x00000010)  /* Pin 4 selected    */
#define GPIO_PIN_5 ((uint32_t)0x00000020)  /* Pin 5 selected    */
#define GPIO_PIN_6 ((uint32_t)0x00000040)  /* Pin 6 selected    */
#define GPIO_PIN_7 ((uint32_t)0x00000080)  /* Pin 7 selected    */
#define GPIO_PIN_8 ((uint32_t)0x00000100)  /* Pin 8 selected    */
#define GPIO_PIN_9 ((uint32_t)0x00000200)  /* Pin 9 selected    */
#define GPIO_PIN_10 ((uint32_t)0x00000400) /* Pin 10 selected   */
#define GPIO_PIN_11 ((uint32_t)0x00000800) /* Pin 11 selected   */
#define GPIO_PIN_12 ((uint32_t)0x00001000) /* Pin 12 selected   */
#define GPIO_PIN_13 ((uint32_t)0x00002000) /* Pin 13 selected   */
#define GPIO_PIN_14 ((uint32_t)0x00004000) /* Pin 14 selected   */
#define GPIO_PIN_15 ((uint32_t)0x00008000) /* Pin 15 selected   */
#define GPIO_PIN_16 ((uint32_t)0x00010000) /* Pin 16 selected   */
#define GPIO_PIN_17 ((uint32_t)0x00020000) /* Pin 17 selected   */
#define GPIO_PIN_18 ((uint32_t)0x00040000) /* Pin 18 selected   */
#define GPIO_PIN_19 ((uint32_t)0x00080000) /* Pin 19 selected   */
#define GPIO_PIN_20 ((uint32_t)0x00100000) /* Pin 20 selected   */
#define GPIO_PIN_21 ((uint32_t)0x00200000) /* Pin 21 selected   */
#define GPIO_PIN_22 ((uint32_t)0x00400000) /* Pin 22 selected   */
#define GPIO_PIN_23 ((uint32_t)0x00800000) /* Pin 23 selected   */
#define GPIO_PIN_24 ((uint32_t)0x01000000) /* Pin 24 selected   */
#define GPIO_PIN_25 ((uint32_t)0x02000000) /* Pin 25 selected   */
#define GPIO_PIN_26 ((uint32_t)0x04000000) /* Pin 26 selected   */
#define GPIO_PIN_27 ((uint32_t)0x08000000) /* Pin 27 selected   */
#define GPIO_PIN_28 ((uint32_t)0x10000000) /* Pin 28 selected   */
#define GPIO_PIN_29 ((uint32_t)0x20000000) /* Pin 29 selected   */
#define GPIO_PIN_30 ((uint32_t)0x40000000) /* Pin 30 selected   */
#define GPIO_PIN_31 ((uint32_t)0x80000000) /* Pin 31 selected   */
#define GPIO_PIN_All ((uint32_t)0xFFFFFFFF) /* All pins selected */

#define GPIO_PIN_MASK 0xFFFFFFFFu           /* PIN mask for assert test */

/** @defgroup GPIO_mode_define GPIO mode define
 * @brief GPIO Configuration Mode
 *        Elements values convention: 0xX0yz00YZ
 *           - X  : GPIO mode or EXTI Mode
 *           - y  : External IT or Event trigger detection
 *           - z  : IO configuration on External IT or Event
 *           - Y  : Output type (Push Pull or Open Drain)
 *           - Z  : IO Direction mode (Input, Output, Alternate or Analog)
 * @{
 */
#define GPIO_MODE_INPUT 0x00000000u     /*!< Input Floating Mode                   */
#define GPIO_MODE_OUTPUT_PP 0x00000001u /*!< Output Push Pull Mode                 */

/** @addtogroup Peripheral_memory_map
 * @{
 */
#define FLASH_BASE 0x08000000UL      /*!< FLASH base address in the alias region */
#define FLASH_BANK1_END 0x0801FFFFUL /*!< FLASH END address of bank1 */
#define SRAM_BASE 0x20000000UL       /*!< SRAM base address in the alias region */
#define L4_WKUP 0x44C00000UL         /*!< L4_WKUP */
#define L4_PER 0x48000000UL          /*!< L4 Peripheral  */

#define SRAM_BB_BASE 0x22000000UL   /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE 0x42000000UL /*!< Peripheral base address in the bit-band region */

/*!< Peripheral memory map */
#define GPIO0_BASE (L4_WKUP + 0x00207000UL)
#define GPIO1_BASE (L4_PER + 0x0004C000UL)
#define GPIO2_BASE (L4_PER + 0x001AC000UL)
#define GPIO3_BASE (L4_PER + 0x001AE000UL)

/**
 * @}
 */

/** @addtogroup Peripheral_declaration
 * @{
 */
#define GPIO0 ((GPIO_TypeDef *)GPIO0_BASE)
#define GPIO1 ((GPIO_TypeDef *)GPIO1_BASE)
#define GPIO2 ((GPIO_TypeDef *)GPIO2_BASE)
#define GPIO3 ((GPIO_TypeDef *)GPIO3_BASE)
/**
 * @}
 */

/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Macros GPIO Private Macros
 * @{
 */

/******************************* GPIO Instances *******************************/
#define IS_GPIO_ALL_INSTANCE(INSTANCE) (((INSTANCE) == GPIO0) || \
                                        ((INSTANCE) == GPIO1) || \
                                        ((INSTANCE) == GPIO2) || \
                                        ((INSTANCE) == GPIO3)
#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))
#define IS_GPIO_PIN(PIN) (((((uint32_t)(1 << PIN)) & GPIO_PIN_MASK) != 0x00u) && ((((uint32_t)(1 << PIN)) & ~GPIO_PIN_MASK) == 0x00u))
#define IS_GPIO_MODE(MODE)              (((MODE) == GPIO_MODE_INPUT)              ||\
                                        ((MODE) == GPIO_MODE_OUTPUT_PP)
/**
 * @}
 */

/* Exported macro ------------------------------------------------------------*/
// #define USE_FULL_ASSERT    1U

#ifdef USE_FULL_ASSERT
/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr If expr is false, it calls assert_failed function
 *         which reports the name of the source file and the source
 *         line number of the call that failed.
 *         If expr is true, it returns no value.
 * @retval None
 */
#define assert_param(expr) ((expr) ? (void)0U : assert_failed())
/* Exported functions ------------------------------------------------------- */
int assert_failed()
{
    printk(KERN_ERR "Unvalid parameter input: %s %d", __func__, __LINE__);
    return -1;
}
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#endif /* LED_H__ */