    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Array.cpp                   //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____** | *****|SnowStorm|************************//
//**+ *+ *+ *+ **|*****************************|****** | ****************************************//
//*+ *+ *+ *+ ***\___ ** ___ ** ___ **|*****|**\___ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|** | **|***|**|***\**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***____/**|***|**\___/***\/ \/***____/** \_**\___/**|******|**|**|** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Array.h"

#include <ostream>

using namespace ylife;

		/* Array: public */

json::Array::Array() :
	content_()
{}

json::Array::Array(Array&& array) :
	content_(std::move(array.content_))
{}

json::EType json::Array::get_type() const
{
	return EType::ARRAY;
}

void json::Array::to_stream(std::wostream& stream, int nesting) const
{
	stream << L'[';
	bool is_first = true;
	for (const auto& i : content_)
	{
		if (!is_first)
		{
			stream << L',';
		}
		stream << L' ';
		i->to_stream(stream, nesting + 1);
		is_first = false;
	}
	stream << L" ]";
}

std::vector<std::shared_ptr<json::Element>>& json::Array::get_content() noexcept
{
	return content_;
}

const std::vector<std::shared_ptr<json::Element>>& json::Array::get_content() const noexcept
{
	return content_;
}
