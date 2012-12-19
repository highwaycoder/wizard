#include "CParser.hpp"
#include "ILanguage.hpp"
#include <iostream>

namespace wiz
{
	//! \brief helper function, calls parse_char_* based on current_mode and c
	//! \param[in] c the character to parse
	void CParser::parse_char(const char c)
	{
		switch(current_mode.top().mode)
		{
			case EM_COMMAND:
			{
				parse_char_cmd(c);
				break;
			}
			case EM_PRIMITIVE_TYPE:
			{
				type_type = ETT_PRIMITIVE;
				parse_char_pt(c);
				break;
			}
			case EM_TOKEN:
			{
				parse_char_tok(c);
				break;
			}
			case EM_CUSTOM_TYPE:
			{
				type_type = ETT_CUSTOM;
				parse_char_ct(c);
				break;
			}
			case EM_CUSTOM_TYPE_IDENTIFIER:
			{
				parse_char_cti(c);
				break;
			}
			case EM_VALUE:
			{
				parse_char_val(c);
				break;
			}
			case EM_ESCAPED_CHAR:
			{
				parse_char_esc(c);
				break;
			}
			default:
			{
				set_error("Parser is in unknown/unsupported mode.",true);
				break;
			}
		}
	}
	
	//! \brief parses a command character
	//! \param[in] c the character to parse
	void CParser::parse_char_cmd(const char c)
	{
		switch(c)
		{
			case 'v':
			{
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_PRIMITIVE_TYPE));
				break;
			}
			case 'V':
			{
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_CUSTOM_TYPE));
				break;
			}
			default:
			{
				set_error("Unknown/unsupported command",true);
				break;
			}
		}
	}
	
	void CParser::parse_char_ct(const char c)
	{
		switch(c)
		{
			case 'c':
				custom.qualify_const = true;
				break;
			case 's':
				// if(lang->static_appropriate(context)) custom.qualify_static = true;
				break;
			case 'p':
			case '*':
				custom.pointer_qualifiers++;
				break;
			case ':':
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_CUSTOM_TYPE_IDENTIFIER));
				break;
			default:
				set_error("Unknown sub-command (mode: custom type)",true);
				break;
		}
	}
	
	void CParser::parse_char_cti(const char c)
	{
		switch(c)
		{
			case ':':
				output_line << custom.string(language);
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_TOKEN));
				break;
			default:
				custom.name += c;
				break;
		}
	}
	
	void CParser::parse_char_pt(const char c)
	{
		switch(c)
		{
			case 'u':
			{
				primitive.qualify_unsigned = true;
				primitive.qualify_signed = false;
				break;
			}
			case 's':
			{
				primitive.qualify_unsigned = false;
				primitive.qualify_signed = true;
				break;
			}
			case 'c':
			{
				primitive.qualify_const = true;
				break;
			}
			case 'i':
			{
				primitive.type = EPT_INT;
				break;
			}
			case 'p':
			case '*':
			{
				primitive.pointer_qualifiers++;
				break;
			}
			case ':':
			{
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_TOKEN));
				output_line << primitive.string(language);
				break;
			}
			default:
			{
				set_error("Unknown sub-command (mode: primitive type)",true);
				break;
			}
		}
	}
	
	void CParser::parse_char_tok(const char c)
	{
		switch(c)
		{
			case '(':
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_PARAMETER));
				break;
			case ';':
				reset_state();
				break;
			case '\n':
				reset_state();
				break;
			case ':':
				current_mode.pop();
				break;
			case ' ':
				//if(language->allows_whitespace_in_identifiers) output_line << c;
				break;
			case '=':
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_VALUE));
				can_generate = false; // until we know we have an appropriate value
				break;
			case '\\':
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_ESCAPED_CHAR));
				break;
			default:
				output_line << c;
				can_generate = true; // at this stage there's no reason to believe we can't generate valid code
				break;
		}
	}
	
	//! \todo we can do some really awesome type-checking and static
	//! analysis here, since we know what type we're dealing with
	//! but fuck it, let's just assume the programmer isn't a moron
	//! at least for now
	void CParser::parse_char_val(const char c)
	{
		switch(c)
		{
			case 'n':
			{
				if(type_type != ETT_CUSTOM && !language->allow_new_primitives())
				{
					set_error("Warning: 'new' keyword inappropriate in this context.  Skipping.",false);
					break;
				}
				output_line << language->get_operator("equals")
				<< " "
				<< language->new_keyword();
				break;
			}
			case 'z':
			{
				switch(type_type)
				{
					case ETT_CUSTOM:
					{
						if(custom.pointer_qualifiers == 1)
						{
							output_line << language->new_instance(custom);
						}
						else if(custom.pointer_qualifiers == 0)
						{
							output_line << language->new_reference(custom);
						}
						else
						{
							output_line << language->get_operator("equals")
							<< " "
							<< language->get_null_value();
						}
						
						break;
					}
					case ETT_PRIMITIVE:
					{
						if(primitive.pointer_qualifiers == 0)
						{
							output_line << language->get_operator("equals")
							<< " "
							<< language->get_zero_value(primitive);
						}
						else
						{
							output_line << language->get_operator("equals")
							<< " "
							<< language->get_null_value();
						}
						break;
					}
					default:
						break;
				}
				break;
			}
			case '\\':
				current_mode.push(SParserMode(current_mode.top().super_mode,EM_ESCAPED_CHAR));
				break;
			case ' ':
				// always ignore whitespace in value blocks, it's meaningless
				break;
			default:
				output_line << c;
				break;
		}
		can_generate = true; // we can generate anything that has a value set
	}
	
	void CParser::parse_char_esc(const char c)
	{
		output_line << c;
		current_mode.pop();
	}
	
	//! \todo implement this
	void CParser::lookup_line(const std::string& command)
	{
		// compiler gag
		command.empty();
	}
	
	void CParser::parse(const std::string& command)
	{
		if(current_mode.top().super_mode == ESM_EDIT) lookup_line(command);
		for(std::string::const_iterator i = command.begin(); i != command.end(); ++i)
		{
			parse_char(*i);
		}
	}
	
	std::string CParser::generate_code(void)
	{
		std::string rv;
		if(has_error)
			std::cerr << "Generated code would be malformed: " << error_string << std::endl;
		if(fatal_error)
		{
			rv = "";
		}
		else if(!can_generate)
		{
			std::cerr << "Incomplete command (perhaps you missed an identifier?)" << std::endl;
		}
		else
		{
			output_line << language->statement_sentinel();
			rv = output_line.str();
		}
		reset_state();
		return rv;
	}
	
	void CParser::shutdown(void)
	{
		delete language;
		delete this;
	}
	
	void CParser::reset_state(void)
	{
		output_line.str("");
		output_line.clear();
		clear_error();
		while(!current_mode.empty()) current_mode.pop();
		current_mode.push(SParserMode(ESM_CREATE,EM_COMMAND));
		primitive.clear();
		custom.clear();
	}
	
};
