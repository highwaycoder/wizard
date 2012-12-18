#ifndef IPARSER_HPP
#define IPARSER_HPP

#include <string>

namespace wiz
{
	enum ESuperMode
	{
		ESM_CREATE,
		ESM_EDIT,
		ESM_SENTINEL // - SHOULD NEVER BE IN THIS MODE
	};
	
	enum EMode
	{
		EM_COMMAND,
		EM_TOKEN,
		EM_PRIMITIVE_TYPE,
		EM_CUSTOM_TYPE,
		EM_CUSTOM_TYPE_IDENTIFIER,
		EM_FUNCTION_DEF,
		EM_FUNCTION_DEC,
		EM_CLASS_DEF,
		EM_CLASS_DEC,
		EM_PARAMETER,
		EM_VALUE,
		EM_ESCAPED_CHAR,
		//EM_NAMESPACE, // todo
		EM_SENTINEL // - SHOULD NEVER BE IN THIS MODE EITHER
	};
	
	struct SParserMode
	{
	public:
		SParserMode(ESuperMode sm,EMode m) : super_mode(sm),mode(m) {}
		ESuperMode super_mode;
		EMode mode;
		inline void set(ESuperMode sm, EMode m) { super_mode = sm; mode = m; }
	};
	
	struct SParserCommand
	{
		SParserMode mode;
		char command;
	};
	
	class IParser
	{
	public:
		virtual void parse(const std::string& command) = 0;
		virtual void parse_char(const char c) = 0;
		virtual std::string generate_code(void) = 0;
		virtual void shutdown(void) = 0;
	};
};

#endif
