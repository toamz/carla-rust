#pragma once

#include <vector>
#include "carla/geom/Location.h"
#include "carla/rpc/WheelPhysicsControl.h"
#include "carla/rpc/VehiclePhysicsControl.h"
#include "carla_rust/geom.hpp"

namespace carla_rust
{
    namespace rpc {
        using carla::rpc::WheelPhysicsControl;
        using carla::rpc::VehiclePhysicsControl;
        using carla::geom::Vector2D;
        using carla::geom::Location;
        using carla_rust::geom::FfiLocation;

        class FfiWheelPhysicsControl {
        public:
            FfiWheelPhysicsControl() = default;

            FfiWheelPhysicsControl(
                uint8_t in_axle_type,
                geom::Vector3D in_offset,
                float in_wheel_radius,
                float in_wheel_width,
                float in_wheel_mass,
                float in_cornering_stiffness,
                float in_friction_force_multiplier,
                float in_side_slip_modifier,
                float in_slip_threshold,
                float in_skid_threshold,
                float in_max_steer_angle,
                bool in_affected_by_steering,
                bool in_affected_by_brake,
                bool in_affected_by_handbrake,
                bool in_affected_by_engine,
                bool in_abs_enabled,
                bool in_traction_control_enabled,
                float in_max_wheelspin_rotation,
                uint8_t in_external_torque_combine_method,
                const std::vector<geom::Vector2D> &in_lateral_slip_graph,
                geom::Vector3D in_suspension_axis,
                geom::Vector3D in_suspension_force_offset,
                float in_suspension_max_raise,
                float in_suspension_max_drop,
                float in_suspension_damping_ratio,
                float in_wheel_load_ratio,
                float in_spring_rate,
                float in_spring_preload,
                int in_suspension_smoothing,
                float in_rollbar_scaling,
                uint8_t in_sweep_shape,
                uint8_t in_sweep_type,
                float in_max_brake_torque,
                float in_max_hand_brake_torque,
                int32_t in_wheel_index,
                FfiLocation in_location,
                FfiLocation in_old_location,
                FfiLocation in_velocity) {
                    inner_.axle_type = in_axle_type;
                    inner_.offset = in_offset;
                    inner_.wheel_radius = in_wheel_radius;
                    inner_.wheel_width = in_wheel_width;
                    inner_.wheel_mass = in_wheel_mass;
                    inner_.cornering_stiffness = in_cornering_stiffness;
                    inner_.friction_force_multiplier = in_friction_force_multiplier;
                    inner_.side_slip_modifier = in_side_slip_modifier;
                    inner_.slip_threshold = in_slip_threshold;
                    inner_.skid_threshold = in_skid_threshold;
                    inner_.max_steer_angle = in_max_steer_angle;
                    inner_.affected_by_steering = in_affected_by_steering;
                    inner_.affected_by_brake = in_affected_by_brake;
                    inner_.affected_by_handbrake = in_affected_by_handbrake;
                    inner_.affected_by_engine = in_affected_by_engine;
                    inner_.abs_enabled = in_abs_enabled;
                    inner_.traction_control_enabled = in_traction_control_enabled;
                    inner_.max_wheelspin_rotation = in_max_wheelspin_rotation;
                    inner_.external_torque_combine_method = in_external_torque_combine_method;
                    inner_.lateral_slip_graph = in_lateral_slip_graph;
                    inner_.suspension_axis = in_suspension_axis;
                    inner_.suspension_force_offset = in_suspension_force_offset;
                    inner_.suspension_max_raise = in_suspension_max_raise;
                    inner_.suspension_max_drop = in_suspension_max_drop;
                    inner_.suspension_damping_ratio = in_suspension_damping_ratio;
                    inner_.wheel_load_ratio = in_wheel_load_ratio;
                    inner_.spring_rate = in_spring_rate;
                    inner_.spring_preload = in_spring_preload;
                    inner_.suspension_smoothing = in_suspension_smoothing;
                    inner_.rollbar_scaling = in_rollbar_scaling;
                    inner_.sweep_shape = in_sweep_shape;
                    inner_.sweep_type = in_sweep_type;
                    inner_.max_brake_torque = in_max_brake_torque;
                    inner_.max_hand_brake_torque = in_max_hand_brake_torque;
                    inner_.wheel_index = in_wheel_index;
                    inner_.location = reinterpret_cast<const Location&>(in_location);
                    inner_.old_location = reinterpret_cast<const Location&>(in_old_location);
                    inner_.velocity = reinterpret_cast<const Location&>(in_velocity);
            }



            FfiWheelPhysicsControl(WheelPhysicsControl &&base)
                : inner_(std::move(base))
            {}

            uint8_t axle_type() const {
                return inner_.axle_type;
            }

            geom::Vector3D offset() const {
                return inner_.offset;
            }

            float wheel_radius() const {
                return inner_.wheel_radius;
            }

            float wheel_width() const {
                return inner_.wheel_width;
            }

            float wheel_mass() const {
                return inner_.wheel_mass;
            }

            float cornering_stiffness() const {
                return inner_.cornering_stiffness;
            }

            float friction_force_multiplier() const {
                return inner_.friction_force_multiplier;
            }

            float side_slip_modifier() const {
                return inner_.side_slip_modifier;
            }

            float slip_threshold() const {
                return inner_.slip_threshold;
            }

            float skid_threshold() const {
                return inner_.skid_threshold;
            }

            float max_steer_angle() const {
                return inner_.max_steer_angle;
            }

            bool affected_by_steering() const {
                return inner_.affected_by_steering;
            }
            
            bool affected_by_brake() const {
                return inner_.affected_by_brake;
            }

            bool affected_by_handbrake() const {
                return inner_.affected_by_handbrake;
            }

            bool affected_by_engine() const {
                return inner_.affected_by_engine;
            }

            bool abs_enabled() const {
                return inner_.abs_enabled;
            }

            bool traction_control_enabled() const {
                return inner_.traction_control_enabled;
            }

            float max_wheelspin_rotation() const {
                return inner_.max_wheelspin_rotation;
            }

            uint8_t external_torque_combine_method() const {
                return inner_.external_torque_combine_method;
            }
            
            const std::vector<geom::Vector2D>& lateral_slip_graph() const {
                return inner_.lateral_slip_graph;
            }

            geom::Vector3D suspension_axis() const {
                return inner_.suspension_axis;
            }

            geom::Vector3D suspension_force_offset() const {
                return inner_.suspension_force_offset;
            }

            float suspension_max_raise() const {
                return inner_.suspension_max_raise;
            }

            float suspension_max_drop() const {
                return inner_.suspension_max_drop;
            }

            float suspension_damping_ratio() const {
                return inner_.suspension_damping_ratio;
            }

            float wheel_load_ratio() const {
                return inner_.wheel_load_ratio;
            }

            float spring_rate() const {
                return inner_.spring_rate;
            }

            float spring_preload() const {
                return inner_.spring_preload;
            }

            int suspension_smoothing() const {
                return inner_.suspension_smoothing;
            }

            float rollbar_scaling() const {
                return inner_.rollbar_scaling;
            }

            uint8_t sweep_shape() const {
                return inner_.sweep_shape;
            }

            uint8_t sweep_type() const {
                return inner_.sweep_type;
            }

            float max_brake_torque() const {
                return inner_.max_brake_torque;
            }

            float max_hand_brake_torque() const {
                return inner_.max_hand_brake_torque;
            }

            int32_t wheel_index() const {
                return inner_.wheel_index;
            }

            const FfiLocation& location() const {
                return reinterpret_cast<const FfiLocation&>(inner_.location);
            }

            const FfiLocation& old_location() const {
                return reinterpret_cast<const FfiLocation&>(inner_.old_location);
            }

            const FfiLocation& velocity() const {
                return reinterpret_cast<const FfiLocation&>(inner_.velocity);
            }

        private:
            WheelPhysicsControl inner_;
        };

        static_assert(sizeof(FfiWheelPhysicsControl) == sizeof(WheelPhysicsControl), "FfiWheelPhysicsControl has invalid size");
    }
}
