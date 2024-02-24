#include "../../r8gepch.h"

#include "../EntryPoint.h"

int main(int argc, char** argv) {
    r8ge::EntryPointData data{};

    for(int i = 1; i < argc; i++)
        data.argv.emplace_back(argv[i]);

   return r8ge::main(data);
}