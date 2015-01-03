

#ifndef _KEY_H
#define _KEY_H

void key_irq(void);
unsigned key_get_from_queue(void);
void key_add_to_queue(unsigned code);

#define KEY_NEXT 2
#define KEY_SELECT 1

#endif