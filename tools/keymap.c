#include "keymap.h"
#include <linux/input.h>

extern struct keymap defmap[128];
static struct keymap *psg_map = defmap;



struct keymap  *keymap(struct keymap *map)
{
	struct keymap	*poldmap = psg_map, *ptoldmap;
	struct keymap	*ptmap;
	
	ptmap    = psg_map  = map;
	ptoldmap = poldmap;
	for (int i = 0; i < 128; i++) {
		ptmap->tag = poldmap->tag;
		ptmap++;
		poldmap++;
	}

	return poldmap;
}

char keymap(struct input_event *pev)
{	
	char vk = 0;

	if (pev->code >= 128) {
		return 0;
	}
	else {
		return (psg_map + pev->code )->vk[0];
	}
}