#pragma once

#include <vector>
#include "carla/geom/Location.h"
#include "carla/rpc/WheelPhysicsControl.h"
#include "carla/rpc/VehiclePhysicsControl.h"
#include "carla_rust/geom.hpp"
#include "carla_rust/rpc/wheel_physics_control.hpp"

namespace carla_rust
{
    namespace rpc {
        using carla::rpc::WheelPhysicsControl;
        using carla::rpc::VehiclePhysicsControl;
        using carla::geom::Vector2D;
        using carla::geom::Location;
        using carla_rust::geom::FfiLocation;
        using carla_rust::rpc::FfiWheelPhysicsControl;

        class FfiVehiclePhysicsControl {
        public:
            FfiVehiclePhysicsControl() = default;

            FfiVehiclePhysicsControl(
                const std::vector<Vector2D> &in_torque_curve,
                float in_max_rpm,
                float in_rev_up_moi,
                bool in_use_automatic_gears,
                float in_gear_change_time,
                float in_final_ratio,
                std::vector<float> &in_forward_gear_ratios,
                float in_change_up_rpm,
                float in_change_down_rpm,
                float in_mass, float in_drag_coefficient,
                FfiLocation &in_center_of_mass,
                const std::vector<Vector2D> &in_steering_curve,
                //std::vector<FfiWheelPhysicsControl> &in_wheels,
                bool in_use_sweep_wheel_collision) {
                    inner_.torque_curve = in_torque_curve;
                    inner_.max_rpm = in_max_rpm;
                    inner_.rev_up_moi = in_rev_up_moi;
                    inner_.use_automatic_gears = in_use_automatic_gears;
                    inner_.gear_change_time = in_gear_change_time;
                    inner_.final_ratio = in_final_ratio;
                    inner_.forward_gear_ratios = in_forward_gear_ratios;
                    inner_.change_up_rpm = in_change_up_rpm;
                    inner_.change_down_rpm = in_change_down_rpm;
                    inner_.mass = in_mass;
                    inner_.drag_coefficient = in_drag_coefficient;
                    inner_.center_of_mass = reinterpret_cast<const Location&>(in_center_of_mass);
                    inner_.steering_curve = in_steering_curve;
                    // inner_.wheels = reinterpret_cast<const std::vector<WheelPhysicsControl>&>(in_wheels);
                    // TODO: Cannot pass as CxxVector because this type is Opaque and autocxx doesn't support it
                    // Option would be to use rust::Vec from cxx or make some wrapper which is not opaque
                    inner_.use_sweep_wheel_collision = in_use_sweep_wheel_collision;
            }



            FfiVehiclePhysicsControl(VehiclePhysicsControl &&base)
                : inner_(std::move(base))
            {}

            const std::vector<Vector2D>& torque_curve() const {
                return inner_.torque_curve;
            }

            float max_rpm() const {
                return inner_.max_rpm;
            }

            float rev_up_moi() const {
                return inner_.rev_up_moi;
            }

            bool use_automatic_gears() const {
                return inner_.use_automatic_gears;
            }

            float gear_change_time() const {
                return inner_.gear_change_time;
            }

            float final_ratio() const {
                return inner_.final_ratio;
            }

            const std::vector<float>& forward_gear_ratios() const {
                return inner_.forward_gear_ratios;
            }

            float change_up_rpm() const {
                return inner_.change_up_rpm;
            }

            float change_down_rpm() const {
                return inner_.change_down_rpm;
            }

            float mass() const {
                return inner_.mass;
            }

            float drag_coefficient() const {
                return inner_.drag_coefficient;
            }

            const FfiLocation& center_of_mass() const {
                return reinterpret_cast<const FfiLocation&>(inner_.center_of_mass);
            }

            const std::vector<Vector2D>& steering_curve() const {
                return inner_.steering_curve;
            }

            const std::vector<FfiWheelPhysicsControl>& wheels() const {
                return reinterpret_cast<const std::vector<FfiWheelPhysicsControl>&>(inner_.wheels);
            }

            bool use_sweep_wheel_collision() const {
                return inner_.use_sweep_wheel_collision;
            }


            const VehiclePhysicsControl& inner() const {
                return inner_;
            }

        private:
            VehiclePhysicsControl inner_;
        };

        static_assert(sizeof(FfiVehiclePhysicsControl) == sizeof(VehiclePhysicsControl), "FfiVehiclePhysicsControl has invalid size");
    }
}
