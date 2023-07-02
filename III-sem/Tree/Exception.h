#pragma once
#include <string.h>

enum ErrorCodes
{
   MEMORY = -2,
   UNKNOWN = -1,
   OK = 0
};

class MyException
{
private:
   char message[256];
   int code;

public:
   MyException(const char *msg, int c)
   {
      code = c;
      strncpy(message, msg, 255);
   }
   const char *Message() const { return message; }
   int Code() const { return code; }
};