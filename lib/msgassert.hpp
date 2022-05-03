#pragma once

#include <iostream>

#define assert(e, m) ((void)((e) ? 0 : __assert(#e, __FILE__, __LINE__, m)))

#define __assert(e, file, line, m)                                             \
    (std::cerr << file ":" << line << ": " << m << '\n', abort(), 0)
