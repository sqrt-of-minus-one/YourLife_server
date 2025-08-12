    ////////////////////////////////////////
   //        YourLife by sqrt(-1)        //
  //                                    //
 //  File: Command.h                   //
////////////////////////////////////////

#pragma once

#include <memory>

namespace ylife
{

class Player;

struct Command
{
	enum ECommand
	{

	};

	std::shared_ptr<Player> player;

	virtual ECommand get_type() const = 0;
};

}
