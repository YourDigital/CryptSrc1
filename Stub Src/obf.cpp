#include "obf.h"
#define KEY "03uvIJqo5DepFBViBHhX"

void Obf(BYTE *data, int dataSize)
{
   for (int i = 0; i < dataSize; ++i)
   {
      data[i] ^= KEY[i % (sizeof(KEY) - 1)];
      data[i] ^= '\0';
   }
}