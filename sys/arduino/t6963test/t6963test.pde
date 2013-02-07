/*

  t6963test.pde
    
*/

//U8GLIB_T6963_240X128 u8g(8, 9, 10, 11,  4, 5, 6, 7,  17, 14, 15, U8G_PIN_NONE, 16); // 8Bit Com: D0..D7: 8,9,10,11,4,5,6,7 wr=en=17, cs=14, a0=di=15,rd=U8G_PIN_NONE,reset=16

#define D0 8
#define D1 9
#define D2 10
#define D3 11
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define CS 14
#define WR 17
#define RD 18



void set_port_output(void)
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

void set_port_input(void)
{
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
}

void write_byte(uint8_t val)
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
  
  digitalWrite(WR, LOW);
  delay(1);
  digitalWrite(WR, HIGH);
  delay(1);
}

uint8_t read_byte(void)
{
  uint8_t val = 0;
  
  digitalWrite(RD, LOW);
  delay(1);
  
  val |= digitalRead(D0);
  val <<= 1;
  val |= digitalRead(D0);
  val <<= 1;
  val |= digitalRead(D0);
  val <<= 1;
  val |= digitalRead(D0);
  val <<= 1;
  val |= digitalRead(D0);
  val <<= 1;
  val |= digitalRead(D0);
  val <<= 1;
  val |= digitalRead(D0);
  val <<= 1;
  val |= digitalRead(D0);

  digitalWrite(RD, HIGH);
  delay(1);
  
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

uint8_t write_cmd(uint8_t val)
{
  digitalWrite(CS, HIGH);
  if ( wait_until_01_ok() == 0 )
    return 0;
  write_byte(val);
  return 1;  
}

uint8_t write_data(uint8_t val)
{
  digitalWrite(CS, LOW);
  if ( wait_until_01_ok() == 0 )
    return 0;
  write_byte(val);
  return 1;  
}


void setup(void) 
{
  pinMode(WR, OUTPUT);
  pinMode(RD, OUTPUT);
  pinMode(CS, OUTPUT);
  set_port_output();
  
  
}

void loop(void) 
{
}

