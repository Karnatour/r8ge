#include "../r8gepch.h"
#include "EntryPoint.h"

#include "fileio/FileIO.h"
#include "Logger.h"
#include "Ar8ge.h"

namespace r8ge {
    int main(const EntryPointData& entry_data)
    {
        Logger::init();
        auto engine = new Ar8ge;
        global::fileIO = new FileIO(256);

        engine->init();
        engine->run();
        engine->exit();

        delete engine;
        delete global::fileIO;

        return 0;
    }
}

