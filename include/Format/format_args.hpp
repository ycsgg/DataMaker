#pragma once
#include "../Base/named_type.hpp"
namespace Formatter{
namespace FormatterArgs {
enum OutputType {
    RANDOM,
    ORDER,
};
registerNamedType(output_type, OutputType);

registerNamedType(no_weight, bool);

registerNamedType(delimeter, char);

} // namespace FormatterArgs
}