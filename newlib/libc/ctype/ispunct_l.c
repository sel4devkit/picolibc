/*
Copyright (c) 2016 Corinna Vinschen <corinna@vinschen.de> 
Modified (m) 2017 Thomas Wolff: revise Unicode and locale/wchar handling
 */
#include <_ansi.h>
#include <ctype.h>

#undef ispunct_l

int
ispunct_l (int c, struct __locale_t *locale)
{
  return __locale_ctype_ptr_l (locale)[c+1] & _P;
}

