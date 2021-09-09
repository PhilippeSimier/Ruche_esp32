/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ale
 *
 * Created on 8 septembre 2021, 13:30
 tag3 3
 * 
 FX.25[0] send frame: FX.25 mode = 103
  000:  a8 8a a6 a8 40 40 60 ae 84 64 9e a6 b4 63 03 f0  ....@@`..d...c..
  010:  46 6f 6f 3f 42 61 72 3f                          Foo?Bar?
FX.25[0]: transmit 64 data bytes, ctag number 0x03
  000:  7e a8 8a a6 a8 40 40 60 ae 84 64 9e a6 b4 63 03  ~....@@`..d...c.
  010:  f0 46 6f 6f 5f 84 c2 e4 be f4 16 fb f9 f9 f9 f9  .Foo_...........
  020:  f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9  ................
  030:  f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9  ................
FX.25[0]: transmit 16 check bytes:
  000:  41 32 58 30 6e dd 6c a3 a1 10 83 f2 1e c2 59 aa  A2X0n.l.......Y.

 FX.25[0] send frame: FX.25 mode = 103
  000:  a8 8a a6 a8 40 40 60 ae 84 64 9e a6 b4 63 03 f0  ....@@`..d...c..
  010:  46 6f 6f 3f 42 61 72 3f                          Foo?Bar?
FX.25[0]: transmit 64 data bytes, ctag number 0x03 avec RS(80,64) 
  000:  7e a8 8a a6 a8 40 40 60 ae 84 64 9e a6 b4 63 03  ~....@@`..d...c.
  010:  f0 46 6f 6f 5f 84 c2 e4 be f4 16 fb f9 f9 f9 f9  .Foo_...........
  020:  f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9  ................
  030:  f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9  ................
FX.25[0]: transmit 16 check bytes:
  000:  41 32 58 30 6e dd 6c a3 a1 10 83 f2 1e c2 59 aa  A2X0n.l.......Y.
 * 
 */

#include <cstdlib>
#include <ostream>
#include <iostream>

#include "Rs.h"


using namespace std;

static int stuff_it (unsigned char *in, int ilen, unsigned char *out, int osize);
int fx25_send_frame (int chan, unsigned char *fbuf, int flen, int fx_mode);
unsigned short fcs_calc (unsigned char *data, int len);

static const unsigned short ccitt_table[256] = {

// from http://www.ietf.org/rfc/rfc1549.txt

   0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
   0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
   0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
   0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
   0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
   0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
   0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
   0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
   0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
   0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
   0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
   0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
   0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
   0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
   0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
   0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
   0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
   0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
   0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
   0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
   0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
   0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
   0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
   0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
   0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
   0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
   0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
   0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
   0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
   0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
   0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
   0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78

};


Rs leRs;
/*
 * 
 */
int main(int argc, char** argv) {

    static unsigned char preload[] = {
        'T' << 1, 'E' << 1, 'S' << 1, 'T' << 1, ' ' << 1, ' ' << 1, 0x60,
        'W' << 1, 'B' << 1, '2' << 1, 'O' << 1, 'S' << 1, 'Z' << 1, 0x63,
        0x03, 0xf0,
        'F', 'o', 'o', '?', 'B', 'a', 'r', '?', //  '?' causes bit stuffing  oui effectivement LSB 1st
        0, 0, 0 // Room for FCS + extra
    };


    printf("fxsend - FX.25 unit test.\n");
    printf("This generates 11 files named fx01.dat, fx02.dat, ..., fx0b.dat\n");
    //dw_printf("Run fxrec as second part of test.\n");

    leRs.fx25_init(3);

    for (int i = 100 + CTAG_MIN; i <= 100 + CTAG_MAX; i++) {
        fx25_send_frame(0, preload, (int) sizeof (preload) - 3, i);
    }
    return 0;
}

int fx25_send_frame (int chan, unsigned char *fbuf, int flen, int fx_mode)
{

	if (leRs.fx25_get_debug() >= 3) {
	  printf ("------\n");
	  printf ("FX.25[%d] send frame: FX.25 mode = %d\n", chan, fx_mode);
	  leRs.fx_hex_dump (fbuf, flen);
	}

	// Append the FCS.

	int fcs = fcs_calc (fbuf, flen);
	fbuf[flen++] = fcs & 0xff;
	fbuf[flen++] = (fcs >> 8) & 0xff;

	// Add bit-stuffing.

	unsigned char data[FX25_MAX_DATA+1];
	const unsigned char fence = 0xaa;
	data[FX25_MAX_DATA] = fence;

	int dlen = stuff_it(fbuf, flen, data, FX25_MAX_DATA);

	assert (data[FX25_MAX_DATA] == fence);
	if (dlen < 0) {	  
	  printf ("FX.25[%d]: Frame length of %d + overhead is too large to encode.\n", chan, flen);
	  return (-1);
	}

	// Pick suitable correlation tag depending on
	// user's preference, for number of check bytes,
	// and the data size.

	int ctag_num = leRs.fx25_pick_mode (fx_mode, dlen);

	if (ctag_num < CTAG_MIN || ctag_num > CTAG_MAX) {
	  printf ("FX.25[%d]: Could not find suitable format for requested %d and data length %d.\n", chan, fx_mode, dlen);
	  return (-1);
	}

	uint64_t ctag_value = leRs.fx25_get_ctag_value (ctag_num);

	// Zero out part of data which won't be transmitted.
	// It should all be filled by extra HDLC "flag" patterns.

	int k_data_radio = leRs.fx25_get_k_data_radio (ctag_num);
	int k_data_rs = leRs.fx25_get_k_data_rs (ctag_num);
	int shorten_by = FX25_MAX_DATA - k_data_radio;
	if (shorten_by > 0) {
	  memset (data + k_data_radio, 0, shorten_by);
	}

	// Compute the check bytes.

	unsigned char check[FX25_MAX_CHECK+1];
	check[FX25_MAX_CHECK] = fence;
	struct rs *rs = leRs.fx25_get_rs (ctag_num);

	assert (k_data_rs + NROOTS == NN);

	leRs.ENCODE_RS(rs, data, check);
	assert (check[FX25_MAX_CHECK] == fence);

	if (leRs.fx25_get_debug() >= 3) {
	  printf ("FX.25[%d]: transmit %d data bytes, ctag number 0x%02x\n", chan, k_data_radio, ctag_num);
	  leRs.fx_hex_dump (data, k_data_radio);
	  printf ("FX.25[%d]: transmit %d check bytes:\n", chan, NROOTS);
	  leRs.fx_hex_dump (check, NROOTS);
	  printf ("------\n");
	}
       return 1; 
}



#define put_bit(value)  {						\
			if (olen >= osize) return(-1);			\
			if (value) out[olen>>3] |= 1 << (olen & 0x7);	\
			olen++;						\
			}

static int stuff_it (unsigned char *in, int ilen, unsigned char *out, int osize)
{
	const unsigned char flag = 0x7e;
	int ret = -1;
	memset (out, 0, osize);
	out[0] = flag;
	int olen = 8;			// Number of bits in output.
	osize *= 8;			// Now in bits rather than bytes.
	int ones = 0;

	for (int i = 0; i < ilen; i++) {
	  for (unsigned char imask = 1; imask != 0; imask <<= 1) {
	    int v = in[i] & imask;
	    put_bit(v);
	    if (v) {
	      ones++;
	      if (ones == 5) {
	        put_bit(0);
	        ones = 0;
	      }
	    }
	    else {
	      ones = 0;
	    }
	  }
	}
	for (unsigned char imask = 1; imask != 0; imask <<= 1) {
	  put_bit(flag & imask);
	}
	ret = (olen + 7) / 8;		// Includes any partial byte.

	unsigned char imask = 1;
	while (olen < osize) {
	  put_bit( flag & imask);
	  imask = (imask << 1) | (imask >> 7);	// Rotate.
	}

	return (ret);

} // end stuff_it

/* 
 * Use this for an AX.25 frame. 
 */

unsigned short fcs_calc (unsigned char *data, int len)
{
	unsigned short crc = 0xffff;
	int j;

	for (j=0; j<len; j++) {

  	  crc = ((crc) >> 8) ^ ccitt_table[((crc) ^ data[j]) & 0xff];
	}

	return ( crc ^ 0xffff );
}
