#ifndef SCONTEXT_HPP
#define SCONTEXT_HPP

namespace wiz
{
	enum EScope
	{
		ES_GLOBAL,
		ES_FUNCTION_BODY,
		ES_FUNCTION_SIGNATURE,
		ES_BLOCK,
		ES_CLASS_SIGNATURE,
		ES_CLASS_BODY,
		ES_SENTINEL
	};
	
	struct SContext
	{
		SContext() : scope(ES_GLOBAL),identifier("") {}
		EScope scope;
		std::string identifier;
	};
	
};

#endif
