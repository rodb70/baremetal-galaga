/*
 * hardware.h
 *
 */

#ifndef GBA_HARDWARE_H_
#define GBA_HARDWARE_H_

#define MODE_3 3
#define BG2_EN (1<<10)

// DMA Stuff
typedef struct {
    const volatile void *src;
    volatile void *dst;
    volatile unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define REG_DISPCNT *(unsigned short*)0x4000000

#define VIDEOBUFFERADDRESS (unsigned short *)0x6000000
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

#define BUTTONS *(volatile unsigned int *)0x4000130

static inline void hardware_video_init( void )
{
    REG_DISPCNT = MODE_3 | BG2_EN;
}

#endif /* GBA_HARDWARE_H_ */
