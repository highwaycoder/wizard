#ifndef SCUSTOMTYPE_HPP
#define SCUSTOMTYPE_HPP

#include "ILanguage.hpp"
#include <string>
#include <sstream>

namespace wiz
{

	struct SCustomType
	{
		bool qualify_const;
		bool qualify_static;
		unsigned int pointer_qualifiers;
		std::string name;
		inline std::string string(ILanguage* lang)
		{
			std::stringstream builder;
			
			if(qualify_const)
			{
				builder << lang->const_qualifier();
			}
			if(qualify_static)
			{
				if(qualify_const) builder << " ";
				builder << lang->static_qualifier();
			}
			if(qualify_static || qualify_const) builder << " ";
			builder << name;
			builder << lang->pointer_qualifier(pointer_qualifiers);
			builder << " ";
			return builder.str();
		}
		inline void clear(void)
		{
			qualify_const = false;
			qualify_static = false;
			pointer_qualifiers = 0;
			name = "";
		}
	};

};

#endif
