#pragma once

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

#include <iostream>
#include <cstdarg>
#include <thread>


namespace JPH {
    class Factory;
}

namespace r8ge {
    namespace video {
        class Entity;
    }

    namespace ObjectLayers {
        static constexpr JPH::ObjectLayer NON_MOVING = 0;
        static constexpr JPH::ObjectLayer MOVING = 1;
        static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
    }

    class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter {
    public:
        [[nodiscard]] bool ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override;
    };

    namespace BroadPhaseLayers {
        static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
        static constexpr JPH::BroadPhaseLayer MOVING(1);
        static constexpr unsigned int NUM_LAYERS(2);
    }

    class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface {
    public:
        BPLayerInterfaceImpl();

        [[nodiscard]] unsigned int GetNumBroadPhaseLayers() const override;

        [[nodiscard]] JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override;

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
        const char *GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override;
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

    private:
        JPH::BroadPhaseLayer m_objectToBroadPhase[ObjectLayers::NUM_LAYERS];
    };

    class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter {
    public:
        [[nodiscard]] bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override;
    };

    class MyContactListener : public JPH::ContactListener {
    public:
        JPH::ValidateResult OnContactValidate(const JPH::Body &inBody1, const JPH::Body &inBody2,
                                              JPH::RVec3Arg inBaseOffset,
                                              const JPH::CollideShapeResult &inCollisionResult) override;

        void OnContactAdded(const JPH::Body &inBody1, const JPH::Body &inBody2, const JPH::ContactManifold &inManifold,
                            JPH::ContactSettings &ioSettings) override;

        void OnContactPersisted(const JPH::Body &inBody1, const JPH::Body &inBody2,
                                const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) override;

        void OnContactRemoved(const JPH::SubShapeIDPair &inSubShapePair) override;
    };

    class MyBodyActivationListener : public JPH::BodyActivationListener {
    public:
        void OnBodyActivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override;

        void OnBodyDeactivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override;
    };

    class PhysicsManager {
    public:
        PhysicsManager();

        ~PhysicsManager();

        void addBody(video::Entity *entity);

        void init();

        void update();

    private:
        static void loggerImpl(const char *inFMT, ...);

        const unsigned int m_maxContactConstraints = 10240;
        const unsigned int m_maxBodyPairs = 65536;
        const unsigned int m_maxBodies = 65536;
        const unsigned int m_numBodyMutexes = 0;

        std::unordered_map<JPH::BodyID,unsigned int> m_mapBodyIDEntityIndex;
        JPH::TempAllocatorMalloc m_tempAllocator;
        MyBodyActivationListener m_bodyActivationListener;
        MyContactListener m_contactListener;
        BPLayerInterfaceImpl m_broadPhaseLayerInterface;
        ObjectVsBroadPhaseLayerFilterImpl m_objectVsBroadphaseLayerFilter;
        ObjectLayerPairFilterImpl m_objectVsObjectLayerFilter;
        JPH::JobSystemThreadPool *m_jobSystem;
        JPH::PhysicsSystem *m_physicsSystem;
        JPH::BodyInterface *m_bodyInterface;
    };
} // r8ge
