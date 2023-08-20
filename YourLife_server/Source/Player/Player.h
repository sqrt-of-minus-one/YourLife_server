    ////////////////////////////////////////
   //       YourLife by SnegirSoft       //
  //                                    //
 //  File: Player.h                    //
////////////////////////////////////////

#pragma once

#include <string>

namespace ylife
{

enum class EGender
{
	MALE,
	FEMALE
};

class Player
{

private:
	std::wstring login_;
	std::wstring name_;
	std::wstring surname_;
	EGender gender_;
};

}
