#include "utils.h"

String numberToTwoChars(int number){
  if(number<10){
    return "0"+String(number);
  } else {
    return String(number);
  }
}