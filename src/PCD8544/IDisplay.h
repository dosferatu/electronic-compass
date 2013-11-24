#include "PCD8544.h"

class IDisplay : PCD8544
{
  public:
    virtual ~IDisplay();
    void InitDisplay();
    void DisplayHeading(int);

  private:
};
