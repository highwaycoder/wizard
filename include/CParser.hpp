#ifndef CPARSER_HPP
#define CPARSER_HPP

#include "IParser.hpp"
#include "SPrimitiveType.hpp"
#include "SCustomType.hpp"
#include "SContext.hpp"
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <stack>

namespace wiz
{
	enum ETypeType
	{
		ETT_CUSTOM,
		ETT_PRIMITIVE,
		ETT_SENTINEL
	};
	class CParser : public IParser
	{
	public:
		CParser(ILanguage* lang) : has_error(false),fatal_error(false) { language = lang; current_mode.push(SParserMode(ESM_CREATE,EM_COMMAND)); }
		void parse(const std::string& command);
		void parse_char(const char c);
		std::string generate_code(void);
		void shutdown(void);
		// by and large, this should only ever be used privately,
		// but the IDE might want to use it to reset the state via a UI
		// widget rather than having the widget insert a ";" into the
		// stream
		void reset_state(void);
		
	private:
		// private fields
		std::stack<SParserMode> current_mode;
		std::stringstream output_line;
		
		ETypeType type_type;
		SPrimitiveType primitive;
		SCustomType custom;
		
		
		ILanguage* language;
		
		std::string error_string;
		bool has_error;
		bool fatal_error;
		
		SContext context;
	
		// private methods
		inline void set_error(const std::string& error, bool fatal = false) { fatal_error = fatal; has_error = true; error_string = error; }
		inline void clear_error(void) { fatal_error = false; has_error = false; error_string.clear(); }
		
		void lookup_line(const std::string& command);
		
		// the bulk of the parser is from here down
		void parse_char_cmd(const char c);
		void parse_char_pt(const char c);
		void parse_char_tok(const char c);
		void parse_char_ct(const char c);
		void parse_char_cti(const char c);
		void parse_char_val(const char c);
		void parse_char_esc(const char c);
	};
};


#endif
