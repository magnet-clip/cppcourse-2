#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "date.h"

std::ostream &operator<<(std::ostream &stream,
                         const std::pair<Date, std::string> &date);