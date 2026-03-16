#include <iostream>
#include <algorithm>
#include <memory>
#include "MyString.h"
using namespace std;

class String {
   using string = emcpp::MyString;
//    using string = std::string;

/// Store a pointer to dynamically allocated string!
   shared_ptr<string> ptr;

public:
    String(): ptr(make_shared<string>()) {}     /// creates an empty string
    String(const char * str) : ptr(make_shared<string>(str)) {}          /// copy C-string
    String(const String & str) : ptr(str.ptr) {}            /// no copy
    String operator=(const String & s) {
      if (this != &s)
        ptr = s.ptr;
      return *this;
    } /// no copy

    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch) {
      if (ptr.use_count() > 1) {
        ptr = make_shared<string>(*ptr);
      }
      (*ptr)[index] = ch; 
    };
    /// no copy
    char get(int index) const {
      return (*ptr)[index];
    };
    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b) {
      if(!a.ptr || a.ptr->empty()) return b;
      if(!b.ptr || b.ptr->empty()) return a;

      return String((*a.ptr + *b.ptr).c_str());
    }

    friend std::ostream & operator<< (std::ostream & out, String s) {
      return out << *s.ptr;
    }
};
