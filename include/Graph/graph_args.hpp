#pragma once
#include "../Base/named_type.hpp"
namespace GraphArgs {
registerNamedType(hasWeight, bool);
using weightRangeType =
    NamedType<std::pair<int, int>, struct __weightRangeTypeTag>;
static const weightRangeType::Argument weightRange;
registerNamedType(selfLoop, bool);
registerNamedType(repeatedEdge, bool);
} // namespace GraphArgs