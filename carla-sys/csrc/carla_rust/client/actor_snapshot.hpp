#pragma once

#include <memory>
#include "carla/Memory.h"
#include "carla/client/ActorSnapshot.h"
#include "carla_rust/rpc/actor_id.hpp"

namespace carla_rust
{
    namespace client {
        using carla::client::ActorSnapshot;
        using carla_rust::rpc::FfiActorId;
        using carla_rust::geom::FfiTransform;
        using carla::rpc::ActorState;

        class FfiActorSnapshot {
        public:
            FfiActorSnapshot(ActorSnapshot &&base)
                : inner_(std::move(base))
            {}

            uint32_t GetId() const {
                return inner_.id;
            }

            ActorState GetActorState() const {
                return inner_.actor_state;
            }

            FfiTransform GetTransform() const {
                return FfiTransform(inner_.transform);
            }

            Vector3D GetVelocity() const {
                return Vector3D(inner_.velocity);
            }

            Vector3D GetAngularVelocity() const {
                return Vector3D(inner_.angular_velocity);
            }

            Vector3D GetAcceleration() const {
                return Vector3D(inner_.acceleration);
            }

        private:
            ActorSnapshot inner_;
        };
    }
} // namespace carla_rust
