#include <iostream>
#include "target.h"

// mock funcs, these mock funcs will replace origin funcs
void A::class_func(void) {
  std::cout << "mock class func called" << std::endl;
}

void normal_func(void) {
  std::cout << "mock normal func called" << std::endl;
}

// origin funcs, these funcs will be created in objcopy flow
extern void class_func_origin(A a);
extern void normal_func_origin(void);

int main() {
  A a("lucky");
  // mock class func
  a.class_func();
  // origin class func
  class_func_origin(a);
  // mock normal func
  normal_func();
  // origin normal func
  normal_func_origin();
}
