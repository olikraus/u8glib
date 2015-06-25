/**
 * @file    fontutf8u8g.cpp
 * @brief   font api for u8g lib
 * @author  Yunhui Fu (yhfudev@gmail.com)
 * @version 1.0
 * @date    2015-02-19
 * @copyright GPL/BSD
 */

#include <string.h>
#include "u8g.h"

#if defined(ARDUINO)
// there's overflow of the wchar_t due to the 2-byte size in Arduino
// sizeof(wchar_t)=2; sizeof(size_t)=2; sizeof(uint32_t)=4;
// sizeof(int)=2; sizeof(long)=4; sizeof(unsigned)=2;
#define wchar_t uint32_t
#else
// x86_64
// sizeof(wchar_t)=4; sizeof(size_t)=8; sizeof(uint32_t)=4;
// sizeof(int)=4; sizeof(long)=8; sizeof(unsigned)=4;
#endif

#define FALSE 0
#define TRUE  1

#if DEBUG
#define assert(a) if (!(a)) {printf("Assert: " # a); exit(1);}
#define TRACE(fmt, ...) fprintf (stdout, "[%s()] " fmt " {ln:%d, fn:" __FILE__ "}\n", __func__, ##__VA_ARGS__, __LINE__)
#else
#define assert(a)
#define TRACE(...)
#endif

wchar_t
get_val_utf82uni (uint8_t *pstart)
{
    size_t cntleft;
    wchar_t retval = 0;

    if (0 == (0x80 & *pstart)) {
        return *pstart;
    }

    if (((*pstart & 0xE0) ^ 0xC0) == 0) {
        cntleft = 1;
        retval = *pstart & ~0xE0;
    } else if (((*pstart & 0xF0) ^ 0xE0) == 0) {
        cntleft = 2;
        retval = *pstart & ~0xF0;
    } else if (((*pstart & 0xF8) ^ 0xF0) == 0) {
        cntleft = 3;
        retval = *pstart & ~0xF8;
    } else if (((*pstart & 0xFC) ^ 0xF8) == 0) {
        cntleft = 4;
        retval = *pstart & ~0xFC;
    } else if (((*pstart & 0xFE) ^ 0xFC) == 0) {
        cntleft = 5;
        retval = *pstart & ~0xFE;
    } else {
        /* encoding error */
        cntleft = 0;
        retval = 0;
    }
    pstart ++;
    for (; cntleft > 0; cntleft --) {
        retval <<= 6;
        retval |= *pstart & 0x3F;
        pstart ++;
    }
    return retval;
}

/**
 * @brief 转换 UTF-8 编码的一个字符为本地的 Unicode 字符(wchar_t)
 *
 * @param pstart : 存储 UTF-8 字符的指针
 * @param pval : 需要返回的 Unicode 字符存放地址指针
 *
 * @return 成功返回下个 UTF-8 字符的位置
 *
 * 转换 UTF-8 编码的一个字符为本地的 Unicode 字符(wchar_t)
 */
uint8_t *
get_utf8_value (uint8_t *pstart, wchar_t *pval)
{
    uint32_t val = 0;
    uint8_t *p = pstart;
    /*size_t maxlen = strlen (pstart);*/

    assert (NULL != pstart);

    if (0 == (0x80 & *p)) {
        val = (size_t)*p;
        p ++;
    } else if (0xC0 == (0xE0 & *p)) {
        val = *p & 0x1F;
        val <<= 6;
        p ++;
        val |= (*p & 0x3F);
        p ++;
        assert ((wchar_t)val == get_val_utf82uni (pstart));
    } else if (0xE0 == (0xF0 & *p)) {
        val = *p & 0x0F;
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        p ++;
        assert ((wchar_t)val == get_val_utf82uni (pstart));
    } else if (0xF0 == (0xF8 & *p)) {
        val = *p & 0x07;
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        p ++;
        assert ((wchar_t)val == get_val_utf82uni (pstart));
    } else if (0xF8 == (0xFC & *p)) {
        val = *p & 0x03;
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        p ++;
        assert ((wchar_t)val == get_val_utf82uni (pstart));
    } else if (0xFC == (0xFE & *p)) {
        val = *p & 0x01;
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        val <<= 6; p ++;
        val |= (*p & 0x3F);
        p ++;
        assert ((wchar_t)val == get_val_utf82uni (pstart));
    } else if (0x80 == (0xC0 & *p)) {
        /* error? */
        for (; 0x80 == (0xC0 & *p); p ++);
    } else {
        /* error */
        for (; ((0xFE & *p) > 0xFC); p ++);
    }
    /*if (val == 0) {
        p = NULL;*/
/*
    } else if (pstart + maxlen < p) {
        p = pstart;
        if (pval) *pval = 0;
    }
*/

    if (pval) *pval = val;

    return p;
}

/* return v1 - v2 */
static int
fontinfo_compare (u8g_fontinfo_t * v1, u8g_fontinfo_t * v2)
{
    assert (NULL != v1);
    assert (NULL != v2);
    if (v1->page < v2->page) {
        return -1;
    } else if (v1->page > v2->page) {
        return 1;
    }
    if (v1->end < v2->begin) {
        return -1;
    } else if (v1->begin > v2->end) {
        return 1;
    }
    return 0;
}

#if USE_RBTREE_LINUX
struct rb_root g_fontinfo_root = RB_ROOT;
#else
RB_HEAD(_u8g_fontinfo_entries_t, _u8g_fontinfo_t) g_fontinfo_root = RB_INITIALIZER(&g_fontinfo_root);
RB_PROTOTYPE(_u8g_fontinfo_entries_t, _u8g_fontinfo_t, node, fontinfo_compare);
RB_GENERATE(_u8g_fontinfo_entries_t, _u8g_fontinfo_t, node, fontinfo_compare);
#endif

char flag_fontinfo_inited = 0;

static int
fontinfo_insert (void * root_arg, u8g_fontinfo_t *data)
{
#if USE_RBTREE_LINUX
    struct rb_root *root = (struct rb_root *) root_arg;
    struct rb_node **new1 = &(root->rb_node), *parent = NULL;
    // Figure out where to put new node
    while (*new1) {
        u8g_fontinfo_t *this1 = container_of(*new1, u8g_fontinfo_t, node);

        int result = fontinfo_compare (data, this1);

        parent = *new1;
        if (result < 0) {
            new1 = &((*new1)->rb_left);
        } else if (result > 0) {
            new1 = &((*new1)->rb_right);
        } else {
            return FALSE;
        }
    }

    // Add new node and rebalance tree.
    rb_link_node(&data->node, parent, new1);
    rb_insert_color(&data->node, root);

#else
    RB_INSERT(_u8g_fontinfo_entries_t, (struct _u8g_fontinfo_entries_t *) root_arg, data);
#endif

    return TRUE;
}

int
fontinfo_init (u8g_fontinfo_t * fntinfo, int number)
{
    int i;

#if USE_RBTREE_LINUX
    struct rb_root *root = &g_fontinfo_root;
#else
    void * root = &g_fontinfo_root;
#endif

    for (i = 0; i < number; i ++) {
        fontinfo_insert ((void *)root, &fntinfo[i]);
    }
    flag_fontinfo_inited = 1;

    return 0;
}

/**
 * @brief check if font is loaded
 */
char
fontinfo_isinited(void)
{
    return flag_fontinfo_inited;
}

const u8g_fntpgm_uint8_t *
fontinfo_find (wchar_t val)
{
    u8g_fontinfo_t *data = NULL;
    // calculate the page
    u8g_fontinfo_t vcmp = {val / 128, val % 128 + 128, val % 128 + 128, 0, 0};

#if USE_RBTREE_LINUX
    struct rb_root *root = &g_fontinfo_root;
    struct rb_node *node = root->rb_node;
#else
    struct _u8g_fontinfo_entries_t * root = &g_fontinfo_root;
#endif

    if (flag_fontinfo_inited == 0) {
        return NULL;
    }
    if (val < 128) {
        return DEFAULT_FONT; //u8g_font_gdr25;
    }

#if USE_RBTREE_LINUX
    while (node) {
        int result;
        data = container_of(node, u8g_fontinfo_t, node);

        result = fontinfo_compare (&vcmp, data);

        if (result < 0) {
            node = node->rb_left;
        } else if (result > 0) {
            node = node->rb_right;
        } else {
            return data->fntdata;
        }
    }
#else
    data = RB_FIND (_u8g_fontinfo_entries_t, root, &vcmp);
    if (NULL != data) {
        return data->fntdata;
    }
    // dump values:
    // RB_FOREACH(data, _u8g_fontinfo_entries_t, root) printf("%d\n", data->fntdata);
#endif
    return NULL;
}

/**
 * @brief draw a UTF-8 string
 */
void
u8g_DrawUtf8Str (u8g_t *pu8g, unsigned int x, unsigned int y, const char *utf8_msg)
{
    int len;
    uint8_t *pend = NULL;
    uint8_t *p;
    wchar_t val;
    uint8_t buf[2] = {0, 0};
    u8g_fntpgm_uint8_t * fntpqm = NULL;

    if (! fontinfo_isinited()) {
        u8g_DrawStr (pu8g, x, y, "Err: utf8 font not initialized.");
        return;
    }
    //u8g_DrawStr(pu8g, x, y, utf8_msg);
    len = strlen(utf8_msg);
    pend = (uint8_t *)utf8_msg + len;
    for (p = (uint8_t *)utf8_msg; p < pend; ) {
        val = 0;
        p = get_utf8_value(p, &val);
        if (NULL == p) {
            TRACE("No more char, break ...");
            break;
        }
        TRACE("got char=%d", (int)val);
        buf[0] = (uint8_t)(val & 0x7F);
        fntpqm = (u8g_fntpgm_uint8_t *)fontinfo_find (val);
        if (NULL == fntpqm) {
            //continue;
            buf[0] = '?';
            fntpqm = (u8g_fntpgm_uint8_t *)DEFAULT_FONT;
            TRACE("Unknown char, use default font");
        }
        if (DEFAULT_FONT != fntpqm) {
            buf[0] |= 0x80; // use upper page to avoid 0x00 error in C. you may want to generate the font data
        }
        TRACE("set font: %p; (default=%p)", fntpqm, DEFAULT_FONT);
        u8g_SetFont (pu8g, fntpqm);

        u8g_DrawStr(pu8g, x, y, (char *) buf);
        x += u8g_GetStrWidth(pu8g, (char *)buf);
        TRACE("next pos= %d", x);
    }
}
