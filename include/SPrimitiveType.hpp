#ifndef SPRIMITIVETYPE_HPP
#define SPRIMITIVETYPE_HPP

#include "EPrimitiveType.hpp"
#include <string>
#include <sstream>

namespace wiz
{
	class ILanguage;
	struct SPrimitiveType
	{
		bool qualify_unsigned;
		bool qualify_signed;
		bool qualify_const;
		bool qualify_static;
		EPrimitiveType type;
		unsigned short int short_qualifiers;
		unsigned short int long_qualifiers;
		unsigned short int pointer_qualifiers;
		std::string string(ILanguage* lang);
		void clear(void);
	};
};

#endif
