#pragma once

#include "Core.h"

namespace r8ge {
    struct EntryPointData {
        std::vector<std::string_view> argv;
    };

    // Engine's entry point, called by the platform layer
    int main(const EntryPointData& entry_data);
}
