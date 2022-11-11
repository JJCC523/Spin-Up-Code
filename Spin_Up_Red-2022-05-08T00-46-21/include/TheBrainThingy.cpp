#include "vex.h"
#include "string"

using namespace vex;



class gui {



public:
class thatthingyoupress;
public:
class flippityfloppity;
public:
void clrscrn() {
  Brain.Screen.clearScreen();
  
}
  
};

class gui::thatthingyoupress {

  int x;
  int y;
   

  public :
  thatthingyoupress(int x, int y) {
    
    this->x = x;
    this->y = y;
    std::string s = "hi";
    Brain.Screen.setPenWidth(1);
    Brain.Screen.setPenColor(white);
    Brain.Screen.drawRectangle(x,y, 50, 50);
    // Brain.Screen.setCursor(x/10+2, y/10+2);
    // Brain.Screen.print("hi");


  }
  public:
  void p() {
    
    Brain.Screen.setPenColor(red);
    Brain.Screen.drawRectangle(x+10,y+10,30,30);
  }
  void poff() {
    
    Brain.Screen.setPenColor(transparent);
    Brain.Screen.drawRectangle(x+10,y+10,30,30);
  }

  public: bool pressed() {
    if (Brain.Screen.pressing()) {
    if (Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x +50 && Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y +50) {
      return true;
      
    }
    else {
      return false;
    }

  }
  else {
    return false;
  }

  }
  




};

class gui::flippityfloppity {
  int x;
  int y;
  int c;

  public :
  flippityfloppity(int x, int y) {
    
    this->x = x;
    this->y = y;
    

    Brain.Screen.drawRectangle(x,y,c*2, 5);
    Brain.Screen.setCursor(x - c/2 +4, y-2.5);
    Brain.Screen.print("text");


  }
};

