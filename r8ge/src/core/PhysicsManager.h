#pragma once

namespace r8ge
{

    enum TYPE{
        STATIC,
        DYNAMIC,
        KINEMATIC
    };

    class PhysicsManager
    {
    public:
        PhysicsManager();
        void addBody(TYPE type,unsigned int id);
        void changeBodyType(TYPE type);
    private:

    };

} // r8ge