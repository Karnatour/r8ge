#ifndef R8GE_ENTRYTPOINT_H
#define R8GE_ENTRYTPOINT_H

#include <thread>

namespace r8ge {
    namespace video {
        class EntryPoint {
        public:
            EntryPoint();
            ~EntryPoint();
            void run();
        private:
            std::thread m_thread;
        };
    }
}

#endif//!R8GE_ENTRYTPOINT_H
