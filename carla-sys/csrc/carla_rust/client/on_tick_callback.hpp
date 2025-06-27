#pragma once

#include <memory>
#include "carla/client/WorldSnapshot.h"
#include "carla_rust/client/world_snapshot.hpp"

namespace carla_rust
{
    namespace client {
        using carla_rust::client::FfiWorldSnapshot;

        class OnTickCallback {
        public:
            OnTickCallback(void *caller, void *fn, void *delete_fn)
            {
                auto caller_ptr = reinterpret_cast<void (*) (void* ctx, std::unique_ptr<FfiWorldSnapshot> *data)>(caller);
                auto delete_fn_ptr = reinterpret_cast<void (*) (void* ctx)>(delete_fn);

                caller_ = caller_ptr;
                fn_ = fn;
                delete_fn_ = delete_fn_ptr;
            }

            OnTickCallback(OnTickCallback&&) = default;

            ~OnTickCallback() {
                (delete_fn_)(fn_);
            }

            OnTickCallback& operator=(OnTickCallback&&) = default;

            void operator()(std::unique_ptr<FfiWorldSnapshot> data) const {
                (caller_)(fn_, &data);
            }

        private:
            void (*caller_)(void * fn , std::unique_ptr<FfiWorldSnapshot> *data);
            void * fn_;
            void (*delete_fn_)(void *fn);
        };

    }
} // namespace carla_rust
