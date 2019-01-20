#include "PrecompiledHeaders.h"

#include "Vector2i.h"

#include <iostream>

std::istream & operator >>(std::istream & in, Vector2i & v)
{
    in >> v.m_X >> v.m_Y;

    return in;
}

std::ostream & operator <<(std::ostream & out, Vector2i const & v)
{
    out << v.m_X << ' ' << v.m_Y;

    return out;
}
