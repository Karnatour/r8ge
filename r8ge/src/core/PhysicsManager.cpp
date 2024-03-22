//
// Created by vojta on 29.02.2024.
//

#include "PhysicsManager.h"

#include <glm/ext/matrix_transform.hpp>

#include "../video/Video.h"
#include "../video/renderer/Entity.h"

namespace r8ge {
    PhysicsManager::PhysicsManager() {
    }

    PhysicsManager::~PhysicsManager() {
        for (auto i: m_mapBodyIDEntityIndex) {
            m_bodyInterface->RemoveBody(i.first);
            m_bodyInterface->DestroyBody(i.first);
        }
        delete m_physicsSystem;
        delete m_jobSystem;
        JPH::UnregisterTypes();
        delete JPH::Factory::sInstance;
        JPH::Factory::sInstance = nullptr;
    }

    void PhysicsManager::init() {
        JPH::RegisterDefaultAllocator();
        m_tempAllocator.Allocate(10 * 1024 * 1024);
        JPH::Factory::sInstance = new JPH::Factory();
        m_jobSystem = new JPH::JobSystemThreadPool();
        m_jobSystem->Init(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);
        m_physicsSystem = new JPH::PhysicsSystem();
        m_physicsSystem->Init(m_maxBodies, m_numBodyMutexes, m_maxBodyPairs, m_maxContactConstraints,
                              m_broadPhaseLayerInterface, m_objectVsBroadphaseLayerFilter, m_objectVsObjectLayerFilter);
        m_physicsSystem->SetBodyActivationListener(&m_bodyActivationListener);
        m_physicsSystem->SetContactListener(&m_contactListener);
        m_bodyInterface = &m_physicsSystem->GetBodyInterface();
    }

    void PhysicsManager::addBody(video::Entity *entity) {
        if (entity->getBodyCreationSettings().GetShape() == nullptr) {
            R8GE_LOG_ERROR("Entity {} with ID: {} has no body creation settings", entity->getName(),
                           entity->getEntityID());
            return;
        }

        //Already exists no need to add again
        for (const auto &pair: m_mapBodyIDEntityIndex) {
            if (pair.second == entity->getEntityID()) {
                R8GE_LOG_DEBUG("Entity with ID: {} already has a body", entity->getEntityID());
                return;
            }
        }

        JPH::BodyID id = m_bodyInterface->CreateAndAddBody(entity->getBodyCreationSettings(),
                                                           (entity->getBodyCreationSettings().mMotionType ==
                                                            JPH::EMotionType::Static
                                                                ? JPH::EActivation::DontActivate
                                                                : JPH::EActivation::Activate));
        m_bodyInterface->SetLinearVelocity(id, JPH::Vec3(0.0f, 0.0f, 0.0f));
        m_mapBodyIDEntityIndex[id] = entity->getEntityID();
        R8GE_LOG("Physics Manager: added body with ID: {}", id.GetIndex());
    }

    void PhysicsManager::update() {
        m_physicsSystem->Update(static_cast<float>(Video::getTimeStep()->getSeconds()), 1, &m_tempAllocator,
                                m_jobSystem);

        if (m_mapBodyIDEntityIndex.empty()) {
            return;
        }

        for (auto it = m_mapBodyIDEntityIndex.begin(); it != m_mapBodyIDEntityIndex.end();) {
            JPH::RVec3 position = m_bodyInterface->GetCenterOfMassPosition(it->first);
            video::Entity *entity = video::Scene::getEntity(it->second);

            if (entity == nullptr) {
                R8GE_LOG_WARNI("Entity is nullptr probably out of bounds, deleting...");
                m_bodyInterface->RemoveBody(it->first);
                m_bodyInterface->DestroyBody(it->first);
                it = m_mapBodyIDEntityIndex.erase(it);
            } else {
                entity->getTransformation().model = glm::translate(glm::mat4(1.0f),
                                                                   glm::vec3(position.GetX(), position.GetY(),
                                                                             position.GetZ()));
                ++it;
            }
        }
    }


    void PhysicsManager::loggerImpl(const char *inFMT, ...) {
        va_list list;
        va_start(list, inFMT);
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), inFMT, list);
        va_end(list);

        R8GE_LOG("Physics Manager: {}", buffer);
    }

    bool ObjectLayerPairFilterImpl::ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const {
        switch (inObject1) {
            case ObjectLayers::NON_MOVING:
                return inObject2 == ObjectLayers::MOVING;
            case ObjectLayers::MOVING:
                return true;
            default:
                return false;
        }
    }

    BPLayerInterfaceImpl::BPLayerInterfaceImpl() {
        m_objectToBroadPhase[ObjectLayers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
        m_objectToBroadPhase[ObjectLayers::MOVING] = BroadPhaseLayers::MOVING;
    }

    unsigned int BPLayerInterfaceImpl::GetNumBroadPhaseLayers() const {
        return BroadPhaseLayers::NUM_LAYERS;
    }

    JPH::BroadPhaseLayer BPLayerInterfaceImpl::GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const {
        JPH_ASSERT(inLayer < ObjectLayers::NUM_LAYERS);
        return m_objectToBroadPhase[inLayer];
    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    const char *BPLayerInterfaceImpl::GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const {
        switch (static_cast<JPH::BroadPhaseLayer::Type>(inLayer)) {
            case static_cast<JPH::BroadPhaseLayer::Type>(BroadPhaseLayers::NON_MOVING): return "NON_MOVING";
            case static_cast<JPH::BroadPhaseLayer::Type>(BroadPhaseLayers::MOVING): return "MOVING";
            default: JPH_ASSERT(false);
                return "INVALID";
        }
    }
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

    bool ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(JPH::ObjectLayer inLayer1,
                                                          JPH::BroadPhaseLayer inLayer2) const {
        switch (inLayer1) {
            case ObjectLayers::NON_MOVING:
                return inLayer2 == BroadPhaseLayers::MOVING;
            case ObjectLayers::MOVING:
                return true;
            default:
                JPH_ASSERT(false);
                return false;
        }
    }

    JPH::ValidateResult MyContactListener::OnContactValidate(const JPH::Body &inBody1, const JPH::Body &inBody2,
                                                             JPH::RVec3Arg inBaseOffset,
                                                             const JPH::CollideShapeResult &inCollisionResult) {
        R8GE_LOG("Physics Manager: contact validated");
        return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
    }

    void MyContactListener::OnContactAdded(const JPH::Body &inBody1, const JPH::Body &inBody2,
                                           const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) {
        R8GE_LOG("Physics Manager: contact added");
    }

    void MyContactListener::OnContactPersisted(const JPH::Body &inBody1, const JPH::Body &inBody2,
                                               const JPH::ContactManifold &inManifold,
                                               JPH::ContactSettings &ioSettings) {
        R8GE_LOG("Physics Manager: contact persisted");
    }

    void MyContactListener::OnContactRemoved(const JPH::SubShapeIDPair &inSubShapePair) {
        R8GE_LOG("Physics Manager: contact was removed");
    }

    void MyBodyActivationListener::OnBodyActivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) {
        R8GE_LOG("Physics Manager: body with ID {} woke up", inBodyID.GetIndex());
    }

    void MyBodyActivationListener::OnBodyDeactivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) {
        R8GE_LOG("Physics Manager: body with ID {} went to sleep", inBodyID.GetIndex());
    }
} // r8ge
