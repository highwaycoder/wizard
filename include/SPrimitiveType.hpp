#ifndef SPRIMITIVETYPE_HPP
#define SPRIMITIVETYPE_HPP

#include "ILanguage.hpp"
#include "EPrimitiveType.hpp"
#include <string>
#include <sstream>

namespace wiz
{
	
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
		//! \todo thinking about deferring to a method on ILanguage, in 
		//! case of languages that have rules about the order of modifiers
		//! also helps keep whitespace rules in a single, canonical place
		inline std::string string(ILanguage* lang)
		{
			std::stringstream builder;
			
			if(qualify_const)
			{
				builder << lang->const_qualifier();
			}
			if(qualify_signed)
			{
				if(qualify_const) builder << " ";
				builder << lang->signed_qualifier();
			}
			if(qualify_unsigned)
			{
				if(qualify_signed || qualify_const) builder << " ";
				builder << lang->unsigned_qualifier();
			}
			if(qualify_unsigned || qualify_signed || qualify_const) builder << " ";
			builder << lang->short_qualifier(short_qualifiers);
			if(short_qualifiers > 0 && lang->short_qualifier(1) != "") builder << " ";
			builder << lang->long_qualifier(long_qualifiers);
			if(long_qualifiers > 0 && lang->long_qualifier(1) != "") builder << " ";
			builder << lang->type_name(type);
			builder << lang->pointer_qualifier(pointer_qualifiers);
			builder << " ";
			return builder.str();
		}
		inline void clear(void)
		{
			qualify_unsigned = qualify_signed = qualify_const = false;
			type = EPT_INT;
			short_qualifiers = 0;
			long_qualifiers = 0;
			pointer_qualifiers = 0;
		}
	};
};

#endif
