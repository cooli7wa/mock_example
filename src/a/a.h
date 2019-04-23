#pragma once

class A {
public:
  A(std::string name);
  void class_func(void);
  int class_add(int a);
  int class_call(void);
private:
  int num_;
  std::string name_;
};

