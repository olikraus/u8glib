/*

  table2html.c
  
  syntax:
    file := {line}
    line := column | text
    column := ':' <identifier>
    text := <string>
  
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_MAX 1024
#define MAX_COLS 16
#define MAX_ROWS 2000

int phase;

int col_cnt = 0;
int col_last = -1;
char col_name[MAX_COLS][LINE_MAX];
int col_field_visible[MAX_COLS];

int table_line = 0;     /* used in phase 2 */
int table_lines = 0;    /* available after phase 2 */
unsigned char table_visibility[MAX_ROWS][MAX_COLS];

/* find a column by name and return its position or -1 */
int col_find(const char *name)
{
  int i;
  for( i = 0; i < col_cnt; i++ )
    if ( strcmp(col_name[i], name) == 0 )
      return i;
  return -1;
}

/* add a new column, return position */
int col_add(const char *name)
{
  if ( col_cnt >= MAX_COLS )
  {
    fprintf(stderr, "maximum number of columns reached\n");
    exit(1);
  }
  strcpy(col_name[col_cnt], name);
  col_cnt++;
  return col_cnt-1;
}

void col_clear_field_visibility(void)
{
  int i;
  for( i = 0; i < col_cnt; i++ )
    col_field_visible[i] = 0;
}

void col_mark_field_visible(int pos)
{
  col_field_visible[pos] = 1;
}

int col_is_field_visible(int pos)
{
  return col_field_visible[pos];
}

void table_next_line(void)
{
  table_line++;
  col_clear_field_visibility();
}

void table_finish_line(void)
{
  int i;
  for( i = 0; i < col_cnt; i++ )
    table_visibility[table_line][i] = (unsigned char)col_is_field_visible(i);
  table_next_line();
}

void table_add_field(int pos)
{
  if ( col_is_field_visible(pos) == 0 )
  {
    col_mark_field_visible(pos);
  }
  else
  {
    table_finish_line();
    col_mark_field_visible(pos);
  }
}

/* 
  returns 
      0 if the line is not visible 
  or 
      any other positiv integer for the rowspan
*/
int table_get_row_span(int row, int pos)
{
  int i, span = 1;
  if ( table_visibility[row][pos] == 0 )
    return 0;
  i = row+1;
  while(i < table_lines)
  {
    if ( table_visibility[i][pos] != 0 )
      break;
    span++;
    i++;
  }
  return span;
}


void html_out(const char *s)
{
  printf("%s", s);
}

void html_start_table(void)
{
  html_out("<table border=\"1\" cellspacing=\"0\">\n");
}

void html_end_table(void)
{
  html_out("</table>\n");
}


int  is_in_row;
void html_start_row(void)
{
  is_in_row = 1;
  html_out("<tr>\n");
}

void html_end_row(void)
{
  if ( is_in_row == 0 )
    return;
  is_in_row = 0;
  html_out("</tr>\n");
}


int is_in_field =  0;
void html_start_field(int pos)
{
  char buf[LINE_MAX];
  int rowspan;
  is_in_field = 1;  
  rowspan = table_get_row_span(table_line, pos);
  if ( rowspan >= 2 )
    sprintf(buf, "<td rowspan=\"%d\"><font size=\"-1\">\n", rowspan);
  else
    sprintf(buf, "<td><font size=\"-1\">\n");
  html_out(buf);
}

void html_end_field(int pos)
{
  if ( is_in_field == 0 )
    return;
  is_in_field = 0;
  html_out("</font></td>\n");
}

void table_add_field_phase2(int pos)
{
  if ( col_is_field_visible(pos) == 0 )
  {
    html_end_field(col_last);
    col_mark_field_visible(pos);
    html_start_field(pos);
  }
  else
  {
    html_end_field(col_last);
    html_end_row();
    table_next_line();
    html_start_row();
    col_mark_field_visible(pos);
    html_start_field(pos);
  }
}


void table_show_visibilty_matrx(void)
{
  int i, j;
  for( j = 0; j < table_lines; j++ )
  {
    for( i = 0; i < col_cnt; i++ )
    {
      if ( table_visibility[j][i] == 0 )
        printf(".");
      else
        printf("x");        
      printf("%d", table_get_row_span(j,i));
    }
    printf("\n");        
  }
}

void table_column(const char *name)
{
  if ( phase == 0 )     /* find number of columns */
  {
    col_last = col_find(name);
    if ( col_last < 0 ) 
      col_last = col_add(name);
  }
  else if ( phase == 1 )        /* build table visibility matrix */
  {
    col_last = col_find(name);
    if ( col_last < 0 )
      exit(0);
    table_add_field(col_last);
  }
  else if ( phase == 2 )        /* create HTML */
  {
    col_last = col_find(name);
    if ( col_last < 0 )
      exit(0);
    table_add_field_phase2(col_last);
  }
}

void table_text(const char *text)
{
  if ( phase == 2 )        /* output HTML */
  {
    html_out(text);
  }
}



void table_read_fp(FILE *fp)
{
  static char buf[LINE_MAX];
  for(;;)
  {
    if ( fgets(buf, LINE_MAX, fp) == NULL )
      return;
    if ( buf[0] == ':' )
    {
      if ( buf[1] == ':' )
      {
        /* force next line */
        if ( phase == 0 )
        {
        }
        else if ( phase == 1 )
        {
          table_finish_line();
        }
        else if ( phase == 2 )
        {
          html_end_field(col_last);
          html_end_row();
          table_next_line();
          html_start_row();
        }
      }
      else
      {
        table_column(buf+1);
      }
    }
    else
    {
      table_text(buf);
    }
  }
}

void table_read_file(const char *filename)
{
  int i;
  /* count rows */
  FILE *fp;
  fp = fopen(filename, "r");
  if ( fp == NULL )
  {
    perror(filename);
    exit(1);
  }
  phase = 0;
  col_clear_field_visibility();
  table_read_fp(fp);
  fclose(fp);

  /* build visibility matrix for rowspan calculation */
  fp = fopen(filename, "r");
  if ( fp == NULL )
  {
    perror(filename);
    exit(1);
  }
  phase = 1;
  table_line = 0;
  col_clear_field_visibility();
  table_read_fp(fp);
  table_finish_line();
  table_lines = table_line;
  fclose(fp);  
  
  /* render html */
  html_start_table();
  
  html_start_row();
  for( i = 0; i< col_cnt; i++ )
  {
    html_out("<td>\n");
    html_out(col_name[i]);
    html_out("</td>\n");
  }
  html_end_row();

  
  html_start_row();
  fp = fopen(filename, "r");
  if ( fp == NULL )
  {
    perror(filename);
    exit(1);
  }
  phase = 2;
  table_line = 0;
  col_clear_field_visibility();
  table_read_fp(fp);
  html_end_field(col_last);
  html_end_row();
  fclose(fp);  
  html_end_table();
  

}

int main(int argc, char **argv)
{
  if ( argc <= 1 )
  {
    printf("%s <tablefile>\n", argv[0]);
    return 1;
  }
  table_read_file(argv[1]);
  /* table_show_visibilty_matrx(); */
  return 0;
}
