#pragma once

#if _UNICODE
#define SL_STD_STRING std::wstring
#else
#define SL_STD_STRING std::string
#endif
