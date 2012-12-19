#ifndef SCUSTOMTYPE_HPP
#define SCUSTOMTYPE_HPP

#include <string>
#include <sstream>

namespace wiz
{
	class ILanguage;
	struct SCustomType
	{
		bool qualify_const;
		bool qualify_static;
		unsigned int pointer_qualifiers;
		std::string name;
		std::string string(ILanguage* lang);
		void clear(void);
	};

};

#endif
