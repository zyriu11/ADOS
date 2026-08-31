#include "libc.h"
int
strnlen (const char *s, size_t maxlen)
{
  int i;

  for (i = 0; i < maxlen; ++i)
    if (s[i] == '\0')
      break;
  return i;
}