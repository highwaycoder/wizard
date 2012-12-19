#ifndef ILANGUAGE_HPP
#define ILANGUAGE_HPP

#include "EPrimitiveType.hpp"
#include "SCustomType.hpp"
#include "SParam.hpp"
#include <string>
#include <vector>

namespace wiz
{
	struct SPrimitiveType;
	class ILanguage
	{
	public:
		virtual std::string unsigned_qualifier(void) = 0;
		virtual std::string signed_qualifier(void) = 0;
		virtual std::string const_qualifier(void) = 0;
		virtual std::string type_name(const EPrimitiveType& type) = 0;
		virtual std::string short_qualifier(const unsigned int count) = 0;
		virtual std::string long_qualifier(const unsigned int count) = 0;
		virtual std::string statement_sentinel(void) = 0;
		virtual std::string pointer_qualifier(const unsigned int count) = 0;
		virtual std::string static_qualifier(void) = 0;
		virtual std::string get_null_value(void) = 0;
		virtual std::string get_zero_value(const SPrimitiveType& type) = 0;
		virtual std::string new_keyword(void) = 0;
		virtual std::string new_instance(const SCustomType& type, const std::vector<SParam>& parameters = std::vector<SParam>()) = 0;
		virtual std::string new_reference(const SCustomType& type, const std::vector<SParam>& parameters = std::vector<SParam>()) = 0;
		virtual bool allow_new_primitives(void) = 0;
		virtual std::string get_operator(const std::string& type) = 0;
	private:
	};
};

#endif
