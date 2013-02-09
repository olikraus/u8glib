/*

  t6963test.pde
  
  MSB left, LSB right
  horizontal bytes
  
  
    
*/

#include "Arduino.h"

//U8GLIB_T6963_240X128 u8g(8, 9, 10, 11,  4, 5, 6, 7,  17, 14, 15, U8G_PIN_NONE, 16); // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 wr=en=17, cs=14, a0=di=15,rd=U8G_PIN_NONE,reset=16

#define WIDTH 240
#define HEIGHT 64

#define D0 8
#define D1 9
#define D2 10
#define D3 11

#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define CS 14
#define CD 15
#define RST 16
#define WR 17
#define RD 18

static volatile uint8_t *output_data_port[8];
static volatile uint8_t *input_data_port[8];
static volatile uint8_t *mode_port[8];
static uint8_t data_mask[8];

void fast_parallel_init(void)
{
  output_data_port[0] =  portOutputRegister(digitalPinToPort(D0));
  input_data_port[0] =  portInputRegister(digitalPinToPort(D0));
  mode_port[0] =  portModeRegister(digitalPinToPort(D0));
  data_mask[0] =  digitalPinToBitMask(D0);
  
  output_data_port[1] =  portOutputRegister(digitalPinToPort(D1));
  input_data_port[1] =  portInputRegister(digitalPinToPort(D1));
  mode_port[1] =  portModeRegister(digitalPinToPort(D1));
  data_mask[1] =  digitalPinToBitMask(D1);
  
  output_data_port[2] =  portOutputRegister(digitalPinToPort(D2));
  input_data_port[2] =  portInputRegister(digitalPinToPort(D2));
  mode_port[2] =  portModeRegister(digitalPinToPort(D2));
  data_mask[2] =  digitalPinToBitMask(D2);
  
  output_data_port[3] =  portOutputRegister(digitalPinToPort(D3));
  input_data_port[3] =  portInputRegister(digitalPinToPort(D3));
  mode_port[3] =  portModeRegister(digitalPinToPort(D3));
  data_mask[3] =  digitalPinToBitMask(D3);
  
  output_data_port[4] =  portOutputRegister(digitalPinToPort(D4));
  input_data_port[4] =  portInputRegister(digitalPinToPort(D4));
  mode_port[4] =  portModeRegister(digitalPinToPort(D4));
  data_mask[4] =  digitalPinToBitMask(D4);
  
  output_data_port[5] =  portOutputRegister(digitalPinToPort(D5));
  input_data_port[5] =  portInputRegister(digitalPinToPort(D5));
  mode_port[5] =  portModeRegister(digitalPinToPort(D5));
  data_mask[5] =  digitalPinToBitMask(D5);
  
  output_data_port[6] =  portOutputRegister(digitalPinToPort(D6));
  input_data_port[6] =  portInputRegister(digitalPinToPort(D6));
  mode_port[6] =  portModeRegister(digitalPinToPort(D6));
  data_mask[6] =  digitalPinToBitMask(D6);
  
  output_data_port[7] =  portOutputRegister(digitalPinToPort(D7));
  input_data_port[7] =  portInputRegister(digitalPinToPort(D7));
  mode_port[7] =  portModeRegister(digitalPinToPort(D7));
  data_mask[7] =  digitalPinToBitMask(D7);  
}

void fast_write_data_pin(uint8_t pin, uint8_t val)
{
  if ( val != 0 )
    *output_data_port[pin] |= data_mask[pin];
  else
    *output_data_port[pin] &= ~data_mask[pin];
}

uint8_t fast_read_data_pin(uint8_t pin)
{
  if ( (*input_data_port[pin] & data_mask[pin]) == 0 )
    return 0;
  return 1;
}


void _set_port_output(void)
{
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void set_port_output(void)
{
  uint8_t i;
  for( i = 0; i < 8; i++ )
  {
      *mode_port[i] |= data_mask[i]; 
  }
}


void _set_port_input(void)
{
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
}

void set_port_input(void)
{
  uint8_t i;
  for( i = 0; i < 8; i++ )
  {
      *mode_port[i] &= ~data_mask[i]; 
      *output_data_port[i] &= ~data_mask[i]; 	// no pullup
  }
}


void _write_byte(uint8_t val)
{
  
  digitalWrite(D0, val&1);
  val >>= 1;
  digitalWrite(D1, val&1);
  val >>= 1;
  digitalWrite(D2, val&1);
  val >>= 1;
  digitalWrite(D3, val&1);
  val >>= 1;
  digitalWrite(D4, val&1);
  val >>= 1;
  digitalWrite(D5, val&1);
  val >>= 1;
  digitalWrite(D6, val&1);
  val >>= 1;
  digitalWrite(D7, val&1);
  
  //digitalWrite(CS, LOW);
  digitalWrite(WR, LOW);
  delayMicroseconds(1);	// 80ns 
  digitalWrite(WR, HIGH);
  //digitalWrite(CS, HIGH);
  //delayMicroseconds(1);	// 10ns 
}

void write_byte(uint8_t val)
{
  
  fast_write_data_pin(0, val&1);
  val >>= 1;
  fast_write_data_pin(1, val&1);
  val >>= 1;
  fast_write_data_pin(2, val&1);
  val >>= 1;
  fast_write_data_pin(3, val&1);
  val >>= 1;
  fast_write_data_pin(4, val&1);
  val >>= 1;
  fast_write_data_pin(5, val&1);
  val >>= 1;
  fast_write_data_pin(6, val&1);
  val >>= 1;
  fast_write_data_pin(7, val&1);
  
  //digitalWrite(CS, LOW);
  digitalWrite(WR, LOW);
  //__asm("nop");
  delayMicroseconds(1);	// 80ns 
  digitalWrite(WR, HIGH);
  //digitalWrite(CS, HIGH);
  //delayMicroseconds(1);	// 10ns 
}

uint8_t _read_byte(void)
{
  uint8_t val = 0;
  
  //digitalWrite(CS, LOW);
  digitalWrite(RD, LOW);
  delayMicroseconds(1);	// 150ns 
  
  // skip some pins to read
  //val |= digitalRead(D7)&1;
  //val <<= 1;
  //val |= digitalRead(D6)&1;
  //val <<= 1;
  //val |= digitalRead(D5)&1;
  //val <<= 1;
  //val |= digitalRead(D4)&1;
  //val <<= 1;
  val |= digitalRead(D3)&1;
  val <<= 1;
  // val |= digitalRead(D2)&1;
  val <<= 1;
  val |= digitalRead(D1)&1;
  val <<= 1;
  val |= digitalRead(D0)&1;

  digitalWrite(RD, HIGH);
  //digitalWrite(CS, HIGH);  
  //delayMicroseconds(1);	// 10ns 
  
  return val;
}

uint8_t read_byte(void)
{
  uint8_t val = 0;
  
  //digitalWrite(CS, LOW);
  digitalWrite(RD, LOW);
  //delayMicroseconds(1);	// 150ns 
  
  // skip some pins to read
  //val |= digitalRead(D7)&1;
  //val <<= 1;
  //val |= digitalRead(D6)&1;
  //val <<= 1;
  //val |= digitalRead(D5)&1;
  //val <<= 1;
  //val |= digitalRead(D4)&1;
  //val <<= 1;
  if ( (*input_data_port[3] & data_mask[3]) != 0 )
    val++;
  val <<= 1;
  // val |= digitalRead(D2)&1;
  val <<= 1;
  if ( (*input_data_port[1] & data_mask[1]) != 0 )
    val++;
  val <<= 1;
  if ( (*input_data_port[0] & data_mask[0]) != 0 )
    val++;
    
  digitalWrite(RD, HIGH);
  //digitalWrite(CS, HIGH);  
  //delayMicroseconds(1);	// 10ns 
  
  return val;
}

uint8_t wait_until_01_ok(void)
{
  long x;
  
  set_port_input();
  x = millis();
  x += 100;

  for(;;)
  {    
    if ( (read_byte() & 3) == 3 )
      break;
    if ( x < millis() )
      return 0;
  }
  set_port_output();
  return 1;
}

uint8_t wait_until_3_ok(void)
{
  long x;
  
  set_port_input();
  x = millis();
  x += 100;

  for(;;)
  {    
    if ( (read_byte() & 8) == 8 )
      break;
    if ( x < millis() )
      return 0;
  }
  set_port_output();
  return 1;
}

uint8_t write_cmd(uint8_t val)
{
  digitalWrite(CD, HIGH);
  if ( wait_until_01_ok() == 0 )
    return 0;
  digitalWrite(CD, HIGH);
  write_byte(val);
  return 1;  
}

uint8_t write_data(uint8_t val)
{
  digitalWrite(CD, HIGH);
  if ( wait_until_01_ok() == 0 )
    return 0;
  digitalWrite(CD, LOW);
  write_byte(val);
  return 1;  
}

uint8_t write_auto_data(uint8_t val)
{
  digitalWrite(CD, HIGH);
  if ( wait_until_3_ok() == 0 )
    return 0;
  digitalWrite(CD, LOW);
  write_byte(val);
  return 1;  
}


uint8_t _write_init(void)
{
  int i, j;
  static uint8_t x = 1;
  
  // text home address at 0x0000
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_cmd(0x40) == 0 ) return 0;
  // graphics home address at 0x0000
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_cmd(0x42) == 0 ) return 0;
  // text area 0x0014 columns
  if ( write_data(0x14) == 0 ) return 0;
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_cmd(0x41) == 0 ) return 0;
  // graphics area 0x0014 columns
  if ( write_data(WIDTH/8/2-1) == 0 ) return 0;
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_cmd(0x43) == 0 ) return 0;
  // cursor position at 0x0000
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_cmd(0x21) == 0 ) return 0;
  // mode set
  // 0x080: Internal CG, OR Mode
  // 0x081: Internal CG, EXOR Mode
  // 0x083: Internal CG, AND Mode
  // 0x088: External CG, OR Mode
  // 0x089: External CG, EXOR Mode
  // 0x08B: External CG, AND Mode
  if ( write_cmd(0x80) == 0 ) return 0;
  // display mode
  // 0x090: Display off
  // 0x094: Graphic off, text on, cursor off, blink off
  // 0x096: Graphic off, text on, cursor on, blink off
  // 0x097: Graphic off, text on, cursor on, blink on
  // 0x098: Graphic on, text off, cursor off, blink off
  // 0x09a: Graphic on, text off, cursor on, blink off
  // ...
  // 0x09c: Graphic on, text on, cursor off, blink off
  // 0x09f: Graphic on, text on, cursor on, blink on
  if ( write_cmd(0x98) == 0 ) return 0;
  // cursor pattern: 8 line
  if ( write_cmd(0xa7) == 0 ) return 0;
  // offset to 0x0000
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_cmd(0x22) == 0 ) return 0;
  // address ptr to 0x0000
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_data(0x00) == 0 ) return 0;
  if ( write_cmd(0x24) == 0 ) return 0;

  for( j = 0; j < HEIGHT; j ++ )
  {
    uint16_t pos;
    pos = WIDTH/8;
    pos *= j;
    // address ptr to "pos"
    if ( write_data(pos&255) == 0 ) return 0;
    if ( write_data(pos>>8) == 0 ) return 0;
    if ( write_cmd(0x24) == 0 ) return 0;
    
    // auto write
    if ( write_cmd(0xb0) == 0 ) return 0;
    for( i = 0; i < WIDTH/8; i++ )
    {
      if ( write_auto_data(x) == 0 ) return 0;
    }
    // auto reset
    if ( write_cmd(0xb2) == 0 ) return 0;
    
    /*
    for( i = 0; i < WIDTH/8; i++ )
    {
      
      if ( write_data(x) == 0 ) return 0;
      if ( write_cmd(0xc0) == 0 ) return 0;
    }
    */
    x++;
  }
  return 1;
  
}

uint8_t write_init(void)
{
  uint8_t  r;
  delay(1);
  digitalWrite(CS, LOW);
  r = _write_init();
  digitalWrite(CS, HIGH);
  delay(1);
  return r;
}

void setup(void) 
{
  fast_parallel_init();
  
  pinMode(13, OUTPUT);
  
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  
  pinMode(CD, OUTPUT);
  digitalWrite(CD, HIGH);
  
  pinMode(RST, OUTPUT);
  digitalWrite(RST, HIGH);
  
  pinMode(WR, OUTPUT);
  digitalWrite(WR, HIGH);
  
  pinMode(RD, OUTPUT);
  digitalWrite(RD, HIGH);
  
  set_port_output();
  
  delay(1);
  digitalWrite(RST, LOW);
  delay(300);
  digitalWrite(RST, HIGH);
  delay(200);

  
}

void loop(void) 
{
  fast_parallel_init();
  if ( write_init() == 0 )
  {
    digitalWrite(13, LOW);  // LED Off
    /*
    for(;;)
    {
      digitalWrite(13, LOW);
      delay(20);
      digitalWrite(13, HIGH);
      delay(20);
      digitalWrite(13, LOW);
    }
    */
  }
  else
  {
    digitalWrite(13, HIGH);   // LED On
    /*
    for(;;)
    {
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
    }
    */
  }
  
}

