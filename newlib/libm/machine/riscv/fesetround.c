/*
  (c) Copyright 2017 Michael R. Neilly
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  * Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  * Neither the names of the copyright holders nor the names of their
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include <math.h>
#include <fenv.h>

/* This implementation is intended to comply with the following
 * specification:
 *
 * http://pubs.opengroup.org/onlinepubs/009695399/functions/fesetround.html
 * Referred to as 'fegetenv.html below.
 *
 * "The fesetround() function shall establish the rounding direction
 * represented by its argument round. If the argument is not equal to
 * the value of a rounding direction macro, the rounding direction is
 * not changed."
 */

#if __RISCV_HARD_FLOAT

int fesetround(int round)
{

  /* Mask round to be sure only valid rounding bits are set */

  round &= FE_RMODE_MASK;

  /* Set the rounding mode */

  __asm__ volatile("fsrm %0" : : "r"(round));

  /* Per 'fesetround.html:
   *
   * "The fesetround() function shall return a zero value if and only
   * if the requested rounding direction was established."
   */

  return 0;
}
#else
#include ".././fenv/fesetround.c"
#endif
