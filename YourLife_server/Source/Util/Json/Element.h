    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: Element.h                   //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____** | *****|SnowStorm|************************//
//**+ *+ *+ *+ **|*****************************|****** | ****************************************//
//*+ *+ *+ *+ ***\___ ** ___ ** ___ **|*****|**\___ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|** | **|***|**|***\**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***____/**|***|**\___/***\/ \/***____/** \_**\___/**|******|**|**|** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

namespace ylife
{

namespace json
{

/**
 *	\defgroup SnowStorm SnowStorm
 *	\~english
 *	\brief SnowStorm, the SnowEngine JSON system
 *	
 *	SnowStorm allows to work with JSON format. SnowStorm's JSON is slightly different from the
 *	the common JSON. If the string is valid for common JSON, it should also be valid for
 *	SnowStorm's one, but valid SnowStorm's JSON string may turn out not to be valid for common
 *	JSON. The data can be stored by the classes listed below, which are based on the `Element`
 *	class. The `Element` represents any JSON entity. It has methods allowing to convert it to
 *	string and vice versa, save it to file or load the `Element` from file. A string or a file is a
 *	valid JSON if it only has one well-formed JSON element (this element can contain multiple child
 *	elements). Space characters outside elements are ignored. Here is the list of element types.
 *	- Values.
 *		- `StringValue`. Strings must be enclosed in " or ' characters. They can contain escape
 *		sequences listed in the documentation of `String::escape()` method.
 *		- `IntValue`. Integer values can be specified in decimal, binary, octal or hexadecimal
 *		notation. By default the number is assumed to be decimal. Use prefixes to change it: `0b`
 *		(`0B`) for binary, `0o` (`0O`) for octal, `0x` or `0h` (`0X` or `0H`) for hexadecimal.
 *		- `DoubleValue`. Double values can only be specified as decimal numbers. The point
 *		character is used as decimal point.
 *		- `BoolValue`. `true` or `false`. Boolean values are not case sensitive (e. g. `fALsE` is
 *		alse valid boolean value).
 *		- `NullValue`. `null`. It is also not case sensitive.
 *	- `Array`. Arrays can contain any number of `Element`s (including other arrays and objects). In
 *	strings and files array elements are listed inside [ and ] characters and separated by
 *	commas. The last element is allowed to be followed by comma. All space characters between
 *	elements are ignored.
 *	- `JsonObject`. Objects can contain any number of key-value pairs, which in strings and files
 *	are listed inside { and } characters and separated by commas. The last pair is allowed to
 *	be followed by comma. The key is always a string enclosed in " or ' characters. Value can
 *	be any `Element` (including other objects and arrays). The : characters must separate key and
 *	value. The order of elements in an object does not matter. All space characters between
 *	elements are ignored.
 *	
 *	\~russian
 *	\brief SnowStorm, система SnowEngine для работы с JSON
 *	
 *	SnowStorm позволяет работать с форматом JSON. SnowStorm's JSON слегка отличается от обычного
 *	JSON. Если строка корректна для обычного JSON, то она должна быть корректна и для SnowStorm's
 *	JSON, но корректная для SnowStorm's JSON строка может оказаться некорректной для обычного JSON.
 *	Данные могут храниться в классах, перечисленных ниже, которые наследуются от класса `Element`.
 *	`Element` представляет любую сущность JSON. Он имеет методы, позволяющие конвертировать его в
 *	строку и наоборот, сохранять его в файл или загружать `Element` из файла. Строка или файл
 *	является корректным JSON, если имеет только один правильно записанный элемент JSON (этот
 *	элемент может содержать множество дочерних элементов). Пробельные символы вне элементов
 *	игнорируются. Дале приведён список типов элементов.
 *	- Значения.
 *		- `StringValue`. Строки должны быть заключены в символы " или '. Они могут содержать
 *		управляющие последовательности, перечисленные в документации метода `String::escape()`.
 *		- `IntValue`. Целочисленные значения могут быть указаны в десятичной, двоичной,
 *		восьмеричной или шестнадцатеричной записи. По умолчанию предполагается, что число
 *		десятичное. Чтобы изменить это , используйте префиксы: `0b` (`0B`) для двоичной, `0o`
 *		(`0O`) для восьмеричной, `0x` или `0h` (`0X` или `0H`) для шестнадцатеричной системы.
 *		- `DoubleValue`. Вещественные значения могут быть заданы только как десятичные числа. Для
 *		десятичного разделителя используется символ точки.
 *		- `BoolValue`. `true` или `false`. Булевы значения не чувствительны к регистру (например,
 *		`fALsE` — также корректое булево значение).
 *		- `NullValue`. `null`. Также не чувствителен к регистру.
 *	- `Array`. Массивы могут содержать произвольное число `Element`'ов (включая другие массивы и
 *	объекты). В строках и файлах элементы массива перечисляются внутри символов [ и ] и
 *	разделяются запятыми. Допускается наличие запятой после последнего элемента. Все пробельные
 *	символы между элементами игнорируются.
 *	- `JsonObject`. Объекты могут содержать произвольное число пар ключ-значение, которые в строках
 *	и файлах перечисляются внутри символов { и } и разделяются запятыми. Допускается наличие
 *	запятой после последней пары. Ключ всегда является строкой, заключённой в символы " или '.
 *	Значение может быть любым `Element`'ом (включая другие объекты и массивы). Ключ и значение
 *	должны разделяться символом :. Порядок элементов в объекте не важен. Все пробельные символы
 *	между элементами игнорируются.
 */

/**
 *	\addtogroup SnowStorm
 *	\{
 */

class JsonObject;
class Array;

/**
 *	\~english
 *	\brief The type of JSON element
 *	
 *	The enumeration with JSON element types.
 *	
 *	\~russian
 *	\brief Тип элемента JSON
 *	
 *	Перечисление с типами элементов JSON.
 */
enum class EType
{
	OBJECT,			///< \~english JSON object/map \~russian Объект/словарь JSON
	ARRAY,			///< \~english JSON array \~russian Массив JSON
	STRING_VALUE,	///< \~english JSON string value \~russian Строковое значение JSON
	INT_VALUE,		///< \~english JSON integer value \~russian Целочисленное значение JSON
	DOUBLE_VALUE,	///< \~english JSON double value \~russian Вещественное значение JSON
	BOOL_VALUE,		///< \~english JSON boolean value \~russian Булево значение JSON
	NULL_VALUE		///< \~english JSON null value \~russian Нулевое значение JSON
};

/**
 *	\~english
 *	\brief The JSON element
 *	
 *	The base class for all JSON elements: objects, arrays and values. You can convert the string to
 *	JSON element using `from_string()` method. You can also load an element from file using
 *	`load()` method.
 *	
 *	\~russian
 *	\brief Элемент JSON
 *	
 *	Базовый класс для всех элементов JSON: объектов, массивов и значений. Вы можете конвертировать
 *	строку в элемент JSON с помощью метода `from_string()`. Вы можете также загрузить элемент из
 *	файла с помощью метода `load()`.
 */
class Element
{
public:
			/* METHODS */

	/**
	 *	\~english
	 *	\brief Converts the element to string
	 *	
	 *	Creates a string in JSON format representing the element.
	 *	\return The JSON string.
	 *	\sa
	 *	- `from_string()`
	 *	
	 *	\~russian
	 *	\brief Конвертирует элемент в строку
	 *	
	 *	Создаёт строку в формате JSON, представляющую элемент.
	 *	\return JSON-строка.
	 *	\sa
	 *	- `from_string()`
	 */
	std::wstring to_string() const;
	
	/**
	 *	\~english
	 *	\brief The type of the element
	 *	
	 *	Allows to get the element type.
	 *	\return The type of the element.
	 *	
	 *	\~russian
	 *	\brief Тип элемента
	 *	
	 *	Позволяет получить тип элемента.
	 *	\return Тип элемента.
	 */
	virtual EType get_type() const = 0;
	
	/**
	 *	\~english
	 *	\brief Saves in the file
	 *	
	 *	Saves the element in the file in JSON format.
	 *	\param filename The path to the file where the element will be saved.
	 *	\param allow_override Allows to override existing file with the same name. If `false`, the
	 *	file cannot be overriden and the exception is thrown.
	 *	\throw std::runtime_error The file cannot be created, accessed or overriden.
	 *	\sa
	 *	- `load()`
	 *	
	 *	\~russian
	 *	\brief Сохраняет в файл
	 *	
	 *	Сохраняет элемент в файл в формате JSON.
	 *	\param filename Путь к файлу, где элемент будет сохранён.
	 *	\param allow_override Позволяет перезаписывать существующий файл с таким же именем. Если
	 *	`false`, файл не может быть перезаписан, и выбрасывается исключение.
	 *	\throw std::runtime_error Файл не может быть создан, перезаписан или к нему не удаётся
	 *	получить доступ.
	 *	\sa
	 *	- `load()`
	 */
	void save(const std::wstring& filename, bool allow_override = false) const;

	/**
	 *	\~english
	 *	\brief Puts the element to the stream
	 *	
	 *	Converts the element to JSON format and puts it to the stream.
	 *	\param stream The stream where the element will be put.
	 *	\param nesting Number of tabs to the left of the element (only affects objects).
	 *	\sa
	 *	- `from_stream()`
	 *	
	 *	\~russian
	 *	\brief Помещает элемент в поток
	 *	
	 *	Конвертирует элемент в формат JSON и помещает его в поток.
	 *	\param stream Поток, куда будет помещён элемент.
	 *	\param nesting Количество табуляций слева от элемента (влияет только на объекты).
	 *	\sa
	 *	- `from_stream()`
	 */
	virtual void to_stream(std::wostream& stream, int nesting = 0) const = 0;
	
	/**
	 *	\~english
	 *	\brief Creates the element based on the string
	 *	
	 *	Converts the string to the JSON element.
	 *	\param string The string with JSON.
	 *	\return The shared pointer to the created element.
	 *	\throw std::invalid_argument The string is not valid JSON.
	 *	\sa
	 *	- `to_string()`
	 *	
	 *	\~russian
	 *	\brief Создаёт элемент на основе строки
	 *	
	 *	Конвертирует строку в элемент JSON.
	 *	\param string Строка с JSON.
	 *	\return Указатель на созданный элемент.
	 *	\throw std::invalid_argument Строка не является корректным JSON.
	 *	\sa
	 *	- `to_string()`
	 */
	static std::shared_ptr<Element> from_string(const std::wstring& string);
	
	/**
	 *	\~english
	 *	\brief Creates the element by loading JSON from file
	 *	
	 *	Loads the file content and creates the JSON element based on it.
	 *	\param filename The path to the file with JSON.
	 *	\return The shared pointer to the created element.
	 *	\throw std::runtime_error The file does not exist or cannot be accessed.
	 *	\throw std::invalid_argument The file doesn't contain a valid JSON.
	 *	\sa
	 *	- `save()`
	 *	
	 *	\~russian
	 *	\brief Создаёт элемент, загружая JSON из файла
	 *	
	 *	Загружает содержимое файла и создаёт на его основе элемент JSON.
	 *	\param filename Путь к файлу с JSON.
	 *	\return Указатель на созданный элемент.
	 *	\throw std::runtime_error Файл не существует или к нему не удаётся получить доступ.
	 *	\throw std::invalid_argument Файл не содержит корректный JSON.
	 *	\sa
	 *	- `save()`
	 */
	static std::shared_ptr<Element> load(const std::wstring& filename);
	
	/**
	 *	\~english
	 *	\brief Creates the element based on the stream
	 *	
	 *	Reads the stream and converts its content to the JSON element.
	 *	\param stream The stream with JSON.
	 *	\return The shared pointer to the created element.
	 *	\throw std::invalid_argument The stream doesn't contain a valid JSON.
	 *	\sa
	 *	- `to_stream()`
	 *	
	 *	\~russian
	 *	\brief Создаёт элемент на основе поток
	 *	
	 *	Конвертирует строку в элемент JSON.
	 *	\param stream Поток с JSON.
	 *	\return Указатель на созданный элемент.
	 *	\throw std::invalid_argument Поток не содержит корректный JSON.
	 *	\sa
	 *	- `to_stream()`
	 */
	static std::shared_ptr<Element> from_stream(std::wistream& stream);

	static std::wstring escape(const std::wstring& string);
	static std::wstring unescape(const std::wstring& unescape);
	
private:
	static std::shared_ptr<JsonObject> read_object_(std::wistream& stream); // The { character is supposed to be already read
	static std::shared_ptr<Array> read_array_(std::wistream& stream); // The [ character is supposed to be already read
	static std::wstring read_string_(std::wistream& stream, wchar_t first); // The " or ' character is supposed to be already read and is passed as argument (first)
	static std::shared_ptr<Element> read_number_(std::wistream& stream, wchar_t first); // The first character is supposed to be already read and is passed as argument (first)
	static bool read_lit_(std::wistream& stream, const std::wstring& lit); // The first character is supposed to be already read; returns false if couldn't read a desired literal (lit)
	static void read_comment_(std::wistream& stream); // The / character is supposed to be already read
	static void pass_(std::wistream& stream, wchar_t& c); // Pass the space characters and comments
};

/**
 *	\~english
 *	\brief A JSON literal
 *	
 *	Allows to create a JSON elements using literals:
 *	\code
 *		L"{ \"name\": \"The Game\", \"engine\": \"SnowEngine\", \"year\": 2062, \"is_cool\": true }"_json;
 *	\endcode
 *	\param str The string.
 *	\param size The length of the string.
 *	\return The pointer to the JSON element.
 *	\throw std::invalid_argument The string is not a valid JSON.
 *	
 *	\~russian
 *	\brief Литерал JSON
 *	
 *	Позволяет создавать элементы JSON, используя литералы:
 *	\code
 *		L"{ \"name\": \"The Game\", \"engine\": \"SnowEngine\", \"year\": 2062, \"is_cool\": true }"_json;
 *	\endcode
 *	\param str Строка.
 *	\param size Длина строки.
 *	\return Указатель на элемент JSON.
 *	\throw std::invalid_argument Строока не является корректным JSON.
*/
std::shared_ptr<Element> operator""_json(const wchar_t* str, std::size_t size);

/**
 *	\}
 */

}

}

using ylife::json::operator""_json;
