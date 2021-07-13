/* 
 * File:   trame.h
 * Author: philippe
 *
 * Created on 12 juillet 2021, 12:06
 */

#ifndef TRAME_H
#define TRAME_H

typedef struct {
  int16_t poids;
  int16_t temperature;
  
  unsigned char humidite;
  unsigned char type;
} trameMesure;


#endif /* TRAME_H */

