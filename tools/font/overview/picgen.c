/*

  X11 pcf fonts
    die üblichen, dann: 
    cursor, micro, cu12 (enthält auch pictogramme!!! liegt derzeit im ~/tmp ordner)  prüfen mit gbdfed
  
  cu12
    Name: ClearlyU Unicode Bitmap Fonts
    source: http://sofia.nmsu.edu/~mleisher/Software/cu/
    license: BSD License

  didactic gothic
  -a eingeschaltet

  dg14_10
  dg17_11
  dg21_14
  dg24_17
  dg28_20
  dg37_25
  dg43_30
  dg49_35
  dg57_40
  
  free univers
  -a eingeschaltet (ist auch besser, wenn es abgeschaltet ist, sind die ergebnisse schlechter.)
  
  fub16_11
  fub20_14
  fub23_17
  fub27_20
  fub34_25
  fub40_30
  fub49_35
  fub58_42
  
  fur15_11
  fur19_14
  fur23_17
  fur28_20
  fur34_25
  fur40_30
  fur48_35
  fur58_42
  
  old standard
  -a eingeschaltet
  TODO: mit ausgeschaltetem -a probieren
  
  osb25_18
  osb28_21
  osb34_26
  osb38_29
  osb48_35
  osb55_41              <-- geht das überhaupt wegen der glyph größe?
  
  osr26_18
  osr29_21
  osr36_26
  osr41_29
  osr49_35
  osr57_41              <-- geht das überhaupt wegen der glyph größe?
  
  Gentium
  -a ausgeschaltet !!! (dann viel besser)
  
  gbr15_9
  gbr17_10
  gbr18_11
  gbr19_12
  gbr23_14
  gbr27_17
  gbr32_20
  gbr40_25
  gbr48_30
  gbr56_35
  
  gbb18_11
  gbb19_12
  gbb23_14
  gbb27_17
  gbb32_20
  gbb40_25
  gbb48_30
  gbb55_35
  
  Linux schriften nochmal mit ausgeschaltetem -a probieren
  --> nützt nichts
  
*/




#include "u8g.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef ANALYSE

extern unsigned char font10x20[];
extern unsigned char u8g_font_dg40[];
extern unsigned char u8g_font_unicons36[];
extern unsigned char u8g_font_unicons31[];
extern unsigned char u8g_font_unicons24[];
extern unsigned char u8g_font_judson_r22[];
extern unsigned char u8g_font_judson_r34[];
extern unsigned char u8g_font_judson_r44[];

extern unsigned char u8g_font_dg10[];
extern unsigned char u8g_font_dg11[];
extern unsigned char u8g_font_dg12[];
extern unsigned char u8g_font_dg13[];
extern unsigned char u8g_font_dg14[];
extern unsigned char u8g_font_dg15[];
extern unsigned char u8g_font_dg16[];
extern unsigned char u8g_font_dg17[];
extern unsigned char u8g_font_dg18[];
extern unsigned char u8g_font_dg19[];

extern unsigned char u8g_font_dg20[];
extern unsigned char u8g_font_dg21[];
extern unsigned char u8g_font_dg22[];
extern unsigned char u8g_font_dg23[];
extern unsigned char u8g_font_dg24[];
extern unsigned char u8g_font_dg25[];
extern unsigned char u8g_font_dg26[];
extern unsigned char u8g_font_dg27[];
extern unsigned char u8g_font_dg28[];
extern unsigned char u8g_font_dg29[];

extern unsigned char u8g_font_dg30[];
extern unsigned char u8g_font_dg31[];
extern unsigned char u8g_font_dg32[];
extern unsigned char u8g_font_dg33[];
extern unsigned char u8g_font_dg34[];
extern unsigned char u8g_font_dg35[];
extern unsigned char u8g_font_dg36[];
extern unsigned char u8g_font_dg37[];
extern unsigned char u8g_font_dg38[];
extern unsigned char u8g_font_dg39[];

extern unsigned char u8g_font_dg40[];
extern unsigned char u8g_font_dg41[];
extern unsigned char u8g_font_dg42[];
extern unsigned char u8g_font_dg43[];
extern unsigned char u8g_font_dg44[];
extern unsigned char u8g_font_dg45[];
extern unsigned char u8g_font_dg46[];
extern unsigned char u8g_font_dg47[];
extern unsigned char u8g_font_dg48[];
extern unsigned char u8g_font_dg49[];

extern unsigned char u8g_font_dg50[];
extern unsigned char u8g_font_dg51[];
extern unsigned char u8g_font_dg52[];
extern unsigned char u8g_font_dg53[];
extern unsigned char u8g_font_dg54[];
extern unsigned char u8g_font_dg55[];
extern unsigned char u8g_font_dg56[];
extern unsigned char u8g_font_dg57[];
extern unsigned char u8g_font_dg58[];
extern unsigned char u8g_font_dg59[];

extern unsigned char u8g_font_llr10[];
extern unsigned char u8g_font_llr11[];
extern unsigned char u8g_font_llr12[];
extern unsigned char u8g_font_llr13[];
extern unsigned char u8g_font_llr14[];
extern unsigned char u8g_font_llr15[];
extern unsigned char u8g_font_llr16[];
extern unsigned char u8g_font_llr17[];
extern unsigned char u8g_font_llr18[];
extern unsigned char u8g_font_llr19[];

extern unsigned char u8g_font_llr20[];
extern unsigned char u8g_font_llr21[];
extern unsigned char u8g_font_llr22[];
extern unsigned char u8g_font_llr23[];
extern unsigned char u8g_font_llr24[];
extern unsigned char u8g_font_llr25[];
extern unsigned char u8g_font_llr26[];
extern unsigned char u8g_font_llr27[];
extern unsigned char u8g_font_llr28[];
extern unsigned char u8g_font_llr29[];

extern unsigned char u8g_font_llr30[];
extern unsigned char u8g_font_llr31[];
extern unsigned char u8g_font_llr32[];
extern unsigned char u8g_font_llr33[];
extern unsigned char u8g_font_llr34[];
extern unsigned char u8g_font_llr35[];
extern unsigned char u8g_font_llr36[];
extern unsigned char u8g_font_llr37[];
extern unsigned char u8g_font_llr38[];
extern unsigned char u8g_font_llr39[];

extern unsigned char u8g_font_llr40[];
extern unsigned char u8g_font_llr41[];
extern unsigned char u8g_font_llr42[];
extern unsigned char u8g_font_llr43[];
extern unsigned char u8g_font_llr44[];
extern unsigned char u8g_font_llr45[];
extern unsigned char u8g_font_llr46[];
extern unsigned char u8g_font_llr47[];
extern unsigned char u8g_font_llr48[];
extern unsigned char u8g_font_llr49[];

extern unsigned char u8g_font_llr50[];
extern unsigned char u8g_font_llr51[];
extern unsigned char u8g_font_llr52[];
extern unsigned char u8g_font_llr53[];
extern unsigned char u8g_font_llr54[];
extern unsigned char u8g_font_llr55[];
extern unsigned char u8g_font_llr56[];
extern unsigned char u8g_font_llr57[];
extern unsigned char u8g_font_llr58[];
extern unsigned char u8g_font_llr59[];

extern unsigned char u8g_font_llb10[];
extern unsigned char u8g_font_llb11[];
extern unsigned char u8g_font_llb12[];
extern unsigned char u8g_font_llb13[];
extern unsigned char u8g_font_llb14[];
extern unsigned char u8g_font_llb15[];
extern unsigned char u8g_font_llb16[];
extern unsigned char u8g_font_llb17[];
extern unsigned char u8g_font_llb18[];
extern unsigned char u8g_font_llb19[];

extern unsigned char u8g_font_llb20[];
extern unsigned char u8g_font_llb21[];
extern unsigned char u8g_font_llb22[];
extern unsigned char u8g_font_llb23[];
extern unsigned char u8g_font_llb24[];
extern unsigned char u8g_font_llb25[];
extern unsigned char u8g_font_llb26[];
extern unsigned char u8g_font_llb27[];
extern unsigned char u8g_font_llb28[];
extern unsigned char u8g_font_llb29[];

extern unsigned char u8g_font_llb30[];
extern unsigned char u8g_font_llb31[];
extern unsigned char u8g_font_llb32[];
extern unsigned char u8g_font_llb33[];
extern unsigned char u8g_font_llb34[];
extern unsigned char u8g_font_llb35[];
extern unsigned char u8g_font_llb36[];
extern unsigned char u8g_font_llb37[];
extern unsigned char u8g_font_llb38[];
extern unsigned char u8g_font_llb39[];

extern unsigned char u8g_font_llb40[];
extern unsigned char u8g_font_llb41[];
extern unsigned char u8g_font_llb42[];
extern unsigned char u8g_font_llb43[];
extern unsigned char u8g_font_llb44[];
extern unsigned char u8g_font_llb45[];
extern unsigned char u8g_font_llb46[];
extern unsigned char u8g_font_llb47[];
extern unsigned char u8g_font_llb48[];
extern unsigned char u8g_font_llb49[];

extern unsigned char u8g_font_llb50[];
extern unsigned char u8g_font_llb51[];
extern unsigned char u8g_font_llb52[];
extern unsigned char u8g_font_llb53[];
extern unsigned char u8g_font_llb54[];
extern unsigned char u8g_font_llb55[];
extern unsigned char u8g_font_llb56[];
extern unsigned char u8g_font_llb57[];
extern unsigned char u8g_font_llb58[];
extern unsigned char u8g_font_llb59[];

extern unsigned char u8g_font_fur10[];
extern unsigned char u8g_font_fur11[];
extern unsigned char u8g_font_fur12[];
extern unsigned char u8g_font_fur13[];
extern unsigned char u8g_font_fur14[];
extern unsigned char u8g_font_fur15[];
extern unsigned char u8g_font_fur16[];
extern unsigned char u8g_font_fur17[];
extern unsigned char u8g_font_fur18[];
extern unsigned char u8g_font_fur19[];

extern unsigned char u8g_font_fur20[];
extern unsigned char u8g_font_fur21[];
extern unsigned char u8g_font_fur22[];
extern unsigned char u8g_font_fur23[];
extern unsigned char u8g_font_fur24[];
extern unsigned char u8g_font_fur25[];
extern unsigned char u8g_font_fur26[];
extern unsigned char u8g_font_fur27[];
extern unsigned char u8g_font_fur28[];
extern unsigned char u8g_font_fur29[];

extern unsigned char u8g_font_fur30[];
extern unsigned char u8g_font_fur31[];
extern unsigned char u8g_font_fur32[];
extern unsigned char u8g_font_fur33[];
extern unsigned char u8g_font_fur34[];
extern unsigned char u8g_font_fur35[];
extern unsigned char u8g_font_fur36[];
extern unsigned char u8g_font_fur37[];
extern unsigned char u8g_font_fur38[];
extern unsigned char u8g_font_fur39[];

extern unsigned char u8g_font_fur40[];
extern unsigned char u8g_font_fur41[];
extern unsigned char u8g_font_fur42[];
extern unsigned char u8g_font_fur43[];
extern unsigned char u8g_font_fur44[];
extern unsigned char u8g_font_fur45[];
extern unsigned char u8g_font_fur46[];
extern unsigned char u8g_font_fur47[];
extern unsigned char u8g_font_fur48[];
extern unsigned char u8g_font_fur49[];

extern unsigned char u8g_font_fur50[];
extern unsigned char u8g_font_fur51[];
extern unsigned char u8g_font_fur52[];
extern unsigned char u8g_font_fur53[];
extern unsigned char u8g_font_fur54[];
extern unsigned char u8g_font_fur55[];
extern unsigned char u8g_font_fur56[];
extern unsigned char u8g_font_fur57[];
extern unsigned char u8g_font_fur58[];
extern unsigned char u8g_font_fur59[];


extern unsigned char u8g_font_fub10[];
extern unsigned char u8g_font_fub11[];
extern unsigned char u8g_font_fub12[];
extern unsigned char u8g_font_fub13[];
extern unsigned char u8g_font_fub14[];
extern unsigned char u8g_font_fub15[];
extern unsigned char u8g_font_fub16[];
extern unsigned char u8g_font_fub17[];
extern unsigned char u8g_font_fub18[];
extern unsigned char u8g_font_fub19[];

extern unsigned char u8g_font_fub20[];
extern unsigned char u8g_font_fub21[];
extern unsigned char u8g_font_fub22[];
extern unsigned char u8g_font_fub23[];
extern unsigned char u8g_font_fub24[];
extern unsigned char u8g_font_fub25[];
extern unsigned char u8g_font_fub26[];
extern unsigned char u8g_font_fub27[];
extern unsigned char u8g_font_fub28[];
extern unsigned char u8g_font_fub29[];

extern unsigned char u8g_font_fub30[];
extern unsigned char u8g_font_fub31[];
extern unsigned char u8g_font_fub32[];
extern unsigned char u8g_font_fub33[];
extern unsigned char u8g_font_fub34[];
extern unsigned char u8g_font_fub35[];
extern unsigned char u8g_font_fub36[];
extern unsigned char u8g_font_fub37[];
extern unsigned char u8g_font_fub38[];
extern unsigned char u8g_font_fub39[];

extern unsigned char u8g_font_fub40[];
extern unsigned char u8g_font_fub41[];
extern unsigned char u8g_font_fub42[];
extern unsigned char u8g_font_fub43[];
extern unsigned char u8g_font_fub44[];
extern unsigned char u8g_font_fub45[];
extern unsigned char u8g_font_fub46[];
extern unsigned char u8g_font_fub47[];
extern unsigned char u8g_font_fub48[];
extern unsigned char u8g_font_fub49[];

extern unsigned char u8g_font_fub50[];
extern unsigned char u8g_font_fub51[];
extern unsigned char u8g_font_fub52[];
extern unsigned char u8g_font_fub53[];
extern unsigned char u8g_font_fub54[];
extern unsigned char u8g_font_fub55[];
extern unsigned char u8g_font_fub56[];
extern unsigned char u8g_font_fub57[];
extern unsigned char u8g_font_fub58[];
extern unsigned char u8g_font_fub59[];



extern unsigned char u8g_font_osr10[];
extern unsigned char u8g_font_osr11[];
extern unsigned char u8g_font_osr12[];
extern unsigned char u8g_font_osr13[];
extern unsigned char u8g_font_osr14[];
extern unsigned char u8g_font_osr15[];
extern unsigned char u8g_font_osr16[];
extern unsigned char u8g_font_osr17[];
extern unsigned char u8g_font_osr18[];
extern unsigned char u8g_font_osr19[];

extern unsigned char u8g_font_osr20[];
extern unsigned char u8g_font_osr21[];
extern unsigned char u8g_font_osr22[];
extern unsigned char u8g_font_osr23[];
extern unsigned char u8g_font_osr24[];
extern unsigned char u8g_font_osr25[];
extern unsigned char u8g_font_osr26[];
extern unsigned char u8g_font_osr27[];
extern unsigned char u8g_font_osr28[];
extern unsigned char u8g_font_osr29[];

extern unsigned char u8g_font_osr30[];
extern unsigned char u8g_font_osr31[];
extern unsigned char u8g_font_osr32[];
extern unsigned char u8g_font_osr33[];
extern unsigned char u8g_font_osr34[];
extern unsigned char u8g_font_osr35[];
extern unsigned char u8g_font_osr36[];
extern unsigned char u8g_font_osr37[];
extern unsigned char u8g_font_osr38[];
extern unsigned char u8g_font_osr39[];

extern unsigned char u8g_font_osr40[];
extern unsigned char u8g_font_osr41[];
extern unsigned char u8g_font_osr42[];
extern unsigned char u8g_font_osr43[];
extern unsigned char u8g_font_osr44[];
extern unsigned char u8g_font_osr45[];
extern unsigned char u8g_font_osr46[];
extern unsigned char u8g_font_osr47[];
extern unsigned char u8g_font_osr48[];
extern unsigned char u8g_font_osr49[];

extern unsigned char u8g_font_osr50[];
extern unsigned char u8g_font_osr51[];
extern unsigned char u8g_font_osr52[];
extern unsigned char u8g_font_osr53[];
extern unsigned char u8g_font_osr54[];
extern unsigned char u8g_font_osr55[];
extern unsigned char u8g_font_osr56[];
extern unsigned char u8g_font_osr57[];
extern unsigned char u8g_font_osr58[];
extern unsigned char u8g_font_osr59[];

extern unsigned char u8g_font_osb10[];
extern unsigned char u8g_font_osb11[];
extern unsigned char u8g_font_osb12[];
extern unsigned char u8g_font_osb13[];
extern unsigned char u8g_font_osb14[];
extern unsigned char u8g_font_osb15[];
extern unsigned char u8g_font_osb16[];
extern unsigned char u8g_font_osb17[];
extern unsigned char u8g_font_osb18[];
extern unsigned char u8g_font_osb19[];

extern unsigned char u8g_font_osb20[];
extern unsigned char u8g_font_osb21[];
extern unsigned char u8g_font_osb22[];
extern unsigned char u8g_font_osb23[];
extern unsigned char u8g_font_osb24[];
extern unsigned char u8g_font_osb25[];
extern unsigned char u8g_font_osb26[];
extern unsigned char u8g_font_osb27[];
extern unsigned char u8g_font_osb28[];
extern unsigned char u8g_font_osb29[];

extern unsigned char u8g_font_osb30[];
extern unsigned char u8g_font_osb31[];
extern unsigned char u8g_font_osb32[];
extern unsigned char u8g_font_osb33[];
extern unsigned char u8g_font_osb34[];
extern unsigned char u8g_font_osb35[];
extern unsigned char u8g_font_osb36[];
extern unsigned char u8g_font_osb37[];
extern unsigned char u8g_font_osb38[];
extern unsigned char u8g_font_osb39[];

extern unsigned char u8g_font_osb40[];
extern unsigned char u8g_font_osb41[];
extern unsigned char u8g_font_osb42[];
extern unsigned char u8g_font_osb43[];
extern unsigned char u8g_font_osb44[];
extern unsigned char u8g_font_osb45[];
extern unsigned char u8g_font_osb46[];
extern unsigned char u8g_font_osb47[];
extern unsigned char u8g_font_osb48[];
extern unsigned char u8g_font_osb49[];

extern unsigned char u8g_font_osb50[];
extern unsigned char u8g_font_osb51[];
extern unsigned char u8g_font_osb52[];
extern unsigned char u8g_font_osb53[];
extern unsigned char u8g_font_osb54[];
extern unsigned char u8g_font_osb55[];
extern unsigned char u8g_font_osb56[];
extern unsigned char u8g_font_osb57[];
extern unsigned char u8g_font_osb58[];
extern unsigned char u8g_font_osb59[];



extern unsigned char u8g_font_hab10[];
extern unsigned char u8g_font_hab11[];
extern unsigned char u8g_font_hab12[];
extern unsigned char u8g_font_hab13[];
extern unsigned char u8g_font_hab14[];
extern unsigned char u8g_font_hab15[];
extern unsigned char u8g_font_hab16[];
extern unsigned char u8g_font_hab17[];
extern unsigned char u8g_font_hab18[];
extern unsigned char u8g_font_hab19[];

extern unsigned char u8g_font_hab20[];
extern unsigned char u8g_font_hab21[];
extern unsigned char u8g_font_hab22[];
extern unsigned char u8g_font_hab23[];
extern unsigned char u8g_font_hab24[];
extern unsigned char u8g_font_hab25[];
extern unsigned char u8g_font_hab26[];
extern unsigned char u8g_font_hab27[];
extern unsigned char u8g_font_hab28[];
extern unsigned char u8g_font_hab29[];

extern unsigned char u8g_font_hab30[];
extern unsigned char u8g_font_hab31[];
extern unsigned char u8g_font_hab32[];
extern unsigned char u8g_font_hab33[];
extern unsigned char u8g_font_hab34[];
extern unsigned char u8g_font_hab35[];
extern unsigned char u8g_font_hab36[];
extern unsigned char u8g_font_hab37[];
extern unsigned char u8g_font_hab38[];
extern unsigned char u8g_font_hab39[];

extern unsigned char u8g_font_hab40[];
extern unsigned char u8g_font_hab41[];
extern unsigned char u8g_font_hab42[];
extern unsigned char u8g_font_hab43[];
extern unsigned char u8g_font_hab44[];
extern unsigned char u8g_font_hab45[];
extern unsigned char u8g_font_hab46[];
extern unsigned char u8g_font_hab47[];
extern unsigned char u8g_font_hab48[];
extern unsigned char u8g_font_hab49[];

extern unsigned char u8g_font_hab50[];
extern unsigned char u8g_font_hab51[];
extern unsigned char u8g_font_hab52[];
extern unsigned char u8g_font_hab53[];
extern unsigned char u8g_font_hab54[];
extern unsigned char u8g_font_hab55[];
extern unsigned char u8g_font_hab56[];
extern unsigned char u8g_font_hab57[];
extern unsigned char u8g_font_hab58[];
extern unsigned char u8g_font_hab59[];



extern unsigned char u8g_font_gbr10[];
extern unsigned char u8g_font_gbr11[];
extern unsigned char u8g_font_gbr12[];
extern unsigned char u8g_font_gbr13[];
extern unsigned char u8g_font_gbr14[];
extern unsigned char u8g_font_gbr15[];
extern unsigned char u8g_font_gbr16[];
extern unsigned char u8g_font_gbr17[];
extern unsigned char u8g_font_gbr18[];
extern unsigned char u8g_font_gbr19[];

extern unsigned char u8g_font_gbr20[];
extern unsigned char u8g_font_gbr21[];
extern unsigned char u8g_font_gbr22[];
extern unsigned char u8g_font_gbr23[];
extern unsigned char u8g_font_gbr24[];
extern unsigned char u8g_font_gbr25[];
extern unsigned char u8g_font_gbr26[];
extern unsigned char u8g_font_gbr27[];
extern unsigned char u8g_font_gbr28[];
extern unsigned char u8g_font_gbr29[];

extern unsigned char u8g_font_gbr30[];
extern unsigned char u8g_font_gbr31[];
extern unsigned char u8g_font_gbr32[];
extern unsigned char u8g_font_gbr33[];
extern unsigned char u8g_font_gbr34[];
extern unsigned char u8g_font_gbr35[];
extern unsigned char u8g_font_gbr36[];
extern unsigned char u8g_font_gbr37[];
extern unsigned char u8g_font_gbr38[];
extern unsigned char u8g_font_gbr39[];

extern unsigned char u8g_font_gbr40[];
extern unsigned char u8g_font_gbr41[];
extern unsigned char u8g_font_gbr42[];
extern unsigned char u8g_font_gbr43[];
extern unsigned char u8g_font_gbr44[];
extern unsigned char u8g_font_gbr45[];
extern unsigned char u8g_font_gbr46[];
extern unsigned char u8g_font_gbr47[];
extern unsigned char u8g_font_gbr48[];
extern unsigned char u8g_font_gbr49[];

extern unsigned char u8g_font_gbr50[];
extern unsigned char u8g_font_gbr51[];
extern unsigned char u8g_font_gbr52[];
extern unsigned char u8g_font_gbr53[];
extern unsigned char u8g_font_gbr54[];
extern unsigned char u8g_font_gbr55[];
extern unsigned char u8g_font_gbr56[];
extern unsigned char u8g_font_gbr57[];
extern unsigned char u8g_font_gbr58[];
extern unsigned char u8g_font_gbr59[];

extern unsigned char u8g_font_gbb10[];
extern unsigned char u8g_font_gbb11[];
extern unsigned char u8g_font_gbb12[];
extern unsigned char u8g_font_gbb13[];
extern unsigned char u8g_font_gbb14[];
extern unsigned char u8g_font_gbb15[];
extern unsigned char u8g_font_gbb16[];
extern unsigned char u8g_font_gbb17[];
extern unsigned char u8g_font_gbb18[];
extern unsigned char u8g_font_gbb19[];

extern unsigned char u8g_font_gbb20[];
extern unsigned char u8g_font_gbb21[];
extern unsigned char u8g_font_gbb22[];
extern unsigned char u8g_font_gbb23[];
extern unsigned char u8g_font_gbb24[];
extern unsigned char u8g_font_gbb25[];
extern unsigned char u8g_font_gbb26[];
extern unsigned char u8g_font_gbb27[];
extern unsigned char u8g_font_gbb28[];
extern unsigned char u8g_font_gbb29[];

extern unsigned char u8g_font_gbb30[];
extern unsigned char u8g_font_gbb31[];
extern unsigned char u8g_font_gbb32[];
extern unsigned char u8g_font_gbb33[];
extern unsigned char u8g_font_gbb34[];
extern unsigned char u8g_font_gbb35[];
extern unsigned char u8g_font_gbb36[];
extern unsigned char u8g_font_gbb37[];
extern unsigned char u8g_font_gbb38[];
extern unsigned char u8g_font_gbb39[];

extern unsigned char u8g_font_gbb40[];
extern unsigned char u8g_font_gbb41[];
extern unsigned char u8g_font_gbb42[];
extern unsigned char u8g_font_gbb43[];
extern unsigned char u8g_font_gbb44[];
extern unsigned char u8g_font_gbb45[];
extern unsigned char u8g_font_gbb46[];
extern unsigned char u8g_font_gbb47[];
extern unsigned char u8g_font_gbb48[];
extern unsigned char u8g_font_gbb49[];

extern unsigned char u8g_font_gbb50[];
extern unsigned char u8g_font_gbb51[];
extern unsigned char u8g_font_gbb52[];
extern unsigned char u8g_font_gbb53[];
extern unsigned char u8g_font_gbb54[];
extern unsigned char u8g_font_gbb55[];
extern unsigned char u8g_font_gbb56[];
extern unsigned char u8g_font_gbb57[];
extern unsigned char u8g_font_gbb58[];
extern unsigned char u8g_font_gbb59[];

#endif

void pic_gen_short_desc(const u8g_pgm_uint8_t *font, const char *name, u8g_uint_t width, const char *real_name)
{
  char s[256];
  u8g_t u8g;
  u8g_Init(&u8g, &u8g_dev_pbm);
    u8g_SetFont(&u8g, font);
  
  if ( u8g_IsGlyph(&u8g, 'a') != 0 )
    sprintf(s, "%s: 123 ABC abcdefg", name);
  else
    sprintf(s, "0123456789");
    
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetFont(&u8g, font);
    u8g_DrawStr(&u8g, 0, 100, s);    
  }while( u8g_NextPage(&u8g) );
  
  {
    char cmd[256];
    u8g_SetFont(&u8g, font);
    sprintf(cmd, "convert u8g.pbm -trim %s_short.png", name );
    system(cmd);
  }
}



void pic_gen_font(const u8g_pgm_uint8_t *font, const char *name, u8g_uint_t width, const char *real_name)
{
  char s[256];
  const u8g_pgm_uint8_t *disp_font;
  uint16_t i;
  u8g_uint_t x,y,w,h, hcnt, disp_line_height, disp_line_indent;
  uint8_t start, end;
  //u8g_uint_t indent;
  u8g_t u8g;
  
  pic_gen_short_desc(font, name, width, real_name);
  
  
  u8g_Init(&u8g, &u8g_dev_pbm);
  
  disp_font = u8g_font_7x13;
  
  disp_line_height = 14;
  disp_line_indent = 75;
  
  start = u8g_font_GetFontStartEncoding(font);
  end = u8g_font_GetFontEndEncoding(font);
  
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetFont(&u8g, font);
    hcnt = u8g_GetWidth(&u8g);
    hcnt /= u8g_GetFontBBXWidth(&u8g);
    hcnt -= 4;
    
    w = u8g_GetFontBBXWidth(&u8g);
    w = width;
    h = u8g_GetFontBBXHeight(&u8g);
    if ( h < disp_line_height )
      h = disp_line_height ;

    sprintf(s, "%s, %s", name,
        real_name);
    
    u8g_SetFont(&u8g, disp_font);
    u8g_DrawStrFontBBX(&u8g, 0, disp_line_height, 0, s);
    
    u8g_SetFont(&u8g, font);
    sprintf(s, "BBX Width %d, Height %d,  Capital A %d", 
        u8g_GetFontBBXWidth(&u8g), 
        u8g_GetFontBBXHeight(&u8g), 
        u8g_GetFontCapitalAHeight(&u8g));
    
    u8g_SetFont(&u8g, disp_font);    
    u8g_DrawStrFontBBX(&u8g, 0, disp_line_height*2, 0, s);

    
    sprintf(s, "Font data size: %d", u8g_font_GetSize(font));
    u8g_DrawStrFontBBX(&u8g, 0, disp_line_height*3, 0, s);

    hcnt = 16;
    i = start - start % hcnt;
    for( y = 0; y < 16; y++ )
    {
      u8g_SetFont(&u8g, disp_font);
      if ( i <= end )
      {
        sprintf(s, "%3d/0x%02x", i, i);
        u8g_DrawStrFontBBX(&u8g, 0, y*h+disp_line_height*3+h, 0, s);
      }
      
      for( x = 0; x < hcnt; x++ )
      {
        if ( i <= end )
        {
          u8g_SetFont(&u8g, font);
          u8g_DrawGlyphFontBBX(&u8g, x*w+disp_line_indent, y*h+disp_line_height*3+h, 0, i);
          i++;
        }
      }
    }
  }while( u8g_NextPage(&u8g) );
  
  {
    char cmd[256];
    u8g_SetFont(&u8g, font);
    sprintf(cmd, "convert u8g.pbm -trim %s.png", name );
    system(cmd);
  }
}


int main(void)
{
#ifdef ANALYSE
  /*
  pic_gen_font(font10x20, font10x20, "u8g_10x20_", 10, "X11 Font");
  pic_gen_font(u8g_font_unicons36, font10x20, "u8g_font_unicons", 40, "unicons");
  pic_gen_font(u8g_font_unicons31, font10x20, "u8g_font_unicons", 30, "unicons");
  pic_gen_font(u8g_font_unicons24, font10x20, "u8g_font_unicons", 25, "unicons");
  pic_gen_font(u8g_font_judson_r22, u8g_font_judson_r22, "u8g_font_judson", 16, "judson");
  pic_gen_font(u8g_font_judson_r34, u8g_font_judson_r34, "u8g_font_judson", 24, "judson");
  pic_gen_font(u8g_font_judson_r34, u8g_font_judson_r34, "u8g_font_judson", 24, "judson");

  pic_gen_font(u8g_font_dg10, font10x20, "u8g_font_dg10_", 12, "DidactGothic");
  pic_gen_font(u8g_font_dg11, font10x20, "u8g_font_dg11_", 12, "DidactGothic");
  pic_gen_font(u8g_font_dg12, font10x20, "u8g_font_dg12_", 12, "DidactGothic");
  pic_gen_font(u8g_font_dg13, font10x20, "u8g_font_dg13_", 13, "DidactGothic");
  pic_gen_font(u8g_font_dg14, font10x20, "u8g_font_dg14_", 13, "DidactGothic");
  pic_gen_font(u8g_font_dg15, font10x20, "u8g_font_dg15_", 14, "DidactGothic");
  pic_gen_font(u8g_font_dg16, font10x20, "u8g_font_dg16_", 14, "DidactGothic");
  pic_gen_font(u8g_font_dg17, font10x20, "u8g_font_dg17_", 15, "DidactGothic");
  pic_gen_font(u8g_font_dg18, font10x20, "u8g_font_dg18_", 15, "DidactGothic");
  pic_gen_font(u8g_font_dg19, font10x20, "u8g_font_dg19_", 16, "DidactGothic");
  
  pic_gen_font(u8g_font_dg20, font10x20, "u8g_font_dg20_", 16, "DidactGothic");
  pic_gen_font(u8g_font_dg21, font10x20, "u8g_font_dg21_", 17, "DidactGothic");
  pic_gen_font(u8g_font_dg22, font10x20, "u8g_font_dg22_", 17, "DidactGothic");
  pic_gen_font(u8g_font_dg23, font10x20, "u8g_font_dg23_", 18, "DidactGothic");
  pic_gen_font(u8g_font_dg24, font10x20, "u8g_font_dg24_", 18, "DidactGothic");
  pic_gen_font(u8g_font_dg25, font10x20, "u8g_font_dg25_", 19, "DidactGothic");
  pic_gen_font(u8g_font_dg26, font10x20, "u8g_font_dg26_", 19, "DidactGothic");
  pic_gen_font(u8g_font_dg27, font10x20, "u8g_font_dg27_", 20, "DidactGothic");
  pic_gen_font(u8g_font_dg28, font10x20, "u8g_font_dg28_", 21, "DidactGothic");
  pic_gen_font(u8g_font_dg29, font10x20, "u8g_font_dg29_", 21, "DidactGothic");
  
  pic_gen_font(u8g_font_dg30, font10x20, "u8g_font_dg30_", 23, "DidactGothic");
  pic_gen_font(u8g_font_dg31, font10x20, "u8g_font_dg31_", 24, "DidactGothic");
  pic_gen_font(u8g_font_dg32, font10x20, "u8g_font_dg32_", 24, "DidactGothic");
  pic_gen_font(u8g_font_dg33, font10x20, "u8g_font_dg33_", 25, "DidactGothic");
  pic_gen_font(u8g_font_dg34, font10x20, "u8g_font_dg34_", 26, "DidactGothic");
  pic_gen_font(u8g_font_dg35, font10x20, "u8g_font_dg35_", 26, "DidactGothic");
  pic_gen_font(u8g_font_dg36, font10x20, "u8g_font_dg36_", 27, "DidactGothic");
  pic_gen_font(u8g_font_dg37, font10x20, "u8g_font_dg37_", 28, "DidactGothic");
  pic_gen_font(u8g_font_dg38, font10x20, "u8g_font_dg38_", 29, "DidactGothic");
  pic_gen_font(u8g_font_dg39, font10x20, "u8g_font_dg39_", 30, "DidactGothic");

  pic_gen_font(u8g_font_dg40, font10x20, "u8g_font_dg40_", 31, "DidactGothic");
  pic_gen_font(u8g_font_dg41, font10x20, "u8g_font_dg41_", 32, "DidactGothic");
  pic_gen_font(u8g_font_dg42, font10x20, "u8g_font_dg42_", 33, "DidactGothic");
  pic_gen_font(u8g_font_dg43, font10x20, "u8g_font_dg43_", 33, "DidactGothic");
  pic_gen_font(u8g_font_dg44, font10x20, "u8g_font_dg44_", 35, "DidactGothic");
  pic_gen_font(u8g_font_dg45, font10x20, "u8g_font_dg45_", 36, "DidactGothic");
  pic_gen_font(u8g_font_dg46, font10x20, "u8g_font_dg46_", 37, "DidactGothic");
  pic_gen_font(u8g_font_dg47, font10x20, "u8g_font_dg47_", 38, "DidactGothic");
  pic_gen_font(u8g_font_dg48, font10x20, "u8g_font_dg48_", 39, "DidactGothic");
  pic_gen_font(u8g_font_dg49, font10x20, "u8g_font_dg49_", 40, "DidactGothic");

  pic_gen_font(u8g_font_dg50, font10x20, "u8g_font_dg50_", 41, "DidactGothic");
  pic_gen_font(u8g_font_dg51, font10x20, "u8g_font_dg51_", 42, "DidactGothic");
  pic_gen_font(u8g_font_dg52, font10x20, "u8g_font_dg52_", 43, "DidactGothic");
  pic_gen_font(u8g_font_dg53, font10x20, "u8g_font_dg53_", 43, "DidactGothic");
  pic_gen_font(u8g_font_dg54, font10x20, "u8g_font_dg54_", 45, "DidactGothic");
  pic_gen_font(u8g_font_dg55, font10x20, "u8g_font_dg55_", 46, "DidactGothic");
  pic_gen_font(u8g_font_dg56, font10x20, "u8g_font_dg56_", 47, "DidactGothic");
  pic_gen_font(u8g_font_dg57, font10x20, "u8g_font_dg57_", 48, "DidactGothic");
  pic_gen_font(u8g_font_dg58, font10x20, "u8g_font_dg58_", 49, "DidactGothic");
  pic_gen_font(u8g_font_dg59, font10x20, "u8g_font_dg59_", 50, "DidactGothic");
*/

/*


  pic_gen_font(u8g_font_llr10, font10x20, "u8g_font_llr10_", 12, "LinLibertine");
  pic_gen_font(u8g_font_llr11, font10x20, "u8g_font_llr11_", 12, "LinLibertine");
  pic_gen_font(u8g_font_llr12, font10x20, "u8g_font_llr12_", 12, "LinLibertine");
  pic_gen_font(u8g_font_llr13, font10x20, "u8g_font_llr13_", 13, "LinLibertine");
  pic_gen_font(u8g_font_llr14, font10x20, "u8g_font_llr14_", 13, "LinLibertine");
  pic_gen_font(u8g_font_llr15, font10x20, "u8g_font_llr15_", 14, "LinLibertine");
  pic_gen_font(u8g_font_llr16, font10x20, "u8g_font_llr16_", 14, "LinLibertine");
  pic_gen_font(u8g_font_llr17, font10x20, "u8g_font_llr17_", 15, "LinLibertine");
  pic_gen_font(u8g_font_llr18, font10x20, "u8g_font_llr18_", 15, "LinLibertine");
  pic_gen_font(u8g_font_llr19, font10x20, "u8g_font_llr19_", 16, "LinLibertine");
  
  pic_gen_font(u8g_font_llr20, font10x20, "u8g_font_llr20_", 16, "LinLibertine");
  pic_gen_font(u8g_font_llr21, font10x20, "u8g_font_llr21_", 17, "LinLibertine");
  pic_gen_font(u8g_font_llr22, font10x20, "u8g_font_llr22_", 17, "LinLibertine");
  pic_gen_font(u8g_font_llr23, font10x20, "u8g_font_llr23_", 18, "LinLibertine");
  pic_gen_font(u8g_font_llr24, font10x20, "u8g_font_llr24_", 18, "LinLibertine");
  pic_gen_font(u8g_font_llr25, font10x20, "u8g_font_llr25_", 19, "LinLibertine");
  pic_gen_font(u8g_font_llr26, font10x20, "u8g_font_llr26_", 19, "LinLibertine");
  pic_gen_font(u8g_font_llr27, font10x20, "u8g_font_llr27_", 20, "LinLibertine");
  pic_gen_font(u8g_font_llr28, font10x20, "u8g_font_llr28_", 21, "LinLibertine");
  pic_gen_font(u8g_font_llr29, font10x20, "u8g_font_llr29_", 21, "LinLibertine");
  
  pic_gen_font(u8g_font_llr30, font10x20, "u8g_font_llr30_", 23, "LinLibertine");
  pic_gen_font(u8g_font_llr31, font10x20, "u8g_font_llr31_", 24, "LinLibertine");
  pic_gen_font(u8g_font_llr32, font10x20, "u8g_font_llr32_", 24, "LinLibertine");
  pic_gen_font(u8g_font_llr33, font10x20, "u8g_font_llr33_", 25, "LinLibertine");
  pic_gen_font(u8g_font_llr34, font10x20, "u8g_font_llr34_", 26, "LinLibertine");
  pic_gen_font(u8g_font_llr35, font10x20, "u8g_font_llr35_", 26, "LinLibertine");
  pic_gen_font(u8g_font_llr36, font10x20, "u8g_font_llr36_", 27, "LinLibertine");
  pic_gen_font(u8g_font_llr37, font10x20, "u8g_font_llr37_", 28, "LinLibertine");
  pic_gen_font(u8g_font_llr38, font10x20, "u8g_font_llr38_", 29, "LinLibertine");
  pic_gen_font(u8g_font_llr39, font10x20, "u8g_font_llr39_", 30, "LinLibertine");

  pic_gen_font(u8g_font_llr40, font10x20, "u8g_font_llr40_", 31, "LinLibertine");
  pic_gen_font(u8g_font_llr41, font10x20, "u8g_font_llr41_", 32, "LinLibertine");
  pic_gen_font(u8g_font_llr42, font10x20, "u8g_font_llr42_", 33, "LinLibertine");
  pic_gen_font(u8g_font_llr43, font10x20, "u8g_font_llr43_", 33, "LinLibertine");
  pic_gen_font(u8g_font_llr44, font10x20, "u8g_font_llr44_", 35, "LinLibertine");
  pic_gen_font(u8g_font_llr45, font10x20, "u8g_font_llr45_", 36, "LinLibertine");
  pic_gen_font(u8g_font_llr46, font10x20, "u8g_font_llr46_", 37, "LinLibertine");
  pic_gen_font(u8g_font_llr47, font10x20, "u8g_font_llr47_", 38, "LinLibertine");
  pic_gen_font(u8g_font_llr48, font10x20, "u8g_font_llr48_", 39, "LinLibertine");
  pic_gen_font(u8g_font_llr49, font10x20, "u8g_font_llr49_", 40, "LinLibertine");

  pic_gen_font(u8g_font_llr50, font10x20, "u8g_font_llr50_", 41, "LinLibertine");
  pic_gen_font(u8g_font_llr51, font10x20, "u8g_font_llr51_", 42, "LinLibertine");
  pic_gen_font(u8g_font_llr52, font10x20, "u8g_font_llr52_", 43, "LinLibertine");
  pic_gen_font(u8g_font_llr53, font10x20, "u8g_font_llr53_", 43, "LinLibertine");
  pic_gen_font(u8g_font_llr54, font10x20, "u8g_font_llr54_", 45, "LinLibertine");
  pic_gen_font(u8g_font_llr55, font10x20, "u8g_font_llr55_", 46, "LinLibertine");
  pic_gen_font(u8g_font_llr56, font10x20, "u8g_font_llr56_", 47, "LinLibertine");
  pic_gen_font(u8g_font_llr57, font10x20, "u8g_font_llr57_", 48, "LinLibertine");
  pic_gen_font(u8g_font_llr58, font10x20, "u8g_font_llr58_", 49, "LinLibertine");
  pic_gen_font(u8g_font_llr59, font10x20, "u8g_font_llr59_", 50, "LinLibertine");

  pic_gen_font(u8g_font_llb10, font10x20, "u8g_font_llb10_", 12, "LinLibertine");
  pic_gen_font(u8g_font_llb11, font10x20, "u8g_font_llb11_", 12, "LinLibertine");
  pic_gen_font(u8g_font_llb12, font10x20, "u8g_font_llb12_", 12, "LinLibertine");
  pic_gen_font(u8g_font_llb13, font10x20, "u8g_font_llb13_", 13, "LinLibertine");
  pic_gen_font(u8g_font_llb14, font10x20, "u8g_font_llb14_", 13, "LinLibertine");
  pic_gen_font(u8g_font_llb15, font10x20, "u8g_font_llb15_", 14, "LinLibertine");
  pic_gen_font(u8g_font_llb16, font10x20, "u8g_font_llb16_", 14, "LinLibertine");
  pic_gen_font(u8g_font_llb17, font10x20, "u8g_font_llb17_", 15, "LinLibertine");
  pic_gen_font(u8g_font_llb18, font10x20, "u8g_font_llb18_", 15, "LinLibertine");
  pic_gen_font(u8g_font_llb19, font10x20, "u8g_font_llb19_", 16, "LinLibertine");
  
  pic_gen_font(u8g_font_llb20, font10x20, "u8g_font_llb20_", 16, "LinLibertine");
  pic_gen_font(u8g_font_llb21, font10x20, "u8g_font_llb21_", 17, "LinLibertine");
  pic_gen_font(u8g_font_llb22, font10x20, "u8g_font_llb22_", 17, "LinLibertine");
  pic_gen_font(u8g_font_llb23, font10x20, "u8g_font_llb23_", 18, "LinLibertine");
  pic_gen_font(u8g_font_llb24, font10x20, "u8g_font_llb24_", 18, "LinLibertine");
  pic_gen_font(u8g_font_llb25, font10x20, "u8g_font_llb25_", 19, "LinLibertine");
  pic_gen_font(u8g_font_llb26, font10x20, "u8g_font_llb26_", 19, "LinLibertine");
  pic_gen_font(u8g_font_llb27, font10x20, "u8g_font_llb27_", 20, "LinLibertine");
  pic_gen_font(u8g_font_llb28, font10x20, "u8g_font_llb28_", 21, "LinLibertine");
  pic_gen_font(u8g_font_llb29, font10x20, "u8g_font_llb29_", 21, "LinLibertine");
  
  pic_gen_font(u8g_font_llb30, font10x20, "u8g_font_llb30_", 23, "LinLibertine");
  pic_gen_font(u8g_font_llb31, font10x20, "u8g_font_llb31_", 24, "LinLibertine");
  pic_gen_font(u8g_font_llb32, font10x20, "u8g_font_llb32_", 24, "LinLibertine");
  pic_gen_font(u8g_font_llb33, font10x20, "u8g_font_llb33_", 25, "LinLibertine");
  pic_gen_font(u8g_font_llb34, font10x20, "u8g_font_llb34_", 26, "LinLibertine");
  pic_gen_font(u8g_font_llb35, font10x20, "u8g_font_llb35_", 26, "LinLibertine");
  pic_gen_font(u8g_font_llb36, font10x20, "u8g_font_llb36_", 27, "LinLibertine");
  pic_gen_font(u8g_font_llb37, font10x20, "u8g_font_llb37_", 28, "LinLibertine");
  pic_gen_font(u8g_font_llb38, font10x20, "u8g_font_llb38_", 29, "LinLibertine");
  pic_gen_font(u8g_font_llb39, font10x20, "u8g_font_llb39_", 30, "LinLibertine");

  pic_gen_font(u8g_font_llb40, font10x20, "u8g_font_llb40_", 31, "LinLibertine");
  pic_gen_font(u8g_font_llb41, font10x20, "u8g_font_llb41_", 32, "LinLibertine");
  pic_gen_font(u8g_font_llb42, font10x20, "u8g_font_llb42_", 33, "LinLibertine");
  pic_gen_font(u8g_font_llb43, font10x20, "u8g_font_llb43_", 33, "LinLibertine");
  pic_gen_font(u8g_font_llb44, font10x20, "u8g_font_llb44_", 35, "LinLibertine");
  pic_gen_font(u8g_font_llb45, font10x20, "u8g_font_llb45_", 36, "LinLibertine");
  pic_gen_font(u8g_font_llb46, font10x20, "u8g_font_llb46_", 37, "LinLibertine");
  pic_gen_font(u8g_font_llb47, font10x20, "u8g_font_llb47_", 38, "LinLibertine");
  pic_gen_font(u8g_font_llb48, font10x20, "u8g_font_llb48_", 39, "LinLibertine");
  pic_gen_font(u8g_font_llb49, font10x20, "u8g_font_llb49_", 40, "LinLibertine");

  pic_gen_font(u8g_font_llb50, font10x20, "u8g_font_llb50_", 41, "LinLibertine");
  pic_gen_font(u8g_font_llb51, font10x20, "u8g_font_llb51_", 42, "LinLibertine");
  pic_gen_font(u8g_font_llb52, font10x20, "u8g_font_llb52_", 43, "LinLibertine");
  pic_gen_font(u8g_font_llb53, font10x20, "u8g_font_llb53_", 43, "LinLibertine");
  pic_gen_font(u8g_font_llb54, font10x20, "u8g_font_llb54_", 45, "LinLibertine");
  pic_gen_font(u8g_font_llb55, font10x20, "u8g_font_llb55_", 46, "LinLibertine");
  pic_gen_font(u8g_font_llb56, font10x20, "u8g_font_llb56_", 47, "LinLibertine");
  pic_gen_font(u8g_font_llb57, font10x20, "u8g_font_llb57_", 48, "LinLibertine");
  pic_gen_font(u8g_font_llb58, font10x20, "u8g_font_llb58_", 49, "LinLibertine");
  pic_gen_font(u8g_font_llb59, font10x20, "u8g_font_llb59_", 50, "LinLibertine");
*/

/*

  pic_gen_font(u8g_font_fur10, font10x20, "u8g_font_fur10_", 12, "FreeUnivers");
  pic_gen_font(u8g_font_fur11, font10x20, "u8g_font_fur11_", 12, "FreeUnivers");
  pic_gen_font(u8g_font_fur12, font10x20, "u8g_font_fur12_", 12, "FreeUnivers");
  pic_gen_font(u8g_font_fur13, font10x20, "u8g_font_fur13_", 13, "FreeUnivers");
  pic_gen_font(u8g_font_fur14, font10x20, "u8g_font_fur14_", 13, "FreeUnivers");
  pic_gen_font(u8g_font_fur15, font10x20, "u8g_font_fur15_", 14, "FreeUnivers");
  pic_gen_font(u8g_font_fur16, font10x20, "u8g_font_fur16_", 14, "FreeUnivers");
  pic_gen_font(u8g_font_fur17, font10x20, "u8g_font_fur17_", 15, "FreeUnivers");
  pic_gen_font(u8g_font_fur18, font10x20, "u8g_font_fur18_", 15, "FreeUnivers");
  pic_gen_font(u8g_font_fur19, font10x20, "u8g_font_fur19_", 16, "FreeUnivers");
  
  pic_gen_font(u8g_font_fur20, font10x20, "u8g_font_fur20_", 16, "FreeUnivers");
  pic_gen_font(u8g_font_fur21, font10x20, "u8g_font_fur21_", 17, "FreeUnivers");
  pic_gen_font(u8g_font_fur22, font10x20, "u8g_font_fur22_", 17, "FreeUnivers");
  pic_gen_font(u8g_font_fur23, font10x20, "u8g_font_fur23_", 18, "FreeUnivers");
  pic_gen_font(u8g_font_fur24, font10x20, "u8g_font_fur24_", 18, "FreeUnivers");
  pic_gen_font(u8g_font_fur25, font10x20, "u8g_font_fur25_", 19, "FreeUnivers");
  pic_gen_font(u8g_font_fur26, font10x20, "u8g_font_fur26_", 19, "FreeUnivers");
  pic_gen_font(u8g_font_fur27, font10x20, "u8g_font_fur27_", 20, "FreeUnivers");
  pic_gen_font(u8g_font_fur28, font10x20, "u8g_font_fur28_", 21, "FreeUnivers");
  pic_gen_font(u8g_font_fur29, font10x20, "u8g_font_fur29_", 21, "FreeUnivers");
  
  pic_gen_font(u8g_font_fur30, font10x20, "u8g_font_fur30_", 23, "FreeUnivers");
  pic_gen_font(u8g_font_fur31, font10x20, "u8g_font_fur31_", 24, "FreeUnivers");
  pic_gen_font(u8g_font_fur32, font10x20, "u8g_font_fur32_", 24, "FreeUnivers");
  pic_gen_font(u8g_font_fur33, font10x20, "u8g_font_fur33_", 25, "FreeUnivers");
  pic_gen_font(u8g_font_fur34, font10x20, "u8g_font_fur34_", 26, "FreeUnivers");
  pic_gen_font(u8g_font_fur35, font10x20, "u8g_font_fur35_", 26, "FreeUnivers");
  pic_gen_font(u8g_font_fur36, font10x20, "u8g_font_fur36_", 27, "FreeUnivers");
  pic_gen_font(u8g_font_fur37, font10x20, "u8g_font_fur37_", 28, "FreeUnivers");
  pic_gen_font(u8g_font_fur38, font10x20, "u8g_font_fur38_", 29, "FreeUnivers");
  pic_gen_font(u8g_font_fur39, font10x20, "u8g_font_fur39_", 30, "FreeUnivers");

  pic_gen_font(u8g_font_fur40, font10x20, "u8g_font_fur40_", 31, "FreeUnivers");
  pic_gen_font(u8g_font_fur41, font10x20, "u8g_font_fur41_", 32, "FreeUnivers");
  pic_gen_font(u8g_font_fur42, font10x20, "u8g_font_fur42_", 33, "FreeUnivers");
  pic_gen_font(u8g_font_fur43, font10x20, "u8g_font_fur43_", 33, "FreeUnivers");
  pic_gen_font(u8g_font_fur44, font10x20, "u8g_font_fur44_", 35, "FreeUnivers");
  pic_gen_font(u8g_font_fur45, font10x20, "u8g_font_fur45_", 36, "FreeUnivers");
  pic_gen_font(u8g_font_fur46, font10x20, "u8g_font_fur46_", 37, "FreeUnivers");
  pic_gen_font(u8g_font_fur47, font10x20, "u8g_font_fur47_", 38, "FreeUnivers");
  pic_gen_font(u8g_font_fur48, font10x20, "u8g_font_fur48_", 39, "FreeUnivers");
  pic_gen_font(u8g_font_fur49, font10x20, "u8g_font_fur49_", 40, "FreeUnivers");

  pic_gen_font(u8g_font_fur50, font10x20, "u8g_font_fur50_", 41, "FreeUnivers");
  pic_gen_font(u8g_font_fur51, font10x20, "u8g_font_fur51_", 42, "FreeUnivers");
  pic_gen_font(u8g_font_fur52, font10x20, "u8g_font_fur52_", 43, "FreeUnivers");
  pic_gen_font(u8g_font_fur53, font10x20, "u8g_font_fur53_", 43, "FreeUnivers");
  pic_gen_font(u8g_font_fur54, font10x20, "u8g_font_fur54_", 45, "FreeUnivers");
  pic_gen_font(u8g_font_fur55, font10x20, "u8g_font_fur55_", 46, "FreeUnivers");
  pic_gen_font(u8g_font_fur56, font10x20, "u8g_font_fur56_", 47, "FreeUnivers");
  pic_gen_font(u8g_font_fur57, font10x20, "u8g_font_fur57_", 48, "FreeUnivers");
  pic_gen_font(u8g_font_fur58, font10x20, "u8g_font_fur58_", 49, "FreeUnivers");
  pic_gen_font(u8g_font_fur59, font10x20, "u8g_font_fur59_", 50, "FreeUnivers");

  pic_gen_font(u8g_font_fub10, font10x20, "u8g_font_fub10_", 12, "FreeUnivers");
  pic_gen_font(u8g_font_fub11, font10x20, "u8g_font_fub11_", 12, "FreeUnivers");
  pic_gen_font(u8g_font_fub12, font10x20, "u8g_font_fub12_", 12, "FreeUnivers");
  pic_gen_font(u8g_font_fub13, font10x20, "u8g_font_fub13_", 13, "FreeUnivers");
  pic_gen_font(u8g_font_fub14, font10x20, "u8g_font_fub14_", 13, "FreeUnivers");
  pic_gen_font(u8g_font_fub15, font10x20, "u8g_font_fub15_", 14, "FreeUnivers");
  pic_gen_font(u8g_font_fub16, font10x20, "u8g_font_fub16_", 14, "FreeUnivers");
  pic_gen_font(u8g_font_fub17, font10x20, "u8g_font_fub17_", 15, "FreeUnivers");
  pic_gen_font(u8g_font_fub18, font10x20, "u8g_font_fub18_", 15, "FreeUnivers");
  pic_gen_font(u8g_font_fub19, font10x20, "u8g_font_fub19_", 16, "FreeUnivers");
  
  pic_gen_font(u8g_font_fub20, font10x20, "u8g_font_fub20_", 16, "FreeUnivers");
  pic_gen_font(u8g_font_fub21, font10x20, "u8g_font_fub21_", 17, "FreeUnivers");
  pic_gen_font(u8g_font_fub22, font10x20, "u8g_font_fub22_", 17, "FreeUnivers");
  pic_gen_font(u8g_font_fub23, font10x20, "u8g_font_fub23_", 18, "FreeUnivers");
  pic_gen_font(u8g_font_fub24, font10x20, "u8g_font_fub24_", 18, "FreeUnivers");
  pic_gen_font(u8g_font_fub25, font10x20, "u8g_font_fub25_", 19, "FreeUnivers");
  pic_gen_font(u8g_font_fub26, font10x20, "u8g_font_fub26_", 19, "FreeUnivers");
  pic_gen_font(u8g_font_fub27, font10x20, "u8g_font_fub27_", 20, "FreeUnivers");
  pic_gen_font(u8g_font_fub28, font10x20, "u8g_font_fub28_", 21, "FreeUnivers");
  pic_gen_font(u8g_font_fub29, font10x20, "u8g_font_fub29_", 21, "FreeUnivers");
  
  pic_gen_font(u8g_font_fub30, font10x20, "u8g_font_fub30_", 23, "FreeUnivers");
  pic_gen_font(u8g_font_fub31, font10x20, "u8g_font_fub31_", 24, "FreeUnivers");
  pic_gen_font(u8g_font_fub32, font10x20, "u8g_font_fub32_", 24, "FreeUnivers");
  pic_gen_font(u8g_font_fub33, font10x20, "u8g_font_fub33_", 25, "FreeUnivers");
  pic_gen_font(u8g_font_fub34, font10x20, "u8g_font_fub34_", 26, "FreeUnivers");
  pic_gen_font(u8g_font_fub35, font10x20, "u8g_font_fub35_", 26, "FreeUnivers");
  pic_gen_font(u8g_font_fub36, font10x20, "u8g_font_fub36_", 27, "FreeUnivers");
  pic_gen_font(u8g_font_fub37, font10x20, "u8g_font_fub37_", 28, "FreeUnivers");
  pic_gen_font(u8g_font_fub38, font10x20, "u8g_font_fub38_", 29, "FreeUnivers");
  pic_gen_font(u8g_font_fub39, font10x20, "u8g_font_fub39_", 30, "FreeUnivers");

  pic_gen_font(u8g_font_fub40, font10x20, "u8g_font_fub40_", 31, "FreeUnivers");
  pic_gen_font(u8g_font_fub41, font10x20, "u8g_font_fub41_", 32, "FreeUnivers");
  pic_gen_font(u8g_font_fub42, font10x20, "u8g_font_fub42_", 33, "FreeUnivers");
  pic_gen_font(u8g_font_fub43, font10x20, "u8g_font_fub43_", 33, "FreeUnivers");
  pic_gen_font(u8g_font_fub44, font10x20, "u8g_font_fub44_", 35, "FreeUnivers");
  pic_gen_font(u8g_font_fub45, font10x20, "u8g_font_fub45_", 36, "FreeUnivers");
  pic_gen_font(u8g_font_fub46, font10x20, "u8g_font_fub46_", 37, "FreeUnivers");
  pic_gen_font(u8g_font_fub47, font10x20, "u8g_font_fub47_", 38, "FreeUnivers");
  pic_gen_font(u8g_font_fub48, font10x20, "u8g_font_fub48_", 39, "FreeUnivers");
  pic_gen_font(u8g_font_fub49, font10x20, "u8g_font_fub49_", 40, "FreeUnivers");

  pic_gen_font(u8g_font_fub50, font10x20, "u8g_font_fub50_", 41, "FreeUnivers");
  pic_gen_font(u8g_font_fub51, font10x20, "u8g_font_fub51_", 42, "FreeUnivers");
  pic_gen_font(u8g_font_fub52, font10x20, "u8g_font_fub52_", 43, "FreeUnivers");
  pic_gen_font(u8g_font_fub53, font10x20, "u8g_font_fub53_", 43, "FreeUnivers");
  pic_gen_font(u8g_font_fub54, font10x20, "u8g_font_fub54_", 45, "FreeUnivers");
  pic_gen_font(u8g_font_fub55, font10x20, "u8g_font_fub55_", 46, "FreeUnivers");
  pic_gen_font(u8g_font_fub56, font10x20, "u8g_font_fub56_", 47, "FreeUnivers");
  pic_gen_font(u8g_font_fub57, font10x20, "u8g_font_fub57_", 48, "FreeUnivers");
  pic_gen_font(u8g_font_fub58, font10x20, "u8g_font_fub58_", 49, "FreeUnivers");
  pic_gen_font(u8g_font_fub59, font10x20, "u8g_font_fub59_", 50, "FreeUnivers");
*/

/*
  pic_gen_font(u8g_font_osr10, font10x20, "u8g_font_osr10_", 12, "OldStandard");
  pic_gen_font(u8g_font_osr11, font10x20, "u8g_font_osr11_", 12, "OldStandard");
  pic_gen_font(u8g_font_osr12, font10x20, "u8g_font_osr12_", 12, "OldStandard");
  pic_gen_font(u8g_font_osr13, font10x20, "u8g_font_osr13_", 13, "OldStandard");
  pic_gen_font(u8g_font_osr14, font10x20, "u8g_font_osr14_", 13, "OldStandard");
  pic_gen_font(u8g_font_osr15, font10x20, "u8g_font_osr15_", 14, "OldStandard");
  pic_gen_font(u8g_font_osr16, font10x20, "u8g_font_osr16_", 14, "OldStandard");
  pic_gen_font(u8g_font_osr17, font10x20, "u8g_font_osr17_", 15, "OldStandard");
  pic_gen_font(u8g_font_osr18, font10x20, "u8g_font_osr18_", 15, "OldStandard");
  pic_gen_font(u8g_font_osr19, font10x20, "u8g_font_osr19_", 16, "OldStandard");
  
  pic_gen_font(u8g_font_osr20, font10x20, "u8g_font_osr20_", 16, "OldStandard");
  pic_gen_font(u8g_font_osr21, font10x20, "u8g_font_osr21_", 17, "OldStandard");
  pic_gen_font(u8g_font_osr22, font10x20, "u8g_font_osr22_", 17, "OldStandard");
  pic_gen_font(u8g_font_osr23, font10x20, "u8g_font_osr23_", 18, "OldStandard");
  pic_gen_font(u8g_font_osr24, font10x20, "u8g_font_osr24_", 18, "OldStandard");
  pic_gen_font(u8g_font_osr25, font10x20, "u8g_font_osr25_", 19, "OldStandard");
  pic_gen_font(u8g_font_osr26, font10x20, "u8g_font_osr26_", 19, "OldStandard");
  pic_gen_font(u8g_font_osr27, font10x20, "u8g_font_osr27_", 20, "OldStandard");
  pic_gen_font(u8g_font_osr28, font10x20, "u8g_font_osr28_", 21, "OldStandard");
  pic_gen_font(u8g_font_osr29, font10x20, "u8g_font_osr29_", 21, "OldStandard");
  
  pic_gen_font(u8g_font_osr30, font10x20, "u8g_font_osr30_", 23, "OldStandard");
  pic_gen_font(u8g_font_osr31, font10x20, "u8g_font_osr31_", 24, "OldStandard");
  pic_gen_font(u8g_font_osr32, font10x20, "u8g_font_osr32_", 24, "OldStandard");
  pic_gen_font(u8g_font_osr33, font10x20, "u8g_font_osr33_", 25, "OldStandard");
  pic_gen_font(u8g_font_osr34, font10x20, "u8g_font_osr34_", 26, "OldStandard");
  pic_gen_font(u8g_font_osr35, font10x20, "u8g_font_osr35_", 26, "OldStandard");
  pic_gen_font(u8g_font_osr36, font10x20, "u8g_font_osr36_", 27, "OldStandard");
  pic_gen_font(u8g_font_osr37, font10x20, "u8g_font_osr37_", 28, "OldStandard");
  pic_gen_font(u8g_font_osr38, font10x20, "u8g_font_osr38_", 29, "OldStandard");
  pic_gen_font(u8g_font_osr39, font10x20, "u8g_font_osr39_", 30, "OldStandard");

  pic_gen_font(u8g_font_osr40, font10x20, "u8g_font_osr40_", 31, "OldStandard");
  pic_gen_font(u8g_font_osr41, font10x20, "u8g_font_osr41_", 32, "OldStandard");
  pic_gen_font(u8g_font_osr42, font10x20, "u8g_font_osr42_", 33, "OldStandard");
  pic_gen_font(u8g_font_osr43, font10x20, "u8g_font_osr43_", 33, "OldStandard");
  pic_gen_font(u8g_font_osr44, font10x20, "u8g_font_osr44_", 35, "OldStandard");
  pic_gen_font(u8g_font_osr45, font10x20, "u8g_font_osr45_", 36, "OldStandard");
  pic_gen_font(u8g_font_osr46, font10x20, "u8g_font_osr46_", 37, "OldStandard");
  pic_gen_font(u8g_font_osr47, font10x20, "u8g_font_osr47_", 38, "OldStandard");
  pic_gen_font(u8g_font_osr48, font10x20, "u8g_font_osr48_", 39, "OldStandard");
  pic_gen_font(u8g_font_osr49, font10x20, "u8g_font_osr49_", 40, "OldStandard");

  pic_gen_font(u8g_font_osr50, font10x20, "u8g_font_osr50_", 41, "OldStandard");
  pic_gen_font(u8g_font_osr51, font10x20, "u8g_font_osr51_", 42, "OldStandard");
  pic_gen_font(u8g_font_osr52, font10x20, "u8g_font_osr52_", 43, "OldStandard");
  pic_gen_font(u8g_font_osr53, font10x20, "u8g_font_osr53_", 43, "OldStandard");
  pic_gen_font(u8g_font_osr54, font10x20, "u8g_font_osr54_", 45, "OldStandard");
  pic_gen_font(u8g_font_osr55, font10x20, "u8g_font_osr55_", 46, "OldStandard");
  pic_gen_font(u8g_font_osr56, font10x20, "u8g_font_osr56_", 47, "OldStandard");
  pic_gen_font(u8g_font_osr57, font10x20, "u8g_font_osr57_", 48, "OldStandard");
  pic_gen_font(u8g_font_osr58, font10x20, "u8g_font_osr58_", 49, "OldStandard");
  pic_gen_font(u8g_font_osr59, font10x20, "u8g_font_osr59_", 50, "OldStandard");

  pic_gen_font(u8g_font_osb10, font10x20, "u8g_font_osb10_", 12, "OldStandard");
  pic_gen_font(u8g_font_osb11, font10x20, "u8g_font_osb11_", 12, "OldStandard");
  pic_gen_font(u8g_font_osb12, font10x20, "u8g_font_osb12_", 12, "OldStandard");
  pic_gen_font(u8g_font_osb13, font10x20, "u8g_font_osb13_", 13, "OldStandard");
  pic_gen_font(u8g_font_osb14, font10x20, "u8g_font_osb14_", 13, "OldStandard");
  pic_gen_font(u8g_font_osb15, font10x20, "u8g_font_osb15_", 14, "OldStandard");
  pic_gen_font(u8g_font_osb16, font10x20, "u8g_font_osb16_", 14, "OldStandard");
  pic_gen_font(u8g_font_osb17, font10x20, "u8g_font_osb17_", 15, "OldStandard");
  pic_gen_font(u8g_font_osb18, font10x20, "u8g_font_osb18_", 15, "OldStandard");
  pic_gen_font(u8g_font_osb19, font10x20, "u8g_font_osb19_", 16, "OldStandard");
  
  pic_gen_font(u8g_font_osb20, font10x20, "u8g_font_osb20_", 16, "OldStandard");
  pic_gen_font(u8g_font_osb21, font10x20, "u8g_font_osb21_", 17, "OldStandard");
  pic_gen_font(u8g_font_osb22, font10x20, "u8g_font_osb22_", 17, "OldStandard");
  pic_gen_font(u8g_font_osb23, font10x20, "u8g_font_osb23_", 18, "OldStandard");
  pic_gen_font(u8g_font_osb24, font10x20, "u8g_font_osb24_", 18, "OldStandard");
  pic_gen_font(u8g_font_osb25, font10x20, "u8g_font_osb25_", 19, "OldStandard");
  pic_gen_font(u8g_font_osb26, font10x20, "u8g_font_osb26_", 19, "OldStandard");
  pic_gen_font(u8g_font_osb27, font10x20, "u8g_font_osb27_", 20, "OldStandard");
  pic_gen_font(u8g_font_osb28, font10x20, "u8g_font_osb28_", 21, "OldStandard");
  pic_gen_font(u8g_font_osb29, font10x20, "u8g_font_osb29_", 21, "OldStandard");
  
  pic_gen_font(u8g_font_osb30, font10x20, "u8g_font_osb30_", 23, "OldStandard");
  pic_gen_font(u8g_font_osb31, font10x20, "u8g_font_osb31_", 24, "OldStandard");
  pic_gen_font(u8g_font_osb32, font10x20, "u8g_font_osb32_", 24, "OldStandard");
  pic_gen_font(u8g_font_osb33, font10x20, "u8g_font_osb33_", 25, "OldStandard");
  pic_gen_font(u8g_font_osb34, font10x20, "u8g_font_osb34_", 26, "OldStandard");
  pic_gen_font(u8g_font_osb35, font10x20, "u8g_font_osb35_", 26, "OldStandard");
  pic_gen_font(u8g_font_osb36, font10x20, "u8g_font_osb36_", 27, "OldStandard");
  pic_gen_font(u8g_font_osb37, font10x20, "u8g_font_osb37_", 28, "OldStandard");
  pic_gen_font(u8g_font_osb38, font10x20, "u8g_font_osb38_", 29, "OldStandard");
  pic_gen_font(u8g_font_osb39, font10x20, "u8g_font_osb39_", 30, "OldStandard");

  pic_gen_font(u8g_font_osb40, font10x20, "u8g_font_osb40_", 31, "OldStandard");
  pic_gen_font(u8g_font_osb41, font10x20, "u8g_font_osb41_", 32, "OldStandard");
  pic_gen_font(u8g_font_osb42, font10x20, "u8g_font_osb42_", 33, "OldStandard");
  pic_gen_font(u8g_font_osb43, font10x20, "u8g_font_osb43_", 33, "OldStandard");
  pic_gen_font(u8g_font_osb44, font10x20, "u8g_font_osb44_", 35, "OldStandard");
  pic_gen_font(u8g_font_osb45, font10x20, "u8g_font_osb45_", 36, "OldStandard");
  pic_gen_font(u8g_font_osb46, font10x20, "u8g_font_osb46_", 37, "OldStandard");
  pic_gen_font(u8g_font_osb47, font10x20, "u8g_font_osb47_", 38, "OldStandard");
  pic_gen_font(u8g_font_osb48, font10x20, "u8g_font_osb48_", 39, "OldStandard");
  pic_gen_font(u8g_font_osb49, font10x20, "u8g_font_osb49_", 40, "OldStandard");

  pic_gen_font(u8g_font_osb50, font10x20, "u8g_font_osb50_", 41, "OldStandard");
  pic_gen_font(u8g_font_osb51, font10x20, "u8g_font_osb51_", 42, "OldStandard");
  pic_gen_font(u8g_font_osb52, font10x20, "u8g_font_osb52_", 43, "OldStandard");
  pic_gen_font(u8g_font_osb53, font10x20, "u8g_font_osb53_", 43, "OldStandard");
  pic_gen_font(u8g_font_osb54, font10x20, "u8g_font_osb54_", 45, "OldStandard");
  pic_gen_font(u8g_font_osb55, font10x20, "u8g_font_osb55_", 46, "OldStandard");
  pic_gen_font(u8g_font_osb56, font10x20, "u8g_font_osb56_", 47, "OldStandard");
  pic_gen_font(u8g_font_osb57, font10x20, "u8g_font_osb57_", 48, "OldStandard");
  pic_gen_font(u8g_font_osb58, font10x20, "u8g_font_osb58_", 49, "OldStandard");
  pic_gen_font(u8g_font_osb59, font10x20, "u8g_font_osb59_", 50, "OldStandard");
*/

/*
  pic_gen_font(u8g_font_hab10, font10x20, "u8g_font_hab10_", 12, "HanumanB");
  pic_gen_font(u8g_font_hab11, font10x20, "u8g_font_hab11_", 12, "HanumanB");
  pic_gen_font(u8g_font_hab12, font10x20, "u8g_font_hab12_", 12, "HanumanB");
  pic_gen_font(u8g_font_hab13, font10x20, "u8g_font_hab13_", 13, "HanumanB");
  pic_gen_font(u8g_font_hab14, font10x20, "u8g_font_hab14_", 13, "HanumanB");
  pic_gen_font(u8g_font_hab15, font10x20, "u8g_font_hab15_", 14, "HanumanB");
  pic_gen_font(u8g_font_hab16, font10x20, "u8g_font_hab16_", 14, "HanumanB");
  pic_gen_font(u8g_font_hab17, font10x20, "u8g_font_hab17_", 15, "HanumanB");
  pic_gen_font(u8g_font_hab18, font10x20, "u8g_font_hab18_", 15, "HanumanB");
  pic_gen_font(u8g_font_hab19, font10x20, "u8g_font_hab19_", 16, "HanumanB");
  
  pic_gen_font(u8g_font_hab20, font10x20, "u8g_font_hab20_", 16, "HanumanB");
  pic_gen_font(u8g_font_hab21, font10x20, "u8g_font_hab21_", 17, "HanumanB");
  pic_gen_font(u8g_font_hab22, font10x20, "u8g_font_hab22_", 17, "HanumanB");
  pic_gen_font(u8g_font_hab23, font10x20, "u8g_font_hab23_", 18, "HanumanB");
  pic_gen_font(u8g_font_hab24, font10x20, "u8g_font_hab24_", 18, "HanumanB");
  pic_gen_font(u8g_font_hab25, font10x20, "u8g_font_hab25_", 19, "HanumanB");
  pic_gen_font(u8g_font_hab26, font10x20, "u8g_font_hab26_", 19, "HanumanB");
  pic_gen_font(u8g_font_hab27, font10x20, "u8g_font_hab27_", 20, "HanumanB");
  pic_gen_font(u8g_font_hab28, font10x20, "u8g_font_hab28_", 21, "HanumanB");
  pic_gen_font(u8g_font_hab29, font10x20, "u8g_font_hab29_", 21, "HanumanB");
  
  pic_gen_font(u8g_font_hab30, font10x20, "u8g_font_hab30_", 23, "HanumanB");
  pic_gen_font(u8g_font_hab31, font10x20, "u8g_font_hab31_", 24, "HanumanB");
  pic_gen_font(u8g_font_hab32, font10x20, "u8g_font_hab32_", 24, "HanumanB");
  pic_gen_font(u8g_font_hab33, font10x20, "u8g_font_hab33_", 25, "HanumanB");
  pic_gen_font(u8g_font_hab34, font10x20, "u8g_font_hab34_", 26, "HanumanB");
  pic_gen_font(u8g_font_hab35, font10x20, "u8g_font_hab35_", 26, "HanumanB");
  pic_gen_font(u8g_font_hab36, font10x20, "u8g_font_hab36_", 27, "HanumanB");
  pic_gen_font(u8g_font_hab37, font10x20, "u8g_font_hab37_", 28, "HanumanB");
  pic_gen_font(u8g_font_hab38, font10x20, "u8g_font_hab38_", 29, "HanumanB");
  pic_gen_font(u8g_font_hab39, font10x20, "u8g_font_hab39_", 30, "HanumanB");

  pic_gen_font(u8g_font_hab40, font10x20, "u8g_font_hab40_", 31, "HanumanB");
  pic_gen_font(u8g_font_hab41, font10x20, "u8g_font_hab41_", 32, "HanumanB");
  pic_gen_font(u8g_font_hab42, font10x20, "u8g_font_hab42_", 33, "HanumanB");
  pic_gen_font(u8g_font_hab43, font10x20, "u8g_font_hab43_", 33, "HanumanB");
  pic_gen_font(u8g_font_hab44, font10x20, "u8g_font_hab44_", 35, "HanumanB");
  pic_gen_font(u8g_font_hab45, font10x20, "u8g_font_hab45_", 36, "HanumanB");
  pic_gen_font(u8g_font_hab46, font10x20, "u8g_font_hab46_", 37, "HanumanB");
  pic_gen_font(u8g_font_hab47, font10x20, "u8g_font_hab47_", 38, "HanumanB");
  pic_gen_font(u8g_font_hab48, font10x20, "u8g_font_hab48_", 39, "HanumanB");
  pic_gen_font(u8g_font_hab49, font10x20, "u8g_font_hab49_", 40, "HanumanB");

  pic_gen_font(u8g_font_hab50, font10x20, "u8g_font_hab50_", 41, "HanumanB");
  pic_gen_font(u8g_font_hab51, font10x20, "u8g_font_hab51_", 42, "HanumanB");
  pic_gen_font(u8g_font_hab52, font10x20, "u8g_font_hab52_", 43, "HanumanB");
  pic_gen_font(u8g_font_hab53, font10x20, "u8g_font_hab53_", 43, "HanumanB");
  pic_gen_font(u8g_font_hab54, font10x20, "u8g_font_hab54_", 45, "HanumanB");
  pic_gen_font(u8g_font_hab55, font10x20, "u8g_font_hab55_", 46, "HanumanB");
  pic_gen_font(u8g_font_hab56, font10x20, "u8g_font_hab56_", 47, "HanumanB");
  pic_gen_font(u8g_font_hab57, font10x20, "u8g_font_hab57_", 48, "HanumanB");
  pic_gen_font(u8g_font_hab58, font10x20, "u8g_font_hab58_", 49, "HanumanB");
  pic_gen_font(u8g_font_hab59, font10x20, "u8g_font_hab59_", 50, "HanumanB");
*/

/*
  pic_gen_font(u8g_font_gbr10, font10x20, "u8g_font_gbr10_", 12, "Gentium");
  pic_gen_font(u8g_font_gbr11, font10x20, "u8g_font_gbr11_", 12, "Gentium");
  pic_gen_font(u8g_font_gbr12, font10x20, "u8g_font_gbr12_", 12, "Gentium");
  pic_gen_font(u8g_font_gbr13, font10x20, "u8g_font_gbr13_", 13, "Gentium");
  pic_gen_font(u8g_font_gbr14, font10x20, "u8g_font_gbr14_", 13, "Gentium");
  pic_gen_font(u8g_font_gbr15, font10x20, "u8g_font_gbr15_", 14, "Gentium");
  pic_gen_font(u8g_font_gbr16, font10x20, "u8g_font_gbr16_", 14, "Gentium");
  pic_gen_font(u8g_font_gbr17, font10x20, "u8g_font_gbr17_", 15, "Gentium");
  pic_gen_font(u8g_font_gbr18, font10x20, "u8g_font_gbr18_", 15, "Gentium");
  pic_gen_font(u8g_font_gbr19, font10x20, "u8g_font_gbr19_", 16, "Gentium");
  
  pic_gen_font(u8g_font_gbr20, font10x20, "u8g_font_gbr20_", 16, "Gentium");
  pic_gen_font(u8g_font_gbr21, font10x20, "u8g_font_gbr21_", 17, "Gentium");
  pic_gen_font(u8g_font_gbr22, font10x20, "u8g_font_gbr22_", 17, "Gentium");
  pic_gen_font(u8g_font_gbr23, font10x20, "u8g_font_gbr23_", 18, "Gentium");
  pic_gen_font(u8g_font_gbr24, font10x20, "u8g_font_gbr24_", 18, "Gentium");
  pic_gen_font(u8g_font_gbr25, font10x20, "u8g_font_gbr25_", 19, "Gentium");
  pic_gen_font(u8g_font_gbr26, font10x20, "u8g_font_gbr26_", 19, "Gentium");
  pic_gen_font(u8g_font_gbr27, font10x20, "u8g_font_gbr27_", 20, "Gentium");
  pic_gen_font(u8g_font_gbr28, font10x20, "u8g_font_gbr28_", 21, "Gentium");
  pic_gen_font(u8g_font_gbr29, font10x20, "u8g_font_gbr29_", 21, "Gentium");
  
  pic_gen_font(u8g_font_gbr30, font10x20, "u8g_font_gbr30_", 23, "Gentium");
  pic_gen_font(u8g_font_gbr31, font10x20, "u8g_font_gbr31_", 24, "Gentium");
  pic_gen_font(u8g_font_gbr32, font10x20, "u8g_font_gbr32_", 24, "Gentium");
  pic_gen_font(u8g_font_gbr33, font10x20, "u8g_font_gbr33_", 25, "Gentium");
  pic_gen_font(u8g_font_gbr34, font10x20, "u8g_font_gbr34_", 26, "Gentium");
  pic_gen_font(u8g_font_gbr35, font10x20, "u8g_font_gbr35_", 26, "Gentium");
  pic_gen_font(u8g_font_gbr36, font10x20, "u8g_font_gbr36_", 27, "Gentium");
  pic_gen_font(u8g_font_gbr37, font10x20, "u8g_font_gbr37_", 28, "Gentium");
  pic_gen_font(u8g_font_gbr38, font10x20, "u8g_font_gbr38_", 29, "Gentium");
  pic_gen_font(u8g_font_gbr39, font10x20, "u8g_font_gbr39_", 30, "Gentium");

  pic_gen_font(u8g_font_gbr40, font10x20, "u8g_font_gbr40_", 31, "Gentium");
  pic_gen_font(u8g_font_gbr41, font10x20, "u8g_font_gbr41_", 32, "Gentium");
  pic_gen_font(u8g_font_gbr42, font10x20, "u8g_font_gbr42_", 33, "Gentium");
  pic_gen_font(u8g_font_gbr43, font10x20, "u8g_font_gbr43_", 33, "Gentium");
  pic_gen_font(u8g_font_gbr44, font10x20, "u8g_font_gbr44_", 35, "Gentium");
  pic_gen_font(u8g_font_gbr45, font10x20, "u8g_font_gbr45_", 36, "Gentium");
  pic_gen_font(u8g_font_gbr46, font10x20, "u8g_font_gbr46_", 37, "Gentium");
  pic_gen_font(u8g_font_gbr47, font10x20, "u8g_font_gbr47_", 38, "Gentium");
  pic_gen_font(u8g_font_gbr48, font10x20, "u8g_font_gbr48_", 39, "Gentium");
  pic_gen_font(u8g_font_gbr49, font10x20, "u8g_font_gbr49_", 40, "Gentium");

  pic_gen_font(u8g_font_gbr50, font10x20, "u8g_font_gbr50_", 41, "Gentium");
  pic_gen_font(u8g_font_gbr51, font10x20, "u8g_font_gbr51_", 42, "Gentium");
  pic_gen_font(u8g_font_gbr52, font10x20, "u8g_font_gbr52_", 43, "Gentium");
  pic_gen_font(u8g_font_gbr53, font10x20, "u8g_font_gbr53_", 43, "Gentium");
  pic_gen_font(u8g_font_gbr54, font10x20, "u8g_font_gbr54_", 45, "Gentium");
  pic_gen_font(u8g_font_gbr55, font10x20, "u8g_font_gbr55_", 46, "Gentium");
  pic_gen_font(u8g_font_gbr56, font10x20, "u8g_font_gbr56_", 47, "Gentium");
  pic_gen_font(u8g_font_gbr57, font10x20, "u8g_font_gbr57_", 48, "Gentium");
  pic_gen_font(u8g_font_gbr58, font10x20, "u8g_font_gbr58_", 49, "Gentium");
  pic_gen_font(u8g_font_gbr59, font10x20, "u8g_font_gbr59_", 50, "Gentium");

  pic_gen_font(u8g_font_gbb10, font10x20, "u8g_font_gbb10_", 12, "Gentium");
  pic_gen_font(u8g_font_gbb11, font10x20, "u8g_font_gbb11_", 12, "Gentium");
  pic_gen_font(u8g_font_gbb12, font10x20, "u8g_font_gbb12_", 12, "Gentium");
  pic_gen_font(u8g_font_gbb13, font10x20, "u8g_font_gbb13_", 13, "Gentium");
  pic_gen_font(u8g_font_gbb14, font10x20, "u8g_font_gbb14_", 13, "Gentium");
  pic_gen_font(u8g_font_gbb15, font10x20, "u8g_font_gbb15_", 14, "Gentium");
  pic_gen_font(u8g_font_gbb16, font10x20, "u8g_font_gbb16_", 14, "Gentium");
  pic_gen_font(u8g_font_gbb17, font10x20, "u8g_font_gbb17_", 15, "Gentium");
  pic_gen_font(u8g_font_gbb18, font10x20, "u8g_font_gbb18_", 15, "Gentium");
  pic_gen_font(u8g_font_gbb19, font10x20, "u8g_font_gbb19_", 16, "Gentium");
  
  pic_gen_font(u8g_font_gbb20, font10x20, "u8g_font_gbb20_", 16, "Gentium");
  pic_gen_font(u8g_font_gbb21, font10x20, "u8g_font_gbb21_", 17, "Gentium");
  pic_gen_font(u8g_font_gbb22, font10x20, "u8g_font_gbb22_", 17, "Gentium");
  pic_gen_font(u8g_font_gbb23, font10x20, "u8g_font_gbb23_", 18, "Gentium");
  pic_gen_font(u8g_font_gbb24, font10x20, "u8g_font_gbb24_", 18, "Gentium");
  pic_gen_font(u8g_font_gbb25, font10x20, "u8g_font_gbb25_", 19, "Gentium");
  pic_gen_font(u8g_font_gbb26, font10x20, "u8g_font_gbb26_", 19, "Gentium");
  pic_gen_font(u8g_font_gbb27, font10x20, "u8g_font_gbb27_", 20, "Gentium");
  pic_gen_font(u8g_font_gbb28, font10x20, "u8g_font_gbb28_", 21, "Gentium");
  pic_gen_font(u8g_font_gbb29, font10x20, "u8g_font_gbb29_", 21, "Gentium");
  
  pic_gen_font(u8g_font_gbb30, font10x20, "u8g_font_gbb30_", 23, "Gentium");
  pic_gen_font(u8g_font_gbb31, font10x20, "u8g_font_gbb31_", 24, "Gentium");
  pic_gen_font(u8g_font_gbb32, font10x20, "u8g_font_gbb32_", 24, "Gentium");
  pic_gen_font(u8g_font_gbb33, font10x20, "u8g_font_gbb33_", 25, "Gentium");
  pic_gen_font(u8g_font_gbb34, font10x20, "u8g_font_gbb34_", 26, "Gentium");
  pic_gen_font(u8g_font_gbb35, font10x20, "u8g_font_gbb35_", 26, "Gentium");
  pic_gen_font(u8g_font_gbb36, font10x20, "u8g_font_gbb36_", 27, "Gentium");
  pic_gen_font(u8g_font_gbb37, font10x20, "u8g_font_gbb37_", 28, "Gentium");
  pic_gen_font(u8g_font_gbb38, font10x20, "u8g_font_gbb38_", 29, "Gentium");
  pic_gen_font(u8g_font_gbb39, font10x20, "u8g_font_gbb39_", 30, "Gentium");

  pic_gen_font(u8g_font_gbb40, font10x20, "u8g_font_gbb40_", 31, "Gentium");
  pic_gen_font(u8g_font_gbb41, font10x20, "u8g_font_gbb41_", 32, "Gentium");
  pic_gen_font(u8g_font_gbb42, font10x20, "u8g_font_gbb42_", 33, "Gentium");
  pic_gen_font(u8g_font_gbb43, font10x20, "u8g_font_gbb43_", 33, "Gentium");
  pic_gen_font(u8g_font_gbb44, font10x20, "u8g_font_gbb44_", 35, "Gentium");
  pic_gen_font(u8g_font_gbb45, font10x20, "u8g_font_gbb45_", 36, "Gentium");
  pic_gen_font(u8g_font_gbb46, font10x20, "u8g_font_gbb46_", 37, "Gentium");
  pic_gen_font(u8g_font_gbb47, font10x20, "u8g_font_gbb47_", 38, "Gentium");
  pic_gen_font(u8g_font_gbb48, font10x20, "u8g_font_gbb48_", 39, "Gentium");
  pic_gen_font(u8g_font_gbb49, font10x20, "u8g_font_gbb49_", 40, "Gentium");

  pic_gen_font(u8g_font_gbb50, font10x20, "u8g_font_gbb50_", 41, "Gentium");
  pic_gen_font(u8g_font_gbb51, font10x20, "u8g_font_gbb51_", 42, "Gentium");
  pic_gen_font(u8g_font_gbb52, font10x20, "u8g_font_gbb52_", 43, "Gentium");
  pic_gen_font(u8g_font_gbb53, font10x20, "u8g_font_gbb53_", 43, "Gentium");
  pic_gen_font(u8g_font_gbb54, font10x20, "u8g_font_gbb54_", 45, "Gentium");
  pic_gen_font(u8g_font_gbb55, font10x20, "u8g_font_gbb55_", 46, "Gentium");
  pic_gen_font(u8g_font_gbb56, font10x20, "u8g_font_gbb56_", 47, "Gentium");
  pic_gen_font(u8g_font_gbb57, font10x20, "u8g_font_gbb57_", 48, "Gentium");
  pic_gen_font(u8g_font_gbb58, font10x20, "u8g_font_gbb58_", 49, "Gentium");
  pic_gen_font(u8g_font_gbb59, font10x20, "u8g_font_gbb59_", 50, "Gentium");
*/

#endif

#ifdef OLI


  pic_gen_font(u8g_font_10x20, "u8g_font_10x20", 14, "X11 Display Font");
  pic_gen_font(u8g_font_10x20r, "u8g_font_10x20r", 14, "X11 Display Font");
  pic_gen_font(u8g_font_10x20_67_75, "u8g_font_10x20_67_75", 14, "X11 Display Font");
  pic_gen_font(u8g_font_10x20_75r, "u8g_font_10x20_75r", 14, "X11 Display Font");
  pic_gen_font(u8g_font_10x20_78_79, "u8g_font_10x20_78_79", 14, "X11 Display Font");
  
  pic_gen_font(u8g_font_4x6, "u8g_font_4x6", 10, "X11 Display Font");
  pic_gen_font(u8g_font_4x6r, "u8g_font_4x6r", 10, "X11 Display Font");
  //pic_gen_font(u8g_font_4x6n, "u8g_font_4x6n", 10, "X11 Display Font");
  pic_gen_font(u8g_font_micro, "u8g_font_micro", 10, "X11 Display Font");
  //pic_gen_font(u8g_font_micror, "u8g_font_micror", 10, "X11 Display Font");
  pic_gen_font(u8g_font_5x7, "u8g_font_5x7", 10, "X11 Display Font");
  pic_gen_font(u8g_font_5x7r, "u8g_font_5x7r", 10, "X11 Display Font");
  pic_gen_font(u8g_font_5x8, "u8g_font_5x8", 10, "X11 Display Font");
  pic_gen_font(u8g_font_5x8r, "u8g_font_5x8r", 10, "X11 Display Font");

  pic_gen_font(u8g_font_6x10, "u8g_font_6x10", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x10r, "u8g_font_6x10r", 10, "X11 Display Font");


  pic_gen_font(u8g_font_6x12, "u8g_font_6x12", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x12r, "u8g_font_6x12r", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x12_67_75, "u8g_font_6x12_67_75", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x12_75r, "u8g_font_6x12_75r", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x12_78_79, "u8g_font_6x12_78_79", 10, "X11 Display Font");

  pic_gen_font(u8g_font_6x13, "u8g_font_6x13", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x13r, "u8g_font_6x13r", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x13B, "u8g_font_6x13B", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x13Br, "u8g_font_6x13Br", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x13O, "u8g_font_6x13O", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x13Or, "u8g_font_6x13Or", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x13_67_75, "u8g_font_6x13_67_75", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x13_75r, "u8g_font_6x13_75r", 10, "X11 Display Font");
  pic_gen_font(u8g_font_6x13_78_79, "u8g_font_6x13_78_79", 10, "X11 Display Font");

  pic_gen_font(u8g_font_7x13, "u8g_font_7x13", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x13r, "u8g_font_7x13r", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x13B, "u8g_font_7x13B", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x13Br, "u8g_font_7x13Br", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x13O, "u8g_font_7x13O", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x13Or, "u8g_font_7x13Or", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x13_67_75, "u8g_font_7x13_67_75", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x13_75r, "u8g_font_7x13_75r", 14, "X11 Display Font");
  //pic_gen_font(u8g_font_7x13_78_79, "u8g_font_7x13_78_79", 14, "X11 Display Font");

  pic_gen_font(u8g_font_7x14, "u8g_font_7x14", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x14r, "u8g_font_7x14r", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x14B, "u8g_font_7x14B", 14, "X11 Display Font");
  pic_gen_font(u8g_font_7x14Br, "u8g_font_7x14Br", 14, "X11 Display Font");

  pic_gen_font(u8g_font_8x13, "u8g_font_8x13", 14, "X11 Display Font");
  pic_gen_font(u8g_font_8x13r, "u8g_font_8x13r", 14, "X11 Display Font");
  pic_gen_font(u8g_font_8x13B, "u8g_font_8x13B", 14, "X11 Display Font");
  pic_gen_font(u8g_font_8x13Br, "u8g_font_8x13Br", 14, "X11 Display Font");
  pic_gen_font(u8g_font_8x13O, "u8g_font_8x13O", 14, "X11 Display Font");
  pic_gen_font(u8g_font_8x13Or, "u8g_font_8x13Or", 14, "X11 Display Font");
  pic_gen_font(u8g_font_8x13_67_75, "u8g_font_8x13_67_75", 14, "X11 Display Font");
  pic_gen_font(u8g_font_8x13_75r, "u8g_font_8x13_75r", 14, "X11 Display Font");

  pic_gen_font(u8g_font_9x15, "u8g_font_9x15", 14, "X11 Display Font");
  pic_gen_font(u8g_font_9x15r, "u8g_font_9x15r", 14, "X11 Display Font");
  pic_gen_font(u8g_font_9x15B, "u8g_font_9x15B", 14, "X11 Display Font");
  pic_gen_font(u8g_font_9x15Br, "u8g_font_9x15Br", 14, "X11 Display Font");
  pic_gen_font(u8g_font_9x15_67_75, "u8g_font_9x15_67_75", 10, "X11 Display Font");
  pic_gen_font(u8g_font_9x15_75r, "u8g_font_9x15_75r", 10, "X11 Display Font");
  pic_gen_font(u8g_font_9x15_78_79, "u8g_font_9x15_78_79", 10, "X11 Display Font");

  pic_gen_font(u8g_font_9x18, "u8g_font_9x18", 14, "X11 Display Font");
  pic_gen_font(u8g_font_9x18B, "u8g_font_9x18B", 14, "X11 Display Font");
  pic_gen_font(u8g_font_9x18r, "u8g_font_9x18r", 14, "X11 Display Font");
  pic_gen_font(u8g_font_9x18Br, "u8g_font_9x18Br", 14, "X11 Display Font");
  pic_gen_font(u8g_font_9x18_67_75, "u8g_font_9x18_67_75", 10, "X11 Display Font");
  pic_gen_font(u8g_font_9x18_75r, "u8g_font_9x18_75r", 10, "X11 Display Font");
  pic_gen_font(u8g_font_9x18_78_79, "u8g_font_9x18_78_79", 10, "X11 Display Font");

  pic_gen_font(u8g_font_cu12, "u8g_font_cu12", 16, "");
  pic_gen_font(u8g_font_cu12_67_75, "u8g_font_cu12_67_75", 16, "");
  pic_gen_font(u8g_font_cu12_75r, "u8g_font_cu12_75r", 16, "");
  //pic_gen_font(u8g_font_cu12_78_79, "u8g_font_cu12_78_79", 16, "");

  pic_gen_font(u8g_font_cursor, "u8g_font_cursor", 20, "X11 Cursor Font");
  pic_gen_font(u8g_font_cursorr, "u8g_font_cursorr", 20, "X11 Cursor Font");

  pic_gen_font(u8g_font_fub11, "u8g_font_fub11", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub11n, "u8g_font_fub11n", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub11r, "u8g_font_fub11r", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub14, "u8g_font_fub14", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub14n, "u8g_font_fub14n", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub14r, "u8g_font_fub14r", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub17, "u8g_font_fub17", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub17n, "u8g_font_fub17n", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub17r, "u8g_font_fub17r", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub20, "u8g_font_fub20", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub20n, "u8g_font_fub20n", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub20r, "u8g_font_fub20r", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub25, "u8g_font_fub25", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub25n, "u8g_font_fub25n", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub25r, "u8g_font_fub25r", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub30, "u8g_font_fub30", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub30n, "u8g_font_fub30n", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub30r, "u8g_font_fub30r", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub35n, "u8g_font_fub35n", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub42n, "u8g_font_fub42n", 32, "FreeUniversal-Bold");
  pic_gen_font(u8g_font_fub49n, "u8g_font_fub49n", 36, "FreeUniversal-Bold");

  pic_gen_font(u8g_font_fur11, "u8g_font_fur11", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur14, "u8g_font_fur14", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur17, "u8g_font_fur17", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur20, "u8g_font_fur20", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur25, "u8g_font_fur25", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur30, "u8g_font_fur30", 32, "FreeUniversal-Regular");
  
  pic_gen_font(u8g_font_fur11r, "u8g_font_fur11r", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur14r, "u8g_font_fur14r", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur17r, "u8g_font_fur17r", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur20r, "u8g_font_fur20r", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur25r, "u8g_font_fur25r", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur30r, "u8g_font_fur30r", 32, "FreeUniversal-Regular");
  
  pic_gen_font(u8g_font_fur11n, "u8g_font_fur11n", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur14n, "u8g_font_fur14n", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur17n, "u8g_font_fur17n", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur20n, "u8g_font_fur20n", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur25n, "u8g_font_fur25n", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur30n, "u8g_font_fur30n", 32, "FreeUniversal-Regular");
  
  pic_gen_font(u8g_font_fur35n, "u8g_font_fur35n", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur42n, "u8g_font_fur42n", 32, "FreeUniversal-Regular");
  pic_gen_font(u8g_font_fur49n, "u8g_font_fur49n", 36, "FreeUniversal-Regular");

  pic_gen_font(u8g_font_gdb11, "u8g_font_gdb11", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb12, "u8g_font_gdb12", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb14, "u8g_font_gdb14", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb17, "u8g_font_gdb17", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb20, "u8g_font_gdb20", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb25, "u8g_font_gdb25", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb30, "u8g_font_gdb30", 32, "Gentium Bold");

  pic_gen_font(u8g_font_gdb11r, "u8g_font_gdb11r", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb12r, "u8g_font_gdb12r", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb14r, "u8g_font_gdb14r", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb17r, "u8g_font_gdb17r", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb20r, "u8g_font_gdb20r", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb25r, "u8g_font_gdb25r", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb30r, "u8g_font_gdb30r", 32, "Gentium Bold");

  pic_gen_font(u8g_font_gdb11n, "u8g_font_gdb11n", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb12n, "u8g_font_gdb12n", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb14n, "u8g_font_gdb14n", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb17n, "u8g_font_gdb17n", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb20n, "u8g_font_gdb20n", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb25n, "u8g_font_gdb25n", 32, "Gentium Bold");
  pic_gen_font(u8g_font_gdb30n, "u8g_font_gdb30n", 32, "Gentium Bold");

  pic_gen_font(u8g_font_gdr11, "u8g_font_gdr11", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr12, "u8g_font_gdr12", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr14, "u8g_font_gdr14", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr17, "u8g_font_gdr17", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr20, "u8g_font_gdr20", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr25, "u8g_font_gdr25", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr30, "u8g_font_gdr30", 32, "Gentium Regular");

  pic_gen_font(u8g_font_gdr11r, "u8g_font_gdr11r", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr12r, "u8g_font_gdr12r", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr14r, "u8g_font_gdr14r", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr17r, "u8g_font_gdr17r", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr20r, "u8g_font_gdr20r", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr25r, "u8g_font_gdr25r", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr30r, "u8g_font_gdr30r", 32, "Gentium Regular");

  pic_gen_font(u8g_font_gdr11n, "u8g_font_gdr11n", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr12n, "u8g_font_gdr12n", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr14n, "u8g_font_gdr14n", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr17n, "u8g_font_gdr17n", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr20n, "u8g_font_gdr20n", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr25n, "u8g_font_gdr25n", 32, "Gentium Regular");
  pic_gen_font(u8g_font_gdr30n, "u8g_font_gdr30n", 32, "Gentium Regular");

  pic_gen_font(u8g_font_osb18, "u8g_font_osb18", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb21, "u8g_font_osb21", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb26, "u8g_font_osb26", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb29, "u8g_font_osb29", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb35, "u8g_font_osb35", 32, "OldStandard-Bold");

  pic_gen_font(u8g_font_osb18r, "u8g_font_osb18r", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb21r, "u8g_font_osb21r", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb26r, "u8g_font_osb26r", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb29r, "u8g_font_osb29r", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb35r, "u8g_font_osb35r", 32, "OldStandard-Bold");

  pic_gen_font(u8g_font_osb18n, "u8g_font_osb18n", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb21n, "u8g_font_osb21n", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb26n, "u8g_font_osb26n", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb29n, "u8g_font_osb29n", 32, "OldStandard-Bold");
  pic_gen_font(u8g_font_osb35n, "u8g_font_osb35n", 32, "OldStandard-Bold");

  pic_gen_font(u8g_font_osr18, "u8g_font_osr18", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr21, "u8g_font_osr21", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr26, "u8g_font_osr26", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr29, "u8g_font_osr29", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr35, "u8g_font_osr35", 32, "OldStandard-Regular");

  pic_gen_font(u8g_font_osr18r, "u8g_font_osr18r", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr21r, "u8g_font_osr21r", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr26r, "u8g_font_osr26r", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr29r, "u8g_font_osr29r", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr35r, "u8g_font_osr35r", 32, "OldStandard-Regular");

  pic_gen_font(u8g_font_osr18n, "u8g_font_osr18n", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr21n, "u8g_font_osr21n", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr26n, "u8g_font_osr26n", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr29n, "u8g_font_osr29n", 32, "OldStandard-Regular");
  pic_gen_font(u8g_font_osr35n, "u8g_font_osr35n", 32, "OldStandard-Regular");

  pic_gen_font(u8g_font_unifont_72_73, "u8g_font_unifont_72_73", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_67_75, "u8g_font_unifont_67_75", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_75r, "u8g_font_unifont_75r", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_76, "u8g_font_unifont_76", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_77, "u8g_font_unifont_77", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_78_79, "u8g_font_unifont_78_79", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_86, "u8g_font_unifont_86", 17, "Unifont");
  pic_gen_font(u8g_font_unifont, "u8g_font_unifont", 17, "Unifont");
  pic_gen_font(u8g_font_unifontr, "u8g_font_unifontr", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_0_8, "u8g_font_unifont_0_8", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_2_3, "u8g_font_unifont_2_3", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_4_5, "u8g_font_unifont_4_5", 17, "Unifont");
  pic_gen_font(u8g_font_unifont_8_9, "u8g_font_unifont_8_9", 17, "Unifont");
 
  pic_gen_font(u8g_font_04b_03b, "u8g_font_04b_03b", 8, "04b_03b");
  pic_gen_font(u8g_font_04b_03br, "u8g_font_04b_03br", 8, "04b_03b");
  pic_gen_font(u8g_font_04b_03bn, "u8g_font_04b_03bn", 8, "04b_03b");

  pic_gen_font(u8g_font_04b_03, "u8g_font_04b_03", 8, "04b_03");
  pic_gen_font(u8g_font_04b_03r, "u8g_font_04b_03r", 8, "04b_03");
  pic_gen_font(u8g_font_04b_03n, "u8g_font_04b_03n", 8, "04b_03");

  pic_gen_font(u8g_font_04b_24, "u8g_font_04b_24", 8, "04b_24");
  pic_gen_font(u8g_font_04b_24r, "u8g_font_04b_24r", 8, "04b_24");
  pic_gen_font(u8g_font_04b_24n, "u8g_font_04b_24n", 8, "04b_24");

  pic_gen_font(u8g_font_orgv01, "u8g_font_orgv01", 8, "orgdot: org_v01");
  pic_gen_font(u8g_font_orgv01r, "u8g_font_orgv01r", 8, "orgdot: org_v01");
  pic_gen_font(u8g_font_orgv01n, "u8g_font_orgv01n", 8, "orgdot: org_v01");

  pic_gen_font(u8g_font_fixed_v0, "u8g_font_fixed_v0", 8, "orgdot: fixed_v0");
  pic_gen_font(u8g_font_fixed_v0r, "u8g_font_fixed_v0r", 8, "orgdot: fixed_v0");
  pic_gen_font(u8g_font_fixed_v0n, "u8g_font_fixed_v0n", 8, "orgdot: fixed_v0");

  pic_gen_font(u8g_font_tpssb, "u8g_font_tpssb", 12, "orgdot: Teacher's Pet Sans Serif Bold");
  pic_gen_font(u8g_font_tpssbr, "u8g_font_tpssbr", 12, "orgdot: Teacher's Pet Sans Serif Bold");
  pic_gen_font(u8g_font_tpssbn, "u8g_font_tpssbn", 12, "orgdot: Teacher's Pet Sans Serif Bold");

  pic_gen_font(u8g_font_tpss, "u8g_font_tpss", 12, "orgdot: Teacher's Pet Sans Serif");
  pic_gen_font(u8g_font_tpssr, "u8g_font_tpssr", 12, "orgdot: Teacher's Pet Sans Serif");
  pic_gen_font(u8g_font_tpssn, "u8g_font_tpssn", 12, "orgdot: Teacher's Pet Sans Serif");

  pic_gen_font(u8g_font_m2icon_5, "u8g_font_m2icon_5", 12, "u8glib m2icon");
  pic_gen_font(u8g_font_m2icon_7, "u8g_font_m2icon_7", 12, "u8glib m2icon");
  pic_gen_font(u8g_font_m2icon_9, "u8g_font_m2icon_9", 12, "u8glib m2icon");
  

  pic_gen_font(u8g_font_courB08, "u8g_font_courB08", 12, "courB08");
  pic_gen_font(u8g_font_courB08r, "u8g_font_courB08r", 12, "courB08r");
  pic_gen_font(u8g_font_courB10, "u8g_font_courB10", 16, "courB10");
  pic_gen_font(u8g_font_courB10r, "u8g_font_courB10r", 16, "courB10r");
  pic_gen_font(u8g_font_courB12, "u8g_font_courB12", 18, "courB12");
  pic_gen_font(u8g_font_courB12r, "u8g_font_courB12r", 18, "courB12r");
  pic_gen_font(u8g_font_courB14, "u8g_font_courB14", 22, "courB14");
  pic_gen_font(u8g_font_courB14r, "u8g_font_courB14r", 22, "courB14r");
  pic_gen_font(u8g_font_courB18, "u8g_font_courB18", 26, "courB18");
  pic_gen_font(u8g_font_courB18r, "u8g_font_courB18r", 26, "courB18r");
  pic_gen_font(u8g_font_courB24, "u8g_font_courB24", 32, "courB24");
  pic_gen_font(u8g_font_courB24r, "u8g_font_courB24r", 32, "courB24r");
  pic_gen_font(u8g_font_courB24n, "u8g_font_courB24n", 32, "courB24n");

  pic_gen_font(u8g_font_courR08, "u8g_font_courR08", 12, "courR08");
  pic_gen_font(u8g_font_courR08r, "u8g_font_courR08r", 12, "courR08r");
  pic_gen_font(u8g_font_courR10, "u8g_font_courR10", 16, "courR10");
  pic_gen_font(u8g_font_courR10r, "u8g_font_courR10r", 16, "courR10r");
  pic_gen_font(u8g_font_courR12, "u8g_font_courR12", 18, "courR12");
  pic_gen_font(u8g_font_courR12r, "u8g_font_courR12r", 18, "courR12r");
  pic_gen_font(u8g_font_courR14, "u8g_font_courR14", 22, "courR14");
  pic_gen_font(u8g_font_courR14r, "u8g_font_courR14r", 22, "courR14r");
  pic_gen_font(u8g_font_courR18, "u8g_font_courR18", 26, "courR18");
  pic_gen_font(u8g_font_courR18r, "u8g_font_courR18r", 26, "courR18r");
  pic_gen_font(u8g_font_courR24, "u8g_font_courR24", 32, "courR24");
  pic_gen_font(u8g_font_courR24r, "u8g_font_courR24r", 32, "courR24r");
  pic_gen_font(u8g_font_courR24n, "u8g_font_courR24n", 32, "courR24n");

  pic_gen_font(u8g_font_helvB08, "u8g_font_helvB08", 12, "helvB08");
  pic_gen_font(u8g_font_helvB08r, "u8g_font_helvB08r", 12, "helvB08r");
  pic_gen_font(u8g_font_helvB10, "u8g_font_helvB10", 16, "helvB10");
  pic_gen_font(u8g_font_helvB10r, "u8g_font_helvB10r", 16, "helvB10r");
  pic_gen_font(u8g_font_helvB12, "u8g_font_helvB12", 18, "helvB12");
  pic_gen_font(u8g_font_helvB12r, "u8g_font_helvB12r", 18, "helvB12r");
  pic_gen_font(u8g_font_helvB14, "u8g_font_helvB14", 22, "helvB14");
  pic_gen_font(u8g_font_helvB14r, "u8g_font_helvB14r", 22, "helvB14r");
  pic_gen_font(u8g_font_helvB18, "u8g_font_helvB18", 26, "helvB18");
  pic_gen_font(u8g_font_helvB18r, "u8g_font_helvB18r", 26, "helvB18r");
  pic_gen_font(u8g_font_helvB24, "u8g_font_helvB24", 32, "helvB24");
  pic_gen_font(u8g_font_helvB24r, "u8g_font_helvB24r", 32, "helvB24r");
  pic_gen_font(u8g_font_helvB24n, "u8g_font_helvB24n", 32, "helvB24n");

  pic_gen_font(u8g_font_helvR08, "u8g_font_helvR08", 12, "helvR08");
  pic_gen_font(u8g_font_helvR08r, "u8g_font_helvR08r", 12, "helvR08r");
  pic_gen_font(u8g_font_helvR10, "u8g_font_helvR10", 16, "helvR10");
  pic_gen_font(u8g_font_helvR10r, "u8g_font_helvR10r", 16, "helvR10r");
  pic_gen_font(u8g_font_helvR12, "u8g_font_helvR12", 18, "helvR12");
  pic_gen_font(u8g_font_helvR12r, "u8g_font_helvR12r", 18, "helvR12r");
  pic_gen_font(u8g_font_helvR14, "u8g_font_helvR14", 22, "helvR14");
  pic_gen_font(u8g_font_helvR14r, "u8g_font_helvR14r", 22, "helvR14r");
  pic_gen_font(u8g_font_helvR18, "u8g_font_helvR18", 26, "helvR18");
  pic_gen_font(u8g_font_helvR18r, "u8g_font_helvR18r", 26, "helvR18r");
  pic_gen_font(u8g_font_helvR24, "u8g_font_helvR24", 32, "helvR24");
  pic_gen_font(u8g_font_helvR24r, "u8g_font_helvR24r", 32, "helvR24r");
  pic_gen_font(u8g_font_helvR24n, "u8g_font_helvR24n", 32, "helvR24n");

  pic_gen_font(u8g_font_ncenB08, "u8g_font_ncenB08", 12, "ncenB08");
  pic_gen_font(u8g_font_ncenB08r, "u8g_font_ncenB08r", 12, "ncenB08r");
  pic_gen_font(u8g_font_ncenB10, "u8g_font_ncenB10", 16, "ncenB10");
  pic_gen_font(u8g_font_ncenB10r, "u8g_font_ncenB10r", 16, "ncenB10r");
  pic_gen_font(u8g_font_ncenB12, "u8g_font_ncenB12", 18, "ncenB12");
  pic_gen_font(u8g_font_ncenB12r, "u8g_font_ncenB12r", 18, "ncenB12r");
  pic_gen_font(u8g_font_ncenB14, "u8g_font_ncenB14", 22, "ncenB14");
  pic_gen_font(u8g_font_ncenB14r, "u8g_font_ncenB14r", 22, "ncenB14r");
  pic_gen_font(u8g_font_ncenB18, "u8g_font_ncenB18", 26, "ncenB18");
  pic_gen_font(u8g_font_ncenB18r, "u8g_font_ncenB18r", 26, "ncenB18r");
  pic_gen_font(u8g_font_ncenB24, "u8g_font_ncenB24", 32, "ncenB24");
  pic_gen_font(u8g_font_ncenB24r, "u8g_font_ncenB24r", 32, "ncenB24r");
  pic_gen_font(u8g_font_ncenB24n, "u8g_font_ncenB24n", 32, "ncenB24n");

  pic_gen_font(u8g_font_ncenR08, "u8g_font_ncenR08", 12, "ncenR08");
  pic_gen_font(u8g_font_ncenR08r, "u8g_font_ncenR08r", 12, "ncenR08r");
  pic_gen_font(u8g_font_ncenR10, "u8g_font_ncenR10", 16, "ncenR10");
  pic_gen_font(u8g_font_ncenR10r, "u8g_font_ncenR10r", 16, "ncenR10r");
  pic_gen_font(u8g_font_ncenR12, "u8g_font_ncenR12", 18, "ncenR12");
  pic_gen_font(u8g_font_ncenR12r, "u8g_font_ncenR12r", 18, "ncenR12r");
  pic_gen_font(u8g_font_ncenR14, "u8g_font_ncenR14", 22, "ncenR14");
  pic_gen_font(u8g_font_ncenR14r, "u8g_font_ncenR14r", 22, "ncenR14r");
  pic_gen_font(u8g_font_ncenR18, "u8g_font_ncenR18", 26, "ncenR18");
  pic_gen_font(u8g_font_ncenR18r, "u8g_font_ncenR18r", 26, "ncenR18r");
  pic_gen_font(u8g_font_ncenR24, "u8g_font_ncenR24", 32, "ncenR24");
  pic_gen_font(u8g_font_ncenR24r, "u8g_font_ncenR24r", 32, "ncenR24r");
  pic_gen_font(u8g_font_ncenR24n, "u8g_font_ncenR24n", 32, "ncenR24n");

  pic_gen_font(u8g_font_timB08, "u8g_font_timB08", 12, "timB08");
  pic_gen_font(u8g_font_timB08r, "u8g_font_timB08r", 12, "timB08r");
  pic_gen_font(u8g_font_timB10, "u8g_font_timB10", 16, "timB10");
  pic_gen_font(u8g_font_timB10r, "u8g_font_timB10r", 16, "timB10r");
  pic_gen_font(u8g_font_timB12, "u8g_font_timB12", 18, "timB12");
  pic_gen_font(u8g_font_timB12r, "u8g_font_timB12r", 18, "timB12r");
  pic_gen_font(u8g_font_timB14, "u8g_font_timB14", 22, "timB14");
  pic_gen_font(u8g_font_timB14r, "u8g_font_timB14r", 22, "timB14r");
  pic_gen_font(u8g_font_timB18, "u8g_font_timB18", 26, "timB18");
  pic_gen_font(u8g_font_timB18r, "u8g_font_timB18r", 26, "timB18r");
  pic_gen_font(u8g_font_timB24, "u8g_font_timB24", 32, "timB24");
  pic_gen_font(u8g_font_timB24r, "u8g_font_timB24r", 32, "timB24r");
  pic_gen_font(u8g_font_timB24n, "u8g_font_timB24n", 32, "timB24n");

  pic_gen_font(u8g_font_timR08, "u8g_font_timR08", 12, "timR08");
  pic_gen_font(u8g_font_timR08r, "u8g_font_timR08r", 12, "timR08r");
  pic_gen_font(u8g_font_timR10, "u8g_font_timR10", 16, "timR10");
  pic_gen_font(u8g_font_timR10r, "u8g_font_timR10r", 16, "timR10r");
  pic_gen_font(u8g_font_timR12, "u8g_font_timR12", 18, "timR12");
  pic_gen_font(u8g_font_timR12r, "u8g_font_timR12r", 18, "timR12r");
  pic_gen_font(u8g_font_timR14, "u8g_font_timR14", 22, "timR14");
  pic_gen_font(u8g_font_timR14r, "u8g_font_timR14r", 22, "timR14r");
  pic_gen_font(u8g_font_timR18, "u8g_font_timR18", 26, "timR18");
  pic_gen_font(u8g_font_timR18r, "u8g_font_timR18r", 26, "timR18r");
  pic_gen_font(u8g_font_timR24, "u8g_font_timR24", 32, "timR24");
  pic_gen_font(u8g_font_timR24r, "u8g_font_timR24r", 32, "timR24r");
  pic_gen_font(u8g_font_timR24n, "u8g_font_timR24n", 32, "timR24n");

  pic_gen_font(u8g_font_symb08, "u8g_font_symb08", 12, "symb08");
  pic_gen_font(u8g_font_symb08r, "u8g_font_symb08r", 12, "symb08r");
  pic_gen_font(u8g_font_symb10, "u8g_font_symb10", 16, "symb10");
  pic_gen_font(u8g_font_symb10r, "u8g_font_symb10r", 16, "symb10r");
  pic_gen_font(u8g_font_symb12, "u8g_font_symb12", 18, "symb12");
  pic_gen_font(u8g_font_symb12r, "u8g_font_symb12r", 18, "symb12r");
  pic_gen_font(u8g_font_symb14, "u8g_font_symb14", 22, "symb14");
  pic_gen_font(u8g_font_symb14r, "u8g_font_symb14r", 22, "symb14r");
  pic_gen_font(u8g_font_symb18, "u8g_font_symb18", 26, "symb18");
  pic_gen_font(u8g_font_symb18r, "u8g_font_symb18r", 26, "symb18r");
  pic_gen_font(u8g_font_symb24, "u8g_font_symb24", 32, "symb24");
  pic_gen_font(u8g_font_symb24r, "u8g_font_symb24r", 32, "symb24r");


  pic_gen_font(u8g_font_freedoomr10r, "u8g_font_freedoomr10r", 12, "freedoomr10r");


  pic_gen_font(u8g_font_p01type, "u8g_font_p01type", 10, "P01type");
  pic_gen_font(u8g_font_p01typer, "u8g_font_p01typer", 10, "P01type");
  pic_gen_font(u8g_font_p01typen, "u8g_font_p01typen", 10, "P01type");

  pic_gen_font(u8g_font_lucasfont_alternate, "u8g_font_lucasfont_alternate", 10, "Lucasfont Alternate");
  pic_gen_font(u8g_font_lucasfont_alternater, "u8g_font_lucasfont_alternater", 10, "Lucasfont Alternate");
  pic_gen_font(u8g_font_lucasfont_alternaten, "u8g_font_lucasfont_alternaten", 10, "Lucasfont Alternate");

//  pic_gen_font(u8g_font_fs_onebrickpixelfont, "u8g_font_fs_onebrickpixelfont", 10, "FS One-Brick-Pixel-Font");
//  pic_gen_font(u8g_font_fs_onebrickpixelfontr, "u8g_font_fs_onebrickpixelfontr", 10, "FS One-Brick-Pixel-Font");
//  pic_gen_font(u8g_font_fs_onebrickpixelfontn, "u8g_font_fs_onebrickpixelfontn", 10, "FS One-Brick-Pixel-Font");

  pic_gen_font(u8g_font_chikita, "u8g_font_chikita", 10, "Chikita");
  pic_gen_font(u8g_font_chikitar, "u8g_font_chikitar", 10, "Chikita");
  pic_gen_font(u8g_font_chikitan, "u8g_font_chikitan", 10, "Chikita");

  pic_gen_font(u8g_font_pixelle_micro, "u8g_font_pixelle_micro", 10, "Pixelle Micro");
  pic_gen_font(u8g_font_pixelle_micror, "u8g_font_pixelle_micror", 10, "Pixelle Micro");
  pic_gen_font(u8g_font_pixelle_micron, "u8g_font_pixelle_micron", 10, "Pixelle Micro");

  pic_gen_font(u8g_font_trixel_square, "u8g_font_trixel_square", 10, "Trixel Square");
  pic_gen_font(u8g_font_trixel_squarer, "u8g_font_trixel_squarer", 10, "Trixel Square");
  pic_gen_font(u8g_font_trixel_squaren, "u8g_font_trixel_squaren", 10, "Trixel Square");

  pic_gen_font(u8g_font_robot_de_niro, "u8g_font_robot_de_niro", 10, "Robot de Niro");
  pic_gen_font(u8g_font_robot_de_niror, "u8g_font_robot_de_niror", 10, "Robot de Niro");
  pic_gen_font(u8g_font_robot_de_niron, "u8g_font_robot_de_niron", 10, "Robot de Niro");

  pic_gen_font(u8g_font_baby, "u8g_font_baby", 10, "Baby");
  pic_gen_font(u8g_font_babyr, "u8g_font_babyr", 10, "Baby");
  pic_gen_font(u8g_font_babyn, "u8g_font_babyn", 10, "Baby");

  pic_gen_font(u8g_font_blipfest_07, "u8g_font_blipfest_07", 10, "Blipfest 07");
  pic_gen_font(u8g_font_blipfest_07r, "u8g_font_blipfest_07r", 10, "Blipfest 07");
  pic_gen_font(u8g_font_blipfest_07n, "u8g_font_blipfest_07n", 10, "Blipfest 07");
 
  pic_gen_font(u8g_font_unifont_12_13, "u8g_font_unifont_12_13", 17, "Unifont");

  pic_gen_font(u8g_font_u8glib_4, "u8g_font_u8glib_4", 10, "u8glib 4");
  pic_gen_font(u8g_font_u8glib_4r, "u8g_font_u8glib_4r", 10, "u8glib 4");
#endif

  pic_gen_font(u8g_font_profont10, "u8g_font_profont10", 10, "ProFont");
  pic_gen_font(u8g_font_profont10r, "u8g_font_profont10r", 10, "ProFont");

  pic_gen_font(u8g_font_profont11, "u8g_font_profont11", 10, "ProFont");
  pic_gen_font(u8g_font_profont11r, "u8g_font_profont11r", 10, "ProFont");

  pic_gen_font(u8g_font_profont12, "u8g_font_profont12", 10, "ProFont");
  pic_gen_font(u8g_font_profont12r, "u8g_font_profont12r", 10, "ProFont");

  pic_gen_font(u8g_font_profont15, "u8g_font_profont15", 10, "ProFont");
  pic_gen_font(u8g_font_profont15r, "u8g_font_profont15r", 10, "ProFont");

  pic_gen_font(u8g_font_profont17, "u8g_font_profont17", 12, "ProFont");
  pic_gen_font(u8g_font_profont17r, "u8g_font_profont17r", 12, "ProFont");

  pic_gen_font(u8g_font_profont22, "u8g_font_profont22", 15, "ProFont");
  pic_gen_font(u8g_font_profont22r, "u8g_font_profont22r", 15, "ProFont");

  pic_gen_font(u8g_font_profont29, "u8g_font_profont29", 18, "ProFont");
  pic_gen_font(u8g_font_profont29r, "u8g_font_profont29r", 18, "ProFont");

  return 0;
}



