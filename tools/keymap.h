#ifndef _KEYMAP_H_
#define _KEYMAP_H_
#include <stdint.h>


struct keymap
{
	uint16_t sc;
	uint16_t vk[3];
	uint32_t tag;
};

#define TAG_ISLOCK   
#define TAG_CTRL
#define TAG_ALT      
#define TAG_SHIFT         (0x00000001u)
#define TAG_CAP_LOCK      (0x00000002u)
#define TAG_NUM_LOCK
#define TAG_SCROLL_LOCK

struct keymap *keymap(struct keymap *map);
char keymap(struct input_event *pev);
#endif