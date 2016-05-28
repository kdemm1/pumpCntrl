/*
  Author: Kyle Demmerle
  Project: CRC Generator for Infusion Pump Control - Source File
  Supervisor: Taimoore Rajah
  Date: 4/1/16
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
using namespace std;

#define GEN_POLY 0x8408
#define BYTE_SIZE 8

uint8_t shiftRight(uint8_t b, bool e, bool C){
  if(e) b = (b-1)/2;
  else  b = b/2;
  
  if(C) b = b + 128;
  
  return b;
};

bool evenTest(uint8_t b){
  uint8_t a = b/2;

  if(a*2 == b)
    return false;
  else
    return true;
};

void generateCRC(string test, unsigned int* crcVal){
  //string test = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x49\x0D\x0A";

  uint8_t polyH = 0x84;
  uint8_t polyL = 0x8;
  uint8_t crcH = 0xFF;
  uint8_t crcL = 0xFF;
  uint8_t y; //for individual chars
  int i, x; //iterator
  bool e1;
  bool e2;
  
  for(i = 0; (unsigned) i < test.size(); i++){
    y = test[i];
    for(x = 0; x < BYTE_SIZE; x++){
      e1 = evenTest(crcH);
      crcH = shiftRight(crcH, e1, false);
      e2 = evenTest(crcL);
      crcL = shiftRight(crcL, e2, e1);
      e1 = evenTest(y);
      y = shiftRight(y, e1, false);
      if(e1 ^ e2){
	crcL = crcL ^ polyL;
	crcH = crcH ^ polyH;
      }
    }
  }
  
  crcVal[0] = crcL;
  crcVal[1] = crcH;

};

unsigned int buildMsg(string msg, unsigned int* crc){
  stringstream ss;
  string fmsg;

  ss << '\xA8' << msg << hex << crc[0] << hex << crc[1] << '\xA8';
  fmsg = ss.str();

  for(int i = 0; i < (int) fmsg.size(); i++){
    cout << hex << fmsg[i];
  }
  
  cout << endl;

  return 0;
};

void printMenu(){
  cout << "--------------------------------" << endl;
  cout << "| 1 | 2 | 3 |    Y    |    N   |" << endl;
  cout << "--------------------------------" << endl;
  cout << "| 4 | 5 | 6 |         |        |" << endl;
  cout << "--------------------------------" << endl;
  cout << "| 7 | 8 | 9 |    B    |        |" << endl;
  cout << "--------------------------------" << endl;
  cout << "| . | 0 | I |         |    C   |" << endl;
  cout << "--------------------------------" << endl;
};

int main(void){
  //uint16_t crcVal;
   char input;
   string simMsg;
   unsigned int crcVal[2];

  printMenu();
  cout << "Please press a key: ";
  cin >> input;

  switch(input){
  case '0':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x30\x0D\x0A";
    break;
  case '1':
     simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x31\x0D\x0A";
     break;
  case '2':
     simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x32\x0D\x0A";
     break;
  case '3':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x33\x0D\x0A";
    break;
  case '4':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x34\x0D\x0A";
    break;
  case '5':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x35\x0D\x0A";
    break;
  case '6':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x36\x0D\x0A";
    break;
  case '7':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x37\x0D\x0A";
    break; 
 case '8':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x38\x0D\x0A";
    break;
  case '9':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x39\x0D\x0A";
    break;
  case '.':
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x50\x0D\x0A";
    break;
  case ('Y'):
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x52\x0D\x0A";
    break;
  case ('N'):
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x53\x0D\x0A";
    break;
  case ('I'):
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x49\x0D\x0A";
    break;
  case ('B'):
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x42\x0D\x0A";
    break;
  case ('C'):
    simMsg = "\x1B\x54\x20\x33\x31\x39\x35\x37\x0D\x0A\x4B\x43\x0D\x0A";
    break;
  }

  generateCRC(simMsg, crcVal);
  buildMsg(simMsg, crcVal);
  //cout << "CRC: " << hex << crcVal[0] << hex << crcVal[1] << endl;
  //cout << hex << "Generated CRC-CCITT Value: " << crcVal << endl;
};

