#pragma once

#include <exception>

class FileNotFoundException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "File Not Found";
  }
};

class CannotDetermineFileSizeException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Cannot Determine File Size";
  }
};

