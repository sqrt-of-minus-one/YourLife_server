    ////////////////////////////////////////
   //       YourLife by SnegirSoft       //
  //                                    //
 //  File: Game.h                      //
////////////////////////////////////////

#pragma once

#include <memory>

namespace ylife
{

class World;

class Game
{
	
private:
	std::unique_ptr<World> world_;
};

}
