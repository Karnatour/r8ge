#include "EntrytPoint.h"

#include "Video.h"

#include <r8ge/r8ge.h>
#include <thread>

namespace r8ge {
    video::EntryPoint::EntryPoint() {
        m_thread = std::thread(&EntryPoint::run, this);
    }

    video::EntryPoint::~EntryPoint() {
        m_thread.join();
    }

    void video::EntryPoint::run() {
        while(!Ar8ge::isReady())
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // TODO: Get data from core

        Video video;

        video.init();

        video.run();

        video.exit();
    }

    video::EntryPoint entryPoint;
}