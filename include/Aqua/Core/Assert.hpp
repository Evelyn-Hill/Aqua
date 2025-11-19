#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

namespace Aqua {
class CustomAssert {
public:
  static void handle_failure(const std::string &expression,
                             const std::string &message,
                             const std::string &file, int line,
                             const std::string &function) {
    std::cerr << "=== AQ ASSERT FAILED! === " << std::endl << std::endl;
    std::cerr << expression << std::endl;
    if (!message.empty()) {
      std::cerr << "Message: " << message << std::endl;
    }
    std::cerr << "File: " << file << ", Line: " << line
              << ", Function: " << function << std::endl;

    // TODO: Make this crossplatform with our own window.
    MessageBox(NULL, 
               message.c_str(),
               "AQ Assert failed!",
               MB_ICONERROR | MB_OK
            );

    std::abort();
  }
};

#define ASSERT(condition, message)                                             \
  do {                                                                         \
    if (!(condition)) {                                                        \
      CustomAssert::handle_failure(#condition, message, __FILE__, __LINE__,    \
                                   __func__);                                  \
    }                                                                          \
  } while (0)
}
