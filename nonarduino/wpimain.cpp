

#if ! defined(ARDUINO)
extern void loop(void);
extern void setup(void);

int
main(void)
{
  setup();
  while (1) {
    loop();
  }
  return 0;
}

#endif

