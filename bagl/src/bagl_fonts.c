/*******************************************************************************
*   Ledger Blue - Non secure firmware
*   (c) 2016 Ledger
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
********************************************************************************/


#include "string.h"
#include "bagl.h"

/*******************************************************************************
 * FONT REQUIRED FORMAT                                                        *
 * Data length: 8 bits                                                         *
 * Invert bits: No                                                             *
 * Data format: Little Endian, Row based, Row preferred, Packed                *
 *******************************************************************************/

#include "bagl_font_lucida_console_8.inc"

#include "bagl_font_open_sans_bold_13px.inc"
#include "bagl_font_open_sans_bold_21px.inc"
#include "bagl_font_open_sans_light_13px.inc"
#include "bagl_font_open_sans_light_14px.inc"
#include "bagl_font_open_sans_light_16px.inc"
#include "bagl_font_open_sans_light_21px.inc"
#include "bagl_font_open_sans_semibold_18px.inc"

#include "bagl_font_comic_sans_ms_20px.inc"

const bagl_font_t fontNONE = {
   0 , /* font height in pixels   */
   0 , /* baseline distance from top */
   0, /* kerning */
   0x0000, /* first character */
   0x0000, /* last character  */
   NULL,  /* address of first character */
};

const bagl_font_t* const C_bagl_fonts[] = {

#ifdef HAVE_BAGL_FONT_LUCIDA_CONSOLE_8
  &fontLUCIDA_CONSOLE_8,
#else
  &fontNONE,
#endif // HAVE_BAGL_FONT_LUCIDA_CONSOLE_8

#ifdef HAVE_BAGL_FONT_OPEN_SANS_BOLD_13
  &fontOPEN_SANS_BOLD_13PX,
#else
  &fontNONE,
#endif

#ifdef HAVE_BAGL_FONT_OPEN_SANS_BOLD_21
  &fontOPEN_SANS_BOLD_21PX,
#else
  &fontNONE,
#endif

#ifdef HAVE_BAGL_FONT_OPEN_SANS_LIGHT_13
  &fontOPEN_SANS_LIGHT_13PX,
#else
  &fontNONE,
#endif

#ifdef HAVE_BAGL_FONT_OPEN_SANS_LIGHT_14
  &fontOPEN_SANS_LIGHT_14PX,
#else
  &fontNONE,
#endif

#ifdef HAVE_BAGL_FONT_OPEN_SANS_LIGHT_16
  &fontOPEN_SANS_LIGHT_16PX,
#else
  &fontNONE,
#endif

#ifdef HAVE_BAGL_FONT_OPEN_SANS_LIGHT_21
  &fontOPEN_SANS_LIGHT_21PX,
#else
  &fontNONE,
#endif

#ifdef HAVE_BAGL_FONT_OPEN_SANS_LIGHT_18
  &fontOPEN_SANS_SEMIBOLD_18PX,
#else
  &fontNONE,
#endif

#ifdef HAVE_BAGL_FONT_COMIC_SANS_MS_20
  &fontCOMIC_SANS_MS_20PX,
#else
  &fontNONE,
#endif // HAVE_BL
};
