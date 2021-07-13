/* 
 * File:   trame.h
 * Author: philippe
 *
 * Created on 12 juillet 2021, 12:06
 */

#ifndef TRAME_H
#define TRAME_H

typedef struct {
    short field1;
    short field2;
    short field3;
    unsigned short field5;
    short field6;
    unsigned char field4;
    char type = 1;
} trameMesure;


#endif /* TRAME_H */

