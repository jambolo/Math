#include "Vector3i.h"
#include <iostream>

std::istream & operator >>(std::istream & in, Vector3i & v)
{
    in >> v.m_X >> v.m_Y >> v.m_Z;

    return in;
}

std::ostream & operator <<(std::ostream & out, Vector3i const & v)
{
    out << v.m_X << ' ' << v.m_Y << ' ' << v.m_Z;

    return out;
}
