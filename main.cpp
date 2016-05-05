#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

using namespace std;

int isPowerOfTwo (int x);   //prototype for function to determine if parameter is a power of two

int main() {

    ifstream encodedMessage;
    encodedMessage.open("packets.dat");


    if(encodedMessage.is_open()) {

        while (!encodedMessage.eof()) {

            //declaring variables in while loop initializes each variable for each iteration of the loop
            char packet[14];
            char grayCode[9];
            int binaryCode[9];
            int errorBit = 0;
            int grayCounter = 0;
            int oddOnes = 0;
            int decimalValue = 0;
            char character = 0;

            //read a packet
            encodedMessage >> packet;

            //determine if an error has occurred in transmission
            //if the parity for bit 1 is odd, an error has occurred
            if((packet[0] + packet [2] + packet[4] + packet[6] + packet[8] + packet[10] + packet[12]) % 2 != 0)
                errorBit += 1;
            //if the parity for bit 2 is odd, an error has occurred
            if((packet[1] + packet[2] + packet[5] + packet[6] + packet[9] + packet[10]) % 2 != 0)
                errorBit += 2;
            //if the parity for bit 4 is odd, an error has occurred
            if((packet[3] + packet [4] + packet[5] + packet[6] + packet[11] + packet[12]) % 2 != 0)
                errorBit += 4;
            //if the parity for bit 8 is odd, an error has occurred
            if((packet[7] + packet[8] + packet[9] + packet[10] + packet [11] + packet[12]) % 2 != 0)
                errorBit += 8;


            //fix any error, flip the value of the error bit
                if (packet[errorBit] == '1')
                    packet[errorBit] = '0';
                else
                    packet[errorBit] = '1';


            //extract the gray code message from Hamming
            /*Gray code will compose of all bit positions that are not a
             * power of two, as these are the Hamming code's parity bits*/
            for(int i = 0; i < strlen(packet); i++) {
                if(!isPowerOfTwo(i)) {    //determine if bit should be extracted for gray code
                    grayCode[grayCounter] = packet[i];  //use new counter to compensate for shorter string
                    grayCounter++;  //increment counter for gray code, keeping separate from i due to if statement in loop
                }
            }


            //convert to binary from gray
            /*Copy first value, look to left of current value flipping
             * if number of 1s is odd. Keep value if number of 1s is even*/
            binaryCode[0] = grayCode[0];
            for(int i = 1; i < strlen(grayCode); i ++){
                if(grayCode[i-1] == '1')    //keep track of number of 1's to the left of current value
                    oddOnes++;
                if(oddOnes % 2 == 0 || oddOnes == 0)    //if even
                    binaryCode[i] = grayCode[i];            //copy value
                else {                                  //else if odd
                    if (grayCode[i] == '1')                 //invert value
                        binaryCode[i] = 0;
                    if (grayCode[i] == '0')
                        binaryCode[i] = 1;
                }
            }


            //convert binary to decimal
            for(int i = 0; i < 9; i++){
                if(binaryCode[i] == 1)
                    decimalValue += pow(2,i); //raise 2 to the power of bit position and sum into value
            }
            character = (decimalValue-127); //cast decimal value to char

            //print character
            cout << character;

        }
        encodedMessage.close();
    }
    return(0);
}

int isPowerOfTwo (int x)
{
    while (((x % 2) == 0) && x > 1)
        x /= 2;
    return (x == 1);
}