#ifndef EXIT
#define EXIT

namespace Exit
{
  //----------------------------------------------------------------------------
  // CODE Class
  // list of Enums to distinguish different Exit Code Returns
  //
  enum class Code
  {
    SUCCESS = 0,
    OUT_OF_MEMORY = 1,
    WRONG_USAGE = 2
  };
}

#endif // EXIT

