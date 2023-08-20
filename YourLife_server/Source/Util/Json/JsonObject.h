    ////////////////////////////////////////
   //      SnowEngine by SnegirSoft      //
  //                                    //
 //  File: JsonObject.h                //
////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//*+ *+ *+ *+ *** ____************************* ____** | *****|SnowStorm|************************//
//**+ *+ *+ *+ **|*****************************|****** | ****************************************//
//*+ *+ *+ *+ ***\___ ** ___ ** ___ **|*****|**\___ **_|_** ___ ** ___ ** __ __ *****************//
//**+ *+ *+ *+ ******|**|***|**|***|**|**|**|******|** | **|***|**|***\**|**|**|*** SnowEngine **//
//*+ *+ *+ *+ ***____/**|***|**\___/***\/ \/***____/** \_**\___/**|******|**|**|** JSON  system *//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Element.h"

#include <map>

namespace ylife
{

namespace json
{

/**
 *	\addtogroup SnowStorm
 *	\{
 */

/**
 *	\~english
 *	\brief JSON object (map)
 *	
 *	JSON object is a set of key-value pairs. The key is string, the value can be any JSON element
 *	(string, integer, double, boolean or null values, array, another object). You can access these
 *	pairs via `get_content()` method.
 *	
 *	\~russian
 *	\brief Объект JSON (словарь)
 *	
 *	Объект JSON — набор пар ключ-значение. Ключом является строка, значением может быть любой
 *	элемент JSON (строковое, целочисленное, вещественное, булево или нулевое значение, массив,
 *	другой объект). Вы можете получить доступ к этим парам методом `get_content()`.
 */
class JsonObject : public Element
{
public:
			/* CONSTRUCTORS */

	/**
	 *	\~english
	 *	\brief The default constructor
	 *	
	 *	Creates an empty object (`{ }`).
	 *	
	 *	\~russian
	 *	\brief Конструктор по умолчанию
	 *	
	 *	Создаёт пустой объект (`{ }`).
	 */
	JsonObject();

	/**
	 *	\~english
	 *	\brief The move constructor
	 *	
	 *	Creates a new object by moving the content of another one.
	 *	
	 *	\~russian
	 *	\brief Конструктор перемещения
	 *	
	 *	Создаёт новый объект путём перемещения содержимого другого.
	 */
	JsonObject(JsonObject&& object);

			/* METHODS FROM Element */
	
	/**
	 *	\~english
	 *	\brief The type of the element
	 *	
	 *	Allows to get the element type.
	 *	\return `EType::OBJECT`.
	 *	
	 *	\~russian
	 *	\brief Тип элемента
	 *	
	 *	Позволяет получить тип элемента.
	 *	\return `EType::OBJECT`.
	 */
	virtual EType get_type() const override;

	/**
	 *	\~english
	 *	\brief Puts the object to the stream
	 *	
	 *	Converts the object to JSON format and puts it to the stream.
	 *	\param stream The stream where the object will be put.
	 *	\param nesting Number of tabs to the left of the object.
	 *	
	 *	\~russian
	 *	\brief Помещает объект в поток
	 *	
	 *	Конвертирует объект в формат JSON и помещает его в поток.
	 *	\param stream Поток, куда будет помещён объект.
	 *	\param nesting Количество табуляций слева от объекта.
	 */
	virtual void to_stream(std::wostream& stream, int nesting = 0) const override;

			/* METHODS */

	/**
	 *	\~english
	 *	\brief The content of the object
	 *	
	 *	Allows to access the key-value pairs of the object.
	 *	\return The constant reference to the map with the object content.
	 *	
	 *	\~russian
	 *	\brief Содержимое объекта
	 *	
	 *	Позволяет получить доступ к парам ключ-значение объекта.
	 *	\return Константная ссылка на словарь с содержимым объекта.
	 */
	std::map<std::wstring, std::shared_ptr<Element>>& get_content() noexcept;

	/**
	 *	\~english
	 *	\brief The content of the object
	 *	
	 *	Allows to read the key-value pairs of the object.
	 *	\return The reference to the map with the object content.
	 *	
	 *	\~russian
	 *	\brief Содержимое объекта
	 *	
	 *	Позволяет прочитать пары ключ-значение объекта.
	 *	\return Ссылка на словарь с содержимым объекта.
	 */
	const std::map<std::wstring, std::shared_ptr<Element>>& get_content() const noexcept;
	
private:
	std::map<std::wstring, std::shared_ptr<Element>> content_;
};

/**
 *	\}
 */

}

}
