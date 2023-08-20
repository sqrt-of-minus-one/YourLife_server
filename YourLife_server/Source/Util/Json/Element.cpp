    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Element.cpp                 //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____** | *****|SnowStorm|************************//
//**+ *+ *+ *+ **|*****************************|****** | ****************************************//
//*+ *+ *+ *+ ***\___ ** ___ ** ___ **|*****|**\___ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|** | **|***|**|***\**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***____/**|***|**\___/***\/ \/***____/** \_**\___/**|******|**|**|** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Element.h"

#include <cwctype>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "JsonObject.h"
#include "Array.h"
#include "Value.h"

using namespace ylife;

		/* Element: public */

std::wstring json::Element::to_string() const
{
	std::wostringstream stream;
	to_stream(stream);
	return stream.str();
}

void json::Element::save(const std::wstring& filename, bool allow_override) const
{
	if (!std::filesystem::exists(filename))
	{
		std::filesystem::create_directories(filename);
	}
	else if (!allow_override)
	{
		throw std::runtime_error("The file with the same name already exists");
	}

	std::wofstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("The file couldn't be created or accessed");
	}
	to_stream(file);
	file.close();
}

std::shared_ptr<json::Element> json::Element::from_string(const std::wstring& string)
{
	std::wistringstream stream(string);
	return from_stream(stream);
}

std::shared_ptr<json::Element> json::Element::load(const std::wstring& filename)
{
	std::wifstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("The file does not exist or cannot be accessed");
	}
	return from_stream(file);
}

std::shared_ptr<json::Element> json::Element::from_stream(std::wistream& stream)
{
	wchar_t c;
	while (stream.read(&c, 1))
	{
		// Ignore space characters
		if (std::iswspace(c))
		{
			continue;
		}

		switch (c)
		{
		// The beginning of an object
		case L'{':
		{
			return read_object_(stream);
		}
		// The beginning of an array
		case L'[':
		{
			return read_array_(stream);
		}
		// The bebinning of a string value
		case L'"':
		case L'\'':
		{
			return std::make_shared<StringValue>(read_string_(stream, c));
		}
		// The beginning of an integer or double value
		case L'0':
		case L'1':
		case L'2':
		case L'3':
		case L'4':
		case L'5':
		case L'6':
		case L'7':
		case L'8':
		case L'9':
		case L'.':
		case L'-':
		case L'+':
		{
			return read_number_(stream, c);
		}
		// The beginning of the true boolean value
		case L't':
		case L'T':
		{
			if (!read_lit_(stream, L"true"))
			{
				throw std::invalid_argument("Invalid JSON");
			}
			return std::make_shared<BoolValue>(true);
		}
		// The beginning of the false boolean value
		case L'f':
		case L'F':
		{
			if (!read_lit_(stream, L"false"))
			{
				throw std::invalid_argument("Invalid JSON");
			}
			return std::make_shared<BoolValue>(false);
		}
		// The beginning of the null value
		case L'n':
		case L'N':
		{
			if (!read_lit_(stream, L"null"))
			{
				throw std::invalid_argument("Invalid JSON");
			}
			return std::make_shared<NullValue>();
		}
		// The beginning of a comment
		case L'/':
		{
			read_comment_(stream);
			break;
		}
		// JSON cannot have anything else => throw the exception
		default:
		{
			throw std::invalid_argument("Invalid JSON");
		}
		}
	}
	throw std::invalid_argument("Invalid JSON");
}

std::wstring json::Element::escape(const std::wstring& string)
{
	std::wstring result;
	for (wchar_t i : string)
	{
		switch (i)
		{
		case L'\'':
		{
			result += L"\\\'";
			break;
		}
		case L'\"':
		{
			result += L"\\\"";
			break;
		}
		case L'\\':
		{
			result += L"\\\\";
			break;
		}
		case L'\a':
		{
			result += L"\\\a";
			break;
		}
		case L'\b':
		{
			result += L"\\\b";
			break;
		}
		case L'\f':
		{
			result += L"\\\f";
			break;
		}
		case L'\n':
		{
			result += L"\\\n";
			break;
		}
		case L'\r':
		{
			result += L"\\\r";
			break;
		}
		case L'\t':
		{
			result += L"\\\t";
			break;
		}
		case L'\v':
		{
			result += L"\\\v";
			break;
		}
		default:
		{
			result += i;
		}
		}
	}
	return result;
}

std::wstring json::Element::unescape(const std::wstring& string)
{
	std::wstring result;
	for (int i = 0; i < string.length(); i++)
	{
		if (string[i] == L'\\' && i < string.length() - 1)
		{
			switch (string[++i])
			{
			case L'\'':
			{
				result += L'\'';
				break;
			}
			case L'\"':
			{
				result += L'\"';
				break;
			}
			case L'\\':
			{
				result += L'\\';
				break;
			}
			case L'a':
			{
				result += L'\a';
				break;
			}
			case L'b':
			{
				result += L'\b';
				break;
			}
			case L'f':
			{
				result += L'\f';
				break;
			}
			case L'n':
			{
				result += L'\n';
				break;
			}
			case L'r':
			{
				result += L'\r';
				break;
			}
			case L't':
			{
				result += L'\t';
				break;
			}
			case L'v':
			{
				result += L'\v';
				break;
			}
			default:
			{
				result += L'\\';
				i--;
			}
			}
		}
		else
		{
			result += string[i];
		}
	}
	return result;
}

std::shared_ptr<json::JsonObject> json::Element::read_object_(std::wistream& stream)
{
	std::shared_ptr<JsonObject> result = std::make_shared<JsonObject>();
	while (true)
	{
		wchar_t c = stream.peek();
		pass_(stream, c);
		if (c == L'}')
		{
			stream.get(c);
			return result;
		}
		
		// Read a key
		std::wstring key;
		if (c == L'"' || c == L'\'')
		{
			stream.get(c);
			key = read_string_(stream, c);
		}
		else
		{
			throw std::invalid_argument("Invalid JSON: invalid object, a key was expected");
		}
		
		c = stream.peek();
		pass_(stream, c);
		if (c != L':')
		{
			throw std::invalid_argument("Invalid JSON: invalid object, ':' was expected after the key");
		}
		stream.get(c);
		c = stream.peek();
		pass_(stream, c);
		
		result->get_content()[key] = from_stream(stream);
		
		c = stream.peek();
		pass_(stream, c);
		if (c == L'}')
		{
			stream.get(c);
			return result;
		}
		if (c == L',')
		{
			stream.get(c);
			continue;
		}
		throw std::invalid_argument("Invalid JSON: invalid object");
	}
}

std::shared_ptr<json::Array> json::Element::read_array_(std::wistream& stream)
{
	std::shared_ptr<Array> result = std::make_shared<Array>();
	while (true)
	{
		wchar_t c = stream.peek();
		pass_(stream, c);
		if (c == L']')
		{
			stream.get(c);
			return result;
		}
		
		result->get_content().push_back(from_stream(stream));
		
		c = stream.peek();
		pass_(stream, c);
		if (c == L']')
		{
			stream.get(c);
			return result;
		}
		if (c == L',')
		{
			stream.get(c);
			continue;
		}
		throw std::invalid_argument("Invalid JSON: invalid array");
	}
}

std::wstring json::Element::read_string_(std::wistream& stream, wchar_t first)
{
	wchar_t c;
	std::wstring str;
	bool escape = false;
	while (stream.get(c))
	{
		if (escape)
		{
			escape = false;
		}
		else
		{
			if (c == first)
			{
				return unescape(str);
			}
			if (c == L'\\')
			{
				escape = true;
			}
		}
		str += c;
	}
	throw std::invalid_argument("Invalid JSON: the string is not closed");
}

std::shared_ptr<json::Element> json::Element::read_number_(std::wistream& stream, wchar_t first)
{
	std::wstring result;
	wchar_t c = stream.peek();

	// Define the base
	int base = 10;
	if (first == L'0')
	{
		switch (c)
		{
		case L'x':
		case L'X':
		case L'h':
		case L'H':
		{
			base = 16;
			stream.get(c);
			c = stream.peek();
			break;
		}
		case L'b':
		case L'B':
		{
			base = 2;
			stream.get(c);
			c = stream.peek();
			break;
		}
		case L'o':
		case L'O':
		{
			base = 8;
			stream.get(c);
			c = stream.peek();
			break;
		}
		default:
		{
			result += first;
		}
		}
	}
	else
	{
		result += first;
	}

	bool has_point = false;
	while (c >= L'0' && c <= L'9' ||
		   c >= L'A' && c <= L'F' ||
		   c >= L'a' && c <= L'f' ||
		   c == L'.' || c == L'\'')
	{
		has_point |= c == L'.';
		result += c;
		stream.get(c);
		c = stream.peek();
	}
	
	try
	{
		switch (base)
		{
		case 2:
		{
			return std::make_shared<IntValue>(std::stoi(result, nullptr, 2));
		}
		case 8:
		{
			return std::make_shared<IntValue>(std::stoi(result, nullptr, 8));
		}
		case 10:
		{
			if (has_point)
			{
				return std::make_shared<DoubleValue>(std::stod(result));
			}
			return std::make_shared<IntValue>(std::stoi(result));
		}
		case 16:
		{
			return std::make_shared<IntValue>(std::stoi(result, nullptr, 16));
		}
		}
		throw std::invalid_argument("Invalid JSON");
	}
	catch (std::invalid_argument e)
	{
		throw std::invalid_argument("Invalid JSON");
	}
}

bool json::Element::read_lit_(std::wistream& stream, const std::wstring& lit)
{
	std::wstring up = lit;
	std::wstring low = lit;
	for (int i = 0; i < lit.length(); i++)
	{
		up[i] = std::towupper(up[i]);
		low[i] = std::towlower(low[i]);
	}
	// The first character is supposed to be already read
	for (int i = 1; i < lit.size(); i++)
	{
		wchar_t c = stream.peek();
		if (c != up[i] && c != low[i])
		{
			return false;
		}
		stream.get(c);
	}
	return true;
}

void json::Element::read_comment_(std::wistream& stream)
{
	wchar_t c;
	stream.get(c);
	if (c == L'/')
	{
		while (stream.get(c) && c != L'\n')
			;
		return;
	}
	if (c == L'*')
	{
		while (stream.get(c))
		{
			if (c == L'*' && stream.peek() == L'/')
			{
				stream.get(c);
				return;
			}
		}
		throw std::invalid_argument("Invalid JSON: the multi-line comment is not closed");
	}
	throw std::invalid_argument("Invalid JSON");
}

void json::Element::pass_(std::wistream& stream, wchar_t& c)
{
	while (true)
	{
		if (c == std::wistream::traits_type::eof())
		{
			throw std::invalid_argument("Invalid JSON: unexpected end of JSON");
		}
		if (c == L'//')
		{
			stream.get(c);
			read_comment_(stream);
			c = stream.peek();
			continue;
		}
		if (std::iswspace(c))
		{
			stream.get(c);
			c = stream.peek();
			continue;
		}
		break;
	}
}

std::shared_ptr<json::Element> json::operator""_json(const wchar_t* str, std::size_t size)
{
	return Element::from_string(str);
}
