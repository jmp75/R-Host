#include "stdafx.h"
#include "util.h"
#include "log.h"

using namespace rhost::log;

namespace rhost {
    namespace util {
        void fatal_error(const char* format, va_list va) {
            char message[0xFFFF];
            vsprintf_s(message, format, va);
            logf("Fatal error: %s\n", message);
            R_Suicide(message);
        }

        void fatal_error(const char* format, ...) {
            va_list va;
            va_start(va, format);
            fatal_error(format, va);
            va_end(format);
        }

        std::string to_utf8(const char* buf, size_t len) {
            auto& codecvt_wchar = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(std::locale());
            std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> convert(&codecvt_wchar);
            auto ws = convert.from_bytes(buf, buf + len);

            std::wstring_convert<std::codecvt_utf8<wchar_t>> codecvt_utf8;
            return codecvt_utf8.to_bytes(ws);
        }

        std::string from_utf8(const std::string& u8s) {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> codecvt_utf8;
            auto ws = codecvt_utf8.from_bytes(u8s);

            auto& codecvt_wchar = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(std::locale());
            std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> convert(&codecvt_wchar);
            return convert.to_bytes(ws);
        }
    }
}