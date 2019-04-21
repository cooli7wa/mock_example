#include <iostream>
#include "target.h"

void normal_func(void) {
  std::cout << "origin normal func called" << std::endl;
}

void normal_func1(void) {
  std::cout << "origin normal func1 called" << std::endl;
}

A::A(std::string name): name_(name), num_(0) {
}

void A::class_func(void) {
  std::cout << "origin class func called, name is " << name_ << std::endl;
}

int A::class_add(int a) {
  std::cout << "origin class add called" << std::endl;
  num_ += a;
  return num_;
}

int A::class_call(void) {
  std::cout << "origin class call called" << std::endl;
  normal_func();
  normal_func1();
  return 0;
}

