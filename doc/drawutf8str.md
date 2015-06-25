DrawUtf8Font
============

Show UTF-8 human readable strings from source code to your tiny LCD via u8glib

The original u8g support partially for displaying multi-language by re-coding the char values due to large size of font data and limited memory/flash of embedded systems.
It's very inconviniant to update the firmware if there's (menu) message changed by recoding all these added message chars.
What if we get all these steps done with the human readable messages in source code and processed by automatical tools while keep the compiled firmware as small as previous releases?
This function will release the programmer from the bad experiences.

Basically, this tool will scan the source code of the firmware which using u8g lib, pick up the message strings tagged with "_U8GT()",
and then genrate all of font data structures and save it in .h files for u8g.

The firmware developer now can use UTF-8 plain text in their language source code and regenerate the langauge files once they change the message strings tagged with "_U8GT()" before compiling the souce code.
They should use the function u8g_DrawUtf8Str() or U8GLIB::drawUtf8Str() to display the strings.


Installation and usages
-----------------------

include the generated data file(see steps following) in your source code:
    #include "fontutf8-data.h"


init the font data in setup() function
u8g_SetUtf8Fonts (g_fontinfo, NUM_ARRAY(g_fontinfo));


declare all of the string in macro _U8GT(), for example:

     char s[] = _U8GT("黄沙百戰穿金甲，不破樓蘭終不還。");
    // and draw the string:
    u8g_DrawUtf8Str (&u8g, 3, 30, s);


Prepare BDF font files, you may download a font from WQY, for example: http://wenq.org/daily/wqy-bitmapfont-bdf-gb18030-nightly_build.tar.gz

    tar -xvf wqy-bitmapfont-bdf-gb18030-nightly_build.tar.gz
    cp wqy-bitmapfont-gb18030/wenquanyi_12pt.bdf tools/

change the font file name in the bash script tools/genpages.sh

    FN_FONT=${DN_EXEC}/wenquanyi_12pt.bdf

generate the font file fontutf8-data.h

    cd src
    ../tools/font/genpages/genpages.sh

