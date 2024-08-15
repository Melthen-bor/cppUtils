#ifndef NUMBERS_LOADED
#define NUMBERS_LOADED
#ifdef ROOTS
#include "flags.h"
class byte_with_check{
  unsigned char byte;
  flags checks;
public:
  byte_with_check(){
    this->byte=0;
    this->checks=flags();
  }
  byte_with_check(unsigned char value){
    this->byte=value;
    this->checks=flags();
    this->checks.store(0,1);
    this->checks.store(1,1);
  }
  byte_with_check(char value){
    this->byte=(unsigned char)value;
    this->checks=flags();
    this->checks.store(0,1);
  }
  byte_with_check(signed char value){
    this->byte=(unsigned char)value;
    this->checks=flags();
    this->checks.store(0,1);
    this->checks.store(1,1);
    this->checks.store(2,1);
  }
  bool is_number(){
    return this->checks.read(1);
  }
  bool sign(){
    return this->checks.read(2);
  }
  bool exists(){
    return this->checks.read(0);
  }
  char as_character(){
    if((!this->is_number())&&this->exists()){
      return (char)this->byte;
    }
  }
  unsigned char as_unsigned(){
    if(this->is_number()&&(!this->sign())&&this->exists()){
      return this->byte;
    }
  }
  signed char as_signed(){
    if(this->is_number()&&this->sign()&&this->exists()){
      return this->byte;
    }
  }
  unsigned char& get(){
    return this->byte;
  }
};
class short_with_check{
  unsigned short value;
  flags checks;
public:
  short_with_check(){
    this->value=0;
    this->checks=flags();
  }
  short_with_check(unsigned short val){
    this->value=val;
    this->checks=flags();
    this->checks.store(0,1);
  }
  short_with_checks(short val){
    this->value=val;
    this->checks=flags();
    this->checks.store(0,1);
    this->checks.store(1,1);
  }
};
#endif
#endif
