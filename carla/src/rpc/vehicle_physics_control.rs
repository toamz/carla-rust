use crate::{
    geom::{Location, LocationExt, Vector2D, Vector2DExt},
    utils::IteratorExt,
};
use autocxx::prelude::*;
use carla_sys::{
    carla::rpc::WheelPhysicsControl,
    carla_rust::rpc::FfiVehiclePhysicsControl,
};
use nalgebra::{Translation3, Vector2};

#[derive(Debug, Clone)]
pub struct VehiclePhysicsControl {
    pub torque_curve: Vec<Vector2<f32>>,
    pub max_rpm: f32,
    pub rev_up_moi: f32,
    pub use_automatic_gears: bool,
    pub gear_change_time: f32,
    pub final_ratio: f32,
    pub forward_gear_ratios: Vec<f32>,
    pub change_up_rpm: f32,
    pub change_down_rpm: f32,
    pub mass: f32,
    pub drag_coefficient: f32,
    pub center_of_mass: Translation3<f32>,
    pub steering_curve: Vec<Vector2<f32>>,
    //pub wheels: Vec<WheelPhysicsControl>,
    pub use_sweep_wheel_collision: bool,
}

impl VehiclePhysicsControl {
    pub fn to_cxx(&self) -> UniquePtr<FfiVehiclePhysicsControl> {
        let Self {
            ref torque_curve,
            max_rpm,
            rev_up_moi,
            use_automatic_gears,
            gear_change_time,
            final_ratio,
            ref forward_gear_ratios,
            change_up_rpm,
            change_down_rpm,
            mass,
            drag_coefficient,
            ref center_of_mass,
            ref steering_curve,
            //ref wheels,
            use_sweep_wheel_collision,
        } = *self;

        let torque_curve = torque_curve
            .iter()
            .map(Vector2D::from_na)
            .collect_cxx_vector();
        let steering_curve = steering_curve
            .iter()
            .map(Vector2D::from_na)
            .collect_cxx_vector();
        let mut center_of_mass = Box::pin(Location::from_na_translation(center_of_mass));
        let mut forward_gear_ratios = forward_gear_ratios.iter().cloned().collect_cxx_vector();
        //let mut wheels = wheels.iter().cloned().collect_cxx_vector();

        FfiVehiclePhysicsControl::new1(
            &torque_curve,
            max_rpm,
            rev_up_moi,
            use_automatic_gears,
            gear_change_time,
            final_ratio,
            forward_gear_ratios.pin_mut(),
            change_up_rpm,
            change_down_rpm,
            mass,
            drag_coefficient,
            center_of_mass.as_mut(),
            &steering_curve,
            //wheels.pin_mut(),
            use_sweep_wheel_collision,
        )
        .within_unique_ptr()
    }

    pub fn from_cxx(from: &FfiVehiclePhysicsControl) -> Self {
        Self {
            torque_curve: from.torque_curve().iter().map(|v| v.to_na()).collect(),
            max_rpm: from.max_rpm(),
            rev_up_moi: from.rev_up_moi(),
            use_automatic_gears: from.use_automatic_gears(),
            gear_change_time: from.gear_change_time(),
            final_ratio: from.final_ratio(),
            forward_gear_ratios: from.forward_gear_ratios().iter().cloned().collect(),
            change_up_rpm: from.change_up_rpm(),
            change_down_rpm: from.change_down_rpm(),
            mass: from.mass(),
            drag_coefficient: from.drag_coefficient(),
            center_of_mass: from.center_of_mass().to_na_translation(),
            steering_curve: from.steering_curve().iter().map(|v| v.to_na()).collect(),
            //wheels: from.wheels().iter().cloned().collect(),
            use_sweep_wheel_collision: from.use_sweep_wheel_collision(),
        }
    }
}
