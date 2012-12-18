#include "CCPPLanguage.hpp"
#include "SPrimitiveType.hpp"

namespace wiz
{
	std::string CCPPLanguage::unsigned_qualifier(void)
	{
		return "unsigned";
	}
	std::string CCPPLanguage::signed_qualifier(void)
	{
		return "signed";
	}
	std::string CCPPLanguage::const_qualifier(void)
	{
		return "const";
	}
	std::string CCPPLanguage::static_qualifier(void)
	{
		return "static";
	}
	std::string CCPPLanguage::get_null_value(void)
	{
		return "NULL";
	}
	std::string CCPPLanguage::get_zero_value(const SPrimitiveType type)
	{
		std::string rv;
		switch(type.type)
		{
			case EPT_BOOL:
				rv = "false";
				break;
			case EPT_BYTE:
				rv = ""; // there is no such thing as a byte in C++
				break;
			case EPT_CHAR:
				rv = "'\\0'";
				break;
			case EPT_DOUBLE:
				rv = "0.0";
				break;
			case EPT_FLOAT:
				rv = "0.0f";
				break;
			case EPT_INT:
				rv = "0";
				break;
			default:
				rv = "";
				break;
		}
		return rv;
	}
	std::string CCPPLanguage::type_name(const EPrimitiveType type)
	{
		std::string rv;
		switch(type)
		{
			case EPT_BOOL:
				rv = "bool";
				break;
			case EPT_BYTE:
				rv = ""; // there is no such thing as a byte in C++.  unsigned char is what you want
				break;
			case EPT_CHAR:
				rv = "char";
				break;
			case EPT_DOUBLE:
				rv = "double";
				break;
			case EPT_FLOAT:
				rv = "float";
				break;
			case EPT_INT:
				rv = "int";
				break;
			default:
				rv = "";
				break;
		}
		return rv;
	}
	std::string CCPPLanguage::short_qualifier(const unsigned int count)
	{
		std::string rv;
		if(count >= 2)
			rv = "short short";
		else if(count == 1)
			rv = "short";
		else
			rv = "";
		return rv;
	}
	std::string CCPPLanguage::long_qualifier(const unsigned int count)
	{
		std::string rv;
		if(count >= 2)
			rv = "long long";
		else if(count == 1)
			rv = "long";
		else
			rv = "";
		return rv;
	}
	std::string CCPPLanguage::statement_sentinel(void)
	{
		return ";\n";
	}
	std::string CCPPLanguage::pointer_qualifier(const unsigned int count)
	{
		unsigned int local_count = count;
		std::string rv;
		while(local_count > 0)
		{
			rv += '*';
			local_count--;
		}
		return rv;
	}
};
