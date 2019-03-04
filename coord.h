#pragma once

#include <iostream>

using coord = std::pair<size_t, size_t>;

std::ostream &operator <<(std::ostream &os, const coord &pd);