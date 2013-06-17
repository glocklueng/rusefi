/*
 * print.c
 *
 * print function with float support.
 * It kinda seems like float support is a bit broken :(
 */

#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <sys\types.h>

#include "print.h"

#define  PAD_RIGHT   1
#define  PAD_ZERO    2

static int use_leading_plus = 0 ;

//****************************************************************************
//  This version returns the length of the output string.
//  It is more useful when implementing a walking-string function.
//****************************************************************************
static const float round_nums[8] = {
   0.5,
   0.05,
   0.005,
   0.0005,
   0.00005,
   0.000005,
   0.0000005,
   0.00000005
} ;

static uint my_strlen(char *str)
{
   if (str == 0)
      return 0;
   uint slen = 0 ;
   while (*str != 0) {
      slen++ ;
      str++ ;
   }
   return slen;
}

static unsigned dbl2stri(char *outbfr, float dbl, unsigned dec_digits)
{
   static char local_bfr[128] ;
   char *output = (outbfr == 0) ? local_bfr : outbfr ;

   //*******************************************
   //  extract negative info
   //*******************************************
   if (dbl < 0.0) {
      *output++ = '-' ;
      dbl *= -1.0 ;
   } else {
      if (use_leading_plus) {
         *output++ = '+' ;
      }
   }

   //  handling rounding by adding .5LSB to the floating-point data
   if (dec_digits < 8) {
      dbl += round_nums[dec_digits] ;
   }

   //**************************************************************************
   //  construct fractional multiplier for specified number of digits.
   //**************************************************************************
   uint mult = 1 ;
   uint idx ;
   for (idx=0; idx < dec_digits; idx++)
      mult *= 10 ;

   // printf("mult=%u\n", mult) ;
   uint wholeNum = (uint) dbl ;
   uint decimalNum = (uint) ((dbl - wholeNum) * mult);

   //*******************************************
   //  convert integer portion
   //*******************************************
   char tbfr[40] ;
   idx = 0 ;
   while (wholeNum != 0) {
      tbfr[idx++] = '0' + (wholeNum % 10) ;
      wholeNum /= 10 ;
   }
   // printf("%.3f: whole=%s, dec=%d\n", dbl, tbfr, decimalNum) ;
   if (idx == 0) {
      *output++ = '0' ;
   } else {
      while (idx > 0) {
         *output++ = tbfr[idx-1] ;  //lint !e771
         idx-- ;
      }
   }
   if (dec_digits > 0) {
      *output++ = '.' ;

      //*******************************************
      //  convert fractional portion
      //*******************************************
      idx = 0 ;
      while (decimalNum != 0) {
         tbfr[idx++] = '0' + (decimalNum % 10) ;
         decimalNum /= 10 ;
      }
      //  pad the decimal portion with 0s as necessary;
      //  We wouldn't want to report 3.093 as 3.93, would we??
      while (idx < dec_digits) {
         tbfr[idx++] = '0' ;
      }
      // printf("decimal=%s\n", tbfr) ;
      if (idx == 0) {
         *output++ = '0' ;
      } else {
         while (idx > 0) {
            *output++ = tbfr[idx-1] ;
            idx-- ;
         }
      }
   }
   *output = 0 ;

   //  prepare output
   output = (outbfr == 0) ? local_bfr : outbfr ;
   return my_strlen(output) ;
}

static int prints (const char *string, int width, int pad)
{
	register int pc = 0, padchar = ' ';
	if (width > 0) {
      int len = 0;
      const char *ptr;
		for (ptr = string; *ptr; ++ptr)
			++len;
		if (len >= width)
			width = 0;
		else
			width -= len;
		if (pad & PAD_ZERO)
			padchar = '0';
	}
	if (!(pad & PAD_RIGHT)) {
		for (; width > 0; --width) {
			consolePutChar (padchar);
			++pc;
		}
	}
	for (; *string; ++string) {
		consolePutChar (*string);
		++pc;
	}
	for (; width > 0; --width) {
		consolePutChar (padchar);
		++pc;
	}
	return pc;
}

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12
static int printi (int i, int b, int sg, int width, int pad, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
   char *s;
   int t, neg = 0, pc = 0;
   unsigned u = (unsigned) i;
	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints (print_buf, width, pad);
	}
	if (sg && b == 10 && i < 0) {
		neg = 1;
      u = (unsigned) -i;
	}
   //  make sure print_buf is NULL-term
	s = print_buf + PRINT_BUF_LEN - 1;
	*s = '\0';


	while (u) {
      t = u % b;  //lint !e573  Warning 573: Signed-unsigned mix with divide
		if (t >= 10)
			t += letbase - '0' - 10;
		*--s = t + '0';
      u /= b;  //lint !e573  Warning 573: Signed-unsigned mix with divide
	}
	if (neg) {
		if (width && (pad & PAD_ZERO)) {
			consolePutChar ('-');
			++pc;
			--width;
		}
		else {
			*--s = '-';
		}
   } else {
      if (use_leading_plus) {
         *--s = '+';
      }
   }
	return pc + prints (s, width, pad);
}

static int theprint (int *varg)
{
   int post_decimal ;
   int width, pad ;
   unsigned dec_width = 6 ;
   int pc = 0;
   char *format = (char *) (*varg++);
   char scr[2];
   use_leading_plus = 0 ;  //  start out with this clear
	for (; *format != 0; ++format) {
		if (*format == '%') {
         dec_width = 6 ;
			++format;
			width = pad = 0;
			if (*format == '\0')
				break;
			if (*format == '%')
            goto out_lbl;
			if (*format == '-') {
				++format;
				pad = PAD_RIGHT;
			}
         if (*format == '+') {
            ++format;
            use_leading_plus = 1 ;
         }
         while (*format == '0') {
				++format;
				pad |= PAD_ZERO;
			}
         post_decimal = 0 ;
         if (*format == '.'  ||
            (*format >= '0' &&  *format <= '9')) {

            while (1) {
               if (*format == '.') {
                  post_decimal = 1 ;
                  dec_width = 0 ;
                  format++ ;
               } else if ((*format >= '0' &&  *format <= '9')) {
                  if (post_decimal) {
                     dec_width *= 10;
                     dec_width += *format - '0';
                  } else {
                     width *= 10;
                     width += *format - '0';
                  }
                  format++ ;
               } else {
                  break;
               }
            }
         }
         if (*format == 'l')
            ++format;
         switch (*format) {
         case 's':
            {
            // char *s = *((char **) varg++);   //lint !e740
            char *s = (char *) *varg++ ;  //lint !e740 !e826  convert to double pointer
            pc += prints ( s ? s : "(null)", width, pad);
            use_leading_plus = 0 ;  //  reset this flag after printing one value
            }
            break;
         case 'd':
            pc += printi ( *varg++, 10, 1, width, pad, 'a');
            use_leading_plus = 0 ;  //  reset this flag after printing one value
            break;
         case 'x':
            pc += printi (*varg++, 16, 0, width, pad, 'a');
            use_leading_plus = 0 ;  //  reset this flag after printing one value
            break;
         case 'X':
            pc += printi (*varg++, 16, 0, width, pad, 'A');
            use_leading_plus = 0 ;  //  reset this flag after printing one value
            break;
         case 'u':
            pc += printi ( *varg++, 10, 0, width, pad, 'a');
            use_leading_plus = 0 ;  //  reset this flag after printing one value
            break;
         case 'c':
            /* char are converted to int then pushed on the stack */
            scr[0] = *varg++;
            scr[1] = '\0';
            pc += prints (scr, width, pad);
            use_leading_plus = 0 ;  //  reset this flag after printing one value
            break;

         case 'f':
            {
            // http://wiki.debian.org/ArmEabiPort#Structpackingandalignment
            // Stack alignment
            //
            // The ARM EABI requires 8-byte stack alignment at public function entry points,
            // compared to the previous 4-byte alignment.
            char *cptr = (char *) varg ;  //lint !e740 !e826  convert to double pointer
            // just a bit of hell related to parameters alignment
            uint caddr = (uint) cptr ;
            if ((caddr & 0x7) != 0) {
               cptr += 4 ;
            }
            double *dblptr = (double *) cptr ;  //lint !e740 !e826  convert to double pointer
            double dbl = *dblptr++ ;   //  increment double pointer
            varg = (int *) dblptr ;    //lint !e740  copy updated pointer back to base pointer
            char bfr[81] ;
            // unsigned slen =
            dbl2stri(bfr, dbl, dec_width) ;
            // stuff_talkf("[%s], width=%u, dec_width=%u\n", bfr, width, dec_width) ;
            pc += prints ( bfr, width, pad);
            use_leading_plus = 0 ;  //  reset this flag after printing one value
            }
            break;

         default:
        	 consolePutChar ('%');
        	 consolePutChar (*format);
            use_leading_plus = 0 ;  //  reset this flag after printing one value
            break;
         }
      } else
      // if (*format == '\\') {
      //
      // } else
      {
out_lbl:
			consolePutChar ( *format);
			++pc;
		}
   }  //  for each char in format string
//   if (out) //lint !e850
//		**out = '\0';
	return pc;
}

void print (const char *format, ...)
{
   //  create a pointer into the stack.
   //  Thematically this should be a void*, since the actual usage of the
   //  pointer will vary.  However, int* works fine too.
   //  Either way, the called function will need to re-cast the pointer
   //  for any type which isn't sizeof(int)
   int *varg = (int *) (char *) (&format);
   theprint (varg);
}
