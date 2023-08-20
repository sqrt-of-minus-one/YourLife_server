    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: JsonObject.cpp              //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____** | *****|SnowStorm|************************//
//**+ *+ *+ *+ **|*****************************|****** | ****************************************//
//*+ *+ *+ *+ ***\___ ** ___ ** ___ **|*****|**\___ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|** | **|***|**|***\**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***____/**|***|**\___/***\/ \/***____/** \_**\___/**|******|**|**|** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "JsonObject.h"

using namespace ylife;

		/* JsonObject: public */

json::JsonObject::JsonObject() :
	content_()
{}

json::JsonObject::JsonObject(JsonObject&& object) :
	content_(std::move(object.content_))
{}

json::EType json::JsonObject::get_type() const
{
	return EType::OBJECT;
}

void json::JsonObject::to_stream(std::wostream& stream, int nesting) const
{
	wchar_t* tab = new wchar_t[nesting + 2];
	for (int i = 0; i < nesting + 1; i++)
	{
		tab[i] = '\t';
	}
	tab[nesting + 1] = '\0';
	
	stream << L'{';
	bool is_first = true;
	for (const auto& [k, v] : content_)
	{
		stream << (is_first ? L"\n" : L",\n") << tab << L'"' << escape(k) << L"\": ";
		v->to_stream(stream, nesting + 1);
		is_first = false;
	}
	
	if (!is_first)
	{
		stream << L'\n' << (tab + 1);
	}
	stream << L'}';
}

std::map<std::wstring, std::shared_ptr<json::Element>>& json::JsonObject::get_content() noexcept
{
	return content_;
}

const std::map<std::wstring, std::shared_ptr<json::Element>>& json::JsonObject::get_content() const noexcept
{
	return content_;
}
