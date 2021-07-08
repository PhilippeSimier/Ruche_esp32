#ifndef SCAN_H
#define SCAN_H

#include <Arduino.h>

class Scan {
  
public:
    Scan();
    
   static float lireFloat();
   static int lireInt();
   static String lireString();
   static void confirmer();
   static void lireTabChar(char* buffer, int lenght);

private:
   
  
};


#endif /* SCAN_H */
