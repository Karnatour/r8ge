#pragma once

/*
#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

namespace r8ge
{

    enum TYPE{
        STATIC,
        DYNAMIC,
        KINEMATIC
    };

    enum LAYERS {
        static constexpr ObjectLayer NON_MOVING = 0;
        static constexpr ObjectLayer MOVING = 1;
        static constexpr ObjectLayer NUM_LAYERS = 2;
    };

    class PhysicsManager
    {
    public:
        PhysicsManager();
        void addBody(TYPE type,unsigned int id);
        void changeBodyType(TYPE type);
    private:
        BPLayerInterfaceImpl m_broadPhaseLayerInterface;
        ObjectVsBroadPhaseLayerFilterImpl m_objectVsBroadphaseLayerFilter;
        ObjectLayerPairFilterImpl m_objectVsObjectLayerFilter;
        JPH::PhysicsSystem m_physicsSystem;
        const unsigned int m_maxContactConstraints = 10240;
        const unsigned int m_naxBodyPairs = 65536;
        const unsigned int m_naxBodies = 65536;
        const unsigned int m_numBodyMutexes = 0;
        JobSystemThreadPool job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);
        TempAllocatorImpl temp_allocator(10 * 1024 * 1024);
    };

    class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter {
    public:
        virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
    };

} // r8ge
*/