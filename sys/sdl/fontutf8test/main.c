
#include <stdlib.h>
#include <stdio.h>

#include "u8g.h"
#include "fontutf8-data.h"

void u8g_chinese(u8g_t *pu8g) {
    char s1[] = _U8GT("黄沙百戰穿金甲，");
    char s2[] = _U8GT("不破樓蘭終不還。");
    char buf[20] = _U8GT("Chinese Glyph");
    sprintf (buf, "u32=%d,w=%d,s=%d",sizeof(uint32_t),sizeof(wchar_t),sizeof(size_t));
    //sprintf (buf, "i=%d,l=%d,u=%d",sizeof(int),sizeof(long),sizeof(unsigned));
    u8g_DrawUtf8Str (pu8g, 0, 11, buf);
    u8g_DrawUtf8Str (pu8g, 5, 30, s1);
    u8g_DrawUtf8Str (pu8g, 5, 48, s2);
}

int
main(void)
{
    u8g_t u8g;
    u8g_Init (&u8g, &u8g_dev_sdl_1bit);

    u8g_SetUtf8Fonts (g_fontinfo, NUM_ARRAY(g_fontinfo));

    u8g_FirstPage (&u8g);
    do {
        u8g_chinese(&u8g);
    } while( u8g_NextPage(&u8g) );

    while( u8g_sdl_get_key() < 0 ) ;
    return 0;
}
