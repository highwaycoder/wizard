#ifndef CCPPLANGUAGE_HPP
#define CCPPLANGUAGE_HPP

#include "ILanguage.hpp"

namespace wiz
{
	class CCPPLanguage : public ILanguage
	{
	public:
		virtual std::string unsigned_qualifier(void);
		virtual std::string signed_qualifier(void);
		virtual std::string const_qualifier(void);
		virtual std::string type_name(const EPrimitiveType& type);
		virtual std::string short_qualifier(const unsigned int count);
		virtual std::string long_qualifier(const unsigned int count);
		virtual std::string statement_sentinel(void);
		virtual std::string pointer_qualifier(const unsigned int count);
		virtual std::string static_qualifier(void);
		virtual std::string get_null_value(void);
		virtual std::string get_zero_value(const SPrimitiveType& type);
		virtual std::string new_keyword(void);
		virtual std::string new_instance(const SCustomType& type, const std::vector<SParam>& parameters);
		virtual std::string new_reference(const SCustomType& type, const std::vector<SParam>& parameters);
		virtual std::string get_operator(const std::string& type);
		virtual bool allow_new_primitives(void);
	private:
	};
};

#endif
