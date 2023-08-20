    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Value.cpp                   //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____** | *****|SnowStorm|************************//
//**+ *+ *+ *+ **|*****************************|****** | ****************************************//
//*+ *+ *+ *+ ***\___ ** ___ ** ___ **|*****|**\___ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|** | **|***|**|***\**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***____/**|***|**\___/***\/ \/***____/** \_**\___/**|******|**|**|** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Value.h"

using namespace ylife;

template<>
json::EType json::snow_::type_<std::wstring>() noexcept
{
	return EType::STRING_VALUE;
}

template<>
json::EType json::snow_::type_<int>() noexcept
{
	return EType::INT_VALUE;
}

template<>
json::EType json::snow_::type_<double>() noexcept
{
	return EType::DOUBLE_VALUE;
}

template<>
json::EType json::snow_::type_<bool>() noexcept
{
	return EType::BOOL_VALUE;
}

template<>
json::EType json::snow_::type_<std::nullptr_t>() noexcept
{
	return EType::NULL_VALUE;
}

template<>
std::wstring json::snow_::to_string_<std::wstring>(const std::wstring& val)
{
	return L'"' + Element::escape(val) + L'"';
}

template<>
std::wstring json::snow_::to_string_<int>(const int& val)
{
	return std::to_wstring(val);
}

template<>
std::wstring json::snow_::to_string_<double>(const double& val)
{
	return std::to_wstring(val);
}

template<>
std::wstring json::snow_::to_string_<bool>(const bool& val)
{
	return val ? L"true" : L"false";
}

template<>
std::wstring json::snow_::to_string_<std::nullptr_t>(const std::nullptr_t& val)
{
	return L"null";
}

		/* Value_<std::nullptr_t>: public */

json::snow_::Value_<std::nullptr_t>::Value_()
{}

json::EType json::snow_::Value_<std::nullptr_t>::get_type() const
{
	return EType::NULL_VALUE;
}

void json::snow_::Value_<std::nullptr_t>::to_stream(std::wostream& stream, int nesting) const
{
	stream << L"null";
}

std::shared_ptr<json::snow_::Value_<std::nullptr_t>> json::snow_::Value_<std::nullptr_t>::make()
{
	return std::make_shared<NullValue>();
}
