/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rs.cpp
 * Author: ale
 * 
 * Created on 8 septembre 2021, 13:32
 */

#include "Rs.h"

Rs::Rs() {
}

Rs::Rs(const Rs& orig) {
}

Rs::~Rs() {
}

int Rs::fx25_tag_find_match (uint64_t t)
{
	for (int c = CTAG_MIN; c <= CTAG_MAX; c++) {
	  if (__builtin_popcountll(t ^ tags[c].value) <= CLOSE_ENOUGH) {
	    //printf ("%016" PRIx64 " received\n", t);
	    //printf ("%016" PRIx64 " tag %d\n", tags[c].value, c);
	    //printf ("%016" PRIx64 " xor, popcount = %d\n", t ^ tags[c].value, __builtin_popcountll(t ^ tags[c].value));
	    return (c);
	  }
	}
	return (-1);
}


void Rs::free_rs_char(struct rs *rs){
  free(rs->alpha_to);
  free(rs->index_of);
  free(rs->genpoly);
  free(rs);
}

void Rs::fx25_init ( int debug_level )
{
	g_debug_level = debug_level;

	for (int i = 0 ; i < NTAB ; i++) {
	  Tab[i].rs = INIT_RS(Tab[i].symsize, Tab[i].genpoly, Tab[i].fcs,  Tab[i].prim, Tab[i].nroots);
	  if (Tab[i].rs == NULL) {
	        //text_color_set(DW_COLOR_ERROR);
		//dw_printf("FX.25 internal error: init_rs_char failed!\n");
		exit(EXIT_FAILURE);
	  }
	}

	// Verify integrity of tables and assumptions.
	// This also does a quick check for the popcount function.

	for (int j = 0; j < 16 ; j++) {
	  for (int k = 0; k < 16; k++) {
	    if (j == k) {
	      assert (__builtin_popcountll(tags[j].value ^ tags[k].value) == 0);
	    }
	    else {
	      assert (__builtin_popcountll(tags[j].value ^ tags[k].value) == 32);
	    }
          }
	}

	for (int j = CTAG_MIN; j <= CTAG_MAX; j++) {
	  assert (tags[j].n_block_radio - tags[j].k_data_radio == Tab[tags[j].itab].nroots);
	  assert (tags[j].n_block_rs - tags[j].k_data_rs == Tab[tags[j].itab].nroots);
	  assert (tags[j].n_block_rs == FX25_BLOCK_SIZE);
	}

	assert (fx25_pick_mode (100+1, 239) == 1);
	assert (fx25_pick_mode (100+1, 240) == -1);

	assert (fx25_pick_mode (100+5, 223) == 5);
	assert (fx25_pick_mode (100+5, 224) == -1);

	assert (fx25_pick_mode (100+9, 191) == 9);
	assert (fx25_pick_mode (100+9, 192) == -1);

	assert (fx25_pick_mode (16, 32) == 4);
	assert (fx25_pick_mode (16, 64) == 3);
	assert (fx25_pick_mode (16, 128) == 2);
	assert (fx25_pick_mode (16, 239) == 1);
	assert (fx25_pick_mode (16, 240) == -1);

	assert (fx25_pick_mode (32, 32) == 8);
	assert (fx25_pick_mode (32, 64) == 7);
	assert (fx25_pick_mode (32, 128) == 6);
	assert (fx25_pick_mode (32, 223) == 5);
	assert (fx25_pick_mode (32, 234) == -1);

	assert (fx25_pick_mode (64, 64) == 11);
	assert (fx25_pick_mode (64, 128) == 10);
	assert (fx25_pick_mode (64, 191) == 9);
	assert (fx25_pick_mode (64, 192) == -1);

	assert (fx25_pick_mode (1, 32) == 4);
	assert (fx25_pick_mode (1, 33) == 3);
	assert (fx25_pick_mode (1, 64) == 3);
	assert (fx25_pick_mode (1, 65) == 6);
	assert (fx25_pick_mode (1, 128) == 6);
	assert (fx25_pick_mode (1, 191) == 9);
	assert (fx25_pick_mode (1, 223) == 5);
	assert (fx25_pick_mode (1, 239) == 1);
	assert (fx25_pick_mode (1, 240) == -1);

}  // fx25_init

// Get properties of specified CTAG number.

struct rs *Rs::fx25_get_rs (int ctag_num)
{
	assert (ctag_num >= CTAG_MIN && ctag_num <= CTAG_MAX);
	assert (tags[ctag_num].itab >= 0 && tags[ctag_num].itab < NTAB);
	assert (Tab[tags[ctag_num].itab].rs != NULL);
	return (Tab[tags[ctag_num].itab].rs);
}

uint64_t Rs::fx25_get_ctag_value (int ctag_num)
{
	assert (ctag_num >= CTAG_MIN && ctag_num <= CTAG_MAX);
	return (tags[ctag_num].value);
}

int Rs::fx25_get_k_data_radio (int ctag_num)
{
	assert (ctag_num >= CTAG_MIN && ctag_num <= CTAG_MAX);
	return (tags[ctag_num].k_data_radio);
}

int Rs::fx25_get_k_data_rs (int ctag_num)
{
	assert (ctag_num >= CTAG_MIN && ctag_num <= CTAG_MAX);
	return (tags[ctag_num].k_data_rs);
}

int Rs::fx25_get_nroots (int ctag_num)
{
	assert (ctag_num >= CTAG_MIN && ctag_num <= CTAG_MAX);
	return (Tab[tags[ctag_num].itab].nroots);
}

int Rs::fx25_get_debug (void)
{
	return (g_debug_level);
}

/*-------------------------------------------------------------
 *
 * Name:	fx25_pick_mode
 *
 * Purpose:	Pick suitable transmission format based on user preference
 *		and size of data part required.
 *
 * Inputs:	fx_mode	- 0 = none.
 *			1 = pick a tag automatically.
 *			16, 32, 64 = use this many check bytes.
 *			100 + n = use tag n.
 *
 *			0 and 1 would be the most common.
 *			Others are mostly for testing.
 *
 *		dlen - 	Required size for transmitted "data" part, in bytes.
 *			This includes the AX.25 frame with bit stuffing and a flag
 *			pattern on each end.
 *
 * Returns:	Correlation tag number in range of CTAG_MIN thru CTAG_MAX.
 *		-1 is returned for failure.
 *		The caller should fall back to using plain old AX.25.
 *
 *--------------------------------------------------------------*/

int Rs::fx25_pick_mode (int fx_mode, int dlen)
{
	if (fx_mode <= 0) return (-1);

// Specify a specific tag by adding 100 to the number.
// Fails if data won't fit.

	if (fx_mode - 100 >= CTAG_MIN && fx_mode - 100 <= CTAG_MAX) {
	  if (dlen <= fx25_get_k_data_radio(fx_mode - 100)) {
	    return (fx_mode - 100);
	  }
	  else {
	    return (-1);	// Assuming caller prints failure message.
	  }
	}

// Specify number of check bytes.
// Pick the shortest one that can handle the required data length.

	else if (fx_mode == 16 || fx_mode == 32 || fx_mode == 64) {
	  for (int k = CTAG_MAX; k >= CTAG_MIN; k--) {
	    if (fx_mode == fx25_get_nroots(k) && dlen <= fx25_get_k_data_radio(k)) {
	      return (k);
	    }
	  }
	  return (-1);
	}

// For any other number, [[ or if the preference was not possible, ?? ]]
// try to come up with something reasonable.  For shorter frames,
// use smaller overhead.  For longer frames, where an error is
// more probable, use more check bytes.  When the data gets even
// larger, check bytes must be reduced to fit in block size.
// When all else fails, fall back to normal AX.25.
// Some of this is from observing UZ7HO Soundmodem behavior.
//
//	Tag 	Data 	Check 	Max Num
//	Number	Bytes	Bytes	Repaired
//	------	-----	-----	-----
//	0x04	32	16	8
//	0x03	64	16	8
//	0x06	128	32	16
//	0x09	191	64	32
//	0x05	223	32	16
//	0x01	239	16	8
//	none	larger		
//
// The PRUG FX.25 TNC has additional modes that will handle larger frames
// by using multiple RS blocks.  This is a future possibility but needs
// to be coordinated with other FX.25 developers so we maintain compatibility.

	static const int prefer[6] = { 0x04, 0x03, 0x06, 0x09, 0x05, 0x01 };
	for (int k = 0; k < 6; k++) {
	  int m = prefer[k];
	  if (dlen <= fx25_get_k_data_radio(m)) {
	    return (m);
	  }
	}
	return (-1);

// TODO: revisit error messages, produced by caller, when this returns -1.

}


/* Initialize a Reed-Solomon codec
 *   symsize = symbol size, bits (1-8) - always 8 for this application.
 *   gfpoly = Field generator polynomial coefficients
 *   fcr = first root of RS code generator polynomial, index form
 *   prim = primitive element to generate polynomial roots
 *   nroots = RS code generator polynomial degree (number of roots)
 */

struct rs *Rs::INIT_RS(unsigned int symsize,unsigned int gfpoly,unsigned fcr,unsigned prim,
		unsigned int nroots){
  struct rs *rs;
  int i, j, sr,root,iprim;

  if(symsize > 8*sizeof(DTYPE))
    return NULL; /* Need version with ints rather than chars */

  if(fcr >= (1<<symsize))
    return NULL;
  if(prim == 0 || prim >= (1<<symsize))
    return NULL;
  if(nroots >= (1<<symsize))
    return NULL; /* Can't have more roots than symbol values! */

  rs = (struct rs *)calloc(1,sizeof(struct rs));
  rs->mm = symsize;
  rs->nn = (1<<symsize)-1;

  rs->alpha_to = (DTYPE *)malloc(sizeof(DTYPE)*(rs->nn+1));
  if(rs->alpha_to == NULL){
    free(rs);
    return NULL;
  }
  rs->index_of = (DTYPE *)malloc(sizeof(DTYPE)*(rs->nn+1));
  if(rs->index_of == NULL){
    free(rs->alpha_to);
    free(rs);
    return NULL;
  }

  /* Generate Galois field lookup tables */
  rs->index_of[0] = A0; /* log(zero) = -inf */
  rs->alpha_to[A0] = 0; /* alpha**-inf = 0 */
  sr = 1;
  for(i=0;i<rs->nn;i++){
    rs->index_of[sr] = i;
    rs->alpha_to[i] = sr;
    sr <<= 1;
    if(sr & (1<<symsize))
      sr ^= gfpoly;
    sr &= rs->nn;
  }
  if(sr != 1){
    /* field generator polynomial is not primitive! */
    free(rs->alpha_to);
    free(rs->index_of);
    free(rs);
    return NULL;
  }

  /* Form RS code generator polynomial from its roots */
  rs->genpoly = (DTYPE *)malloc(sizeof(DTYPE)*(nroots+1));
  if(rs->genpoly == NULL){
    free(rs->alpha_to);
    free(rs->index_of);
    free(rs);
    return NULL;
  }
  rs->fcr = fcr;
  rs->prim = prim;
  rs->nroots = nroots;

  /* Find prim-th root of 1, used in decoding */
  for(iprim=1;(iprim % prim) != 0;iprim += rs->nn)
    ;
  rs->iprim = iprim / prim;

  rs->genpoly[0] = 1;
  for (i = 0,root=fcr*prim; i < nroots; i++,root += prim) {
    rs->genpoly[i+1] = 1;

    /* Multiply rs->genpoly[] by  @**(root + x) */
    for (j = i; j > 0; j--){
      if (rs->genpoly[j] != 0)
	rs->genpoly[j] = rs->genpoly[j-1] ^ rs->alpha_to[modnn(rs,rs->index_of[rs->genpoly[j]] + root)];
      else
	rs->genpoly[j] = rs->genpoly[j-1];
    }
    /* rs->genpoly[0] can never be zero */
    rs->genpoly[0] = rs->alpha_to[modnn(rs,rs->index_of[rs->genpoly[0]] + root)];
  }
    /* convert rs->genpoly[] to index form for quicker encoding */
  for (i = 0; i <= nroots; i++) {
    rs->genpoly[i] = rs->index_of[rs->genpoly[i]];
  }
  
// diagnostic prints
/*
  printf("Alpha To:\n\r");
  for (i=0; i < sizeof(DTYPE)*(rs->nn+1); i++) 
    printf("0x%2x,", rs->alpha_to[i]);
  printf("\n\r");

  printf("Index Of:\n\r");
  for (i=0; i < sizeof(DTYPE)*(rs->nn+1); i++) 
    printf("0x%2x,", rs->index_of[i]);
  printf("\n\r");
  
  printf("GenPoly:\n\r");
  for (i = 0; i <= nroots; i++) 
    printf("0x%2x,", rs->genpoly[i]);
  printf("\n\r");
*/
  return rs;
}

void Rs::fx_hex_dump (unsigned char *p, int len) 
{
	int n, i, offset;

	offset = 0;
	while (len > 0) {
	  n = len < 16 ? len : 16; 
	  printf ("  %03x: ", offset);
	  for (i=0; i<n; i++) {
	    printf (" %02x", p[i]);
	  }
	  for (i=n; i<16; i++) {
	    printf ("   ");
	  }
	  printf ("  ");
	  for (i=0; i<n; i++) {
	    printf ("%c", isprint(p[i]) ? p[i] : '.');
	  }
	  printf ("\n");
	  p += 16;
	  offset += 16;
	  len -= 16;
	}
}

void Rs::ENCODE_RS(struct rs * rs, DTYPE * data, DTYPE * bb)
{

  int i, j;
  DTYPE feedback;

  memset(bb,0,NROOTS*sizeof(DTYPE)); // clear out the FEC data area

  for(i=0;i<NN-NROOTS;i++){
    feedback = INDEX_OF[data[i] ^ bb[0]];
    if(feedback != A0){      /* feedback term is non-zero */
      for(j=1;j<NROOTS;j++)
	    bb[j] ^= ALPHA_TO[MODNN(feedback + GENPOLY[NROOTS-j])];
    }
    /* Shift */
    memmove(&bb[0],&bb[1],sizeof(DTYPE)*(NROOTS-1));
    if(feedback != A0)
      bb[NROOTS-1] = ALPHA_TO[MODNN(feedback + GENPOLY[0])];
    else
      bb[NROOTS-1] = 0;
  }
}
