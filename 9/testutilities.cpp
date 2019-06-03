#include "testutilities.h"
#include <glibmm/convert.h>

std::ostream& operator<<(std::ostream& os, const CatchConvertError& utf8_string)
{
    try
    {
        os << static_cast<const Glib::ustring&>(utf8_string);
    }
    catch (const Glib::ConvertError& ex)
    {
        os << "[Glib::ConvertError: " << ex.what() << "]";
    }
    return os;
}
