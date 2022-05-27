#include <stdlib.h>
#include <time.h>

float getRandFloat(){
float randDeviate;
randDeviate = ((float)rand( ) / (float)RAND_MAX);
return randDeviate;
}

int getRandExponential(){
float x, deviate;
x = getRandFloat( );
if (x == 0.0)
      deviate = 0.0;
else if (x <= 0.1)
        deviate = ((x - 0.0) * 1.04 + 0.0);
else if (x <= 0.2)
        deviate = ((x - 0.1) * 1.18 + 0.104);
else if (x <= 0.3)
        deviate = ((x - 0.2) * 1.33 + 0.222);
else if (x <= 0.4)
        deviate = ((x - 0.3) * 1.54 + 0.355);
else if (x <= 0.5)
        deviate = ((x - 0.4) * 1.81 + 0.509);
else if (x <= 0.6)
        deviate = ((x - 0.5) * 2.25 + 0.690);
else if (x <= 0.7)
        deviate = ((x - 0.6) * 2.85 + 0.915);
else if (x <= 0.75)
        deviate =  ((x - 0.70) * 3.60 + 1.2);
else if (x <= 0.8)
        deviate =  ((x - 0.75) * 4.40 + 1.38);
else if (x <= 0.84)
        deviate =  ((x - 0.8) * 5.75 + 1.60);
else if (x <= 0.88)
        deviate =  ((x - 0.84) * 7.25 + 1.83);
else if (x <= 0.9)
        deviate =  ((x - 0.88) * 9.00 + 2.12);
else if (x <= 0.92)
        deviate =  ((x - 0.90) * 11.0 + 2.30);
else if (x <= 0.94)
        deviate =  ((x - 0.92) * 14.5 + 2.52);
else if (x<= 0.95)
        deviate =  ((x - 0.94) * 18.0 + 2.81);
else if (x <= 0.96)
        deviate =  ((x - 0.95) * 21.0 + 2.99);
else if (x <= 0.97)
        deviate =  ((x - 0.96) * 30.0 + 3.20);
else if (x <= 0.98)
        deviate =  ((x - 0.97) * 40.0 + 3.50);
else if (x <= 0.99)
        deviate =  ((x - 0.98) * 70.0 + 3.90);
else if (x <= 0.995)
        deviate =  ((x - 0.99) * 140.0 + 4.60);
else if (x <= 0.998)
        deviate =  ((x - 0.995) * 300.0 + 5.30);
else if (x <= 0.999)
        deviate =  ((x - 0.998) * 800.0 + 6.20);
else
        deviate =  ((x - 0.9997) * 1000.0 + 8.0);

return (float)deviate;
}







void seedRandGenerator(){

time_t seed;
seed = time(NULL);
srand(seed);
return;
