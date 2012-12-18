#ifndef WIZARD_H
#define WIZARD_H

// convenience header that includes all necessary headers in the project
// note that most C* headers already include their I* counterparts
// and therefore including the I* counterpart here is redundant at best

// the headers proper
#include "CParser.hpp"
#include "CCPPLanguage.hpp"

// an inline function to create a default ILanguage* object
inline wiz::ILanguage* create_language_default(void)
	{ return new wiz::CCPPLanguage(); }

// an inline function to create an IParser object, negating the need
// for the user to get involved in the nitty gritty of the actual
// implementation of CParser
// in future this function will take parameters to specify configuration
inline wiz::IParser* create_parser(wiz::ILanguage* language) 
	{ return new wiz::CParser(language); }

inline wiz::IParser* create_parser(void) 
	{ return new wiz::CParser(create_language_default()); }


#endif
