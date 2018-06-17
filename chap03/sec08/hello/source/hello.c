/* hello.c */
int main()
{
  *(unsigned int*)0x04000000=0x0403;
  ((unsigned short*)0x06000000)[120+80*240]=0x001f;
  ((unsigned short*)0x06000000)[136+80*240]=0x03e0;
  ((unsigned short*)0x06000000)[120+96*240]=0x7c00;
  while(1);
}
