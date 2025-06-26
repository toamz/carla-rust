#pragma once

#include <memory>
#include "carla/Memory.h"
#include "carla/client/WorldSnapshot.h"
#include "carla/client/Timestamp.h"
#include "carla_rust/rpc/actor_id.hpp"

namespace carla_rust
{
    namespace client {
        using carla::SharedPtr;
        using carla::client::Map;
        using carla::client::WorldSnapshot;
        using carla::client::Timestamp;
        using carla_rust::rpc::FfiActorId;
        using carla_rust::client::FfiActorSnapshot;

        // Map
        class FfiWorldSnapshot {
        public:
            FfiWorldSnapshot(WorldSnapshot &&base)
                : inner_(std::move(base))
            {}

            uint64_t GetId() const {
                return inner_.GetId();
            }

            size_t GetFrame() const {
                return inner_.GetFrame();
            }

            const Timestamp &GetTimestamp() const {
                return inner_.GetTimestamp();
            }

            bool Contains(FfiActorId actor_id) const {
                return inner_.Contains(actor_id);
            }

            std::unique_ptr<FfiActorSnapshot> Find(FfiActorId actor_id) const {
                boost::optional<ActorSnapshot> snapshot = inner_.Find(actor_id);
                if (snapshot) {
                    return std::make_unique<FfiActorSnapshot>(std::move(*snapshot));
                } else {
                    return nullptr;
                }
            }

            size_t size() const {
                return inner_.size();
            }

        private:
            WorldSnapshot inner_;
        };
    }
} // namespace carla_rust
