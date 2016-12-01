#include "base/errors.hpp"
#include "lpi/context.hpp"

namespace {
	lpi::context* context;
}

void err::set_context(lpi::context& ctx) {
    context = &ctx;
}

std::string err::error_prefix(const std::string& type) {
    auto line = std::to_string(context->line_count());
    return "[Line " + line + "] " + type + " error: ";
}

void err::echo(const std::string& message) {
    std::cout << message << std::endl;
}
