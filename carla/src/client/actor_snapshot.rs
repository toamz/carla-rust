use carla_sys::carla_rust::client::FfiActorSnapshot;
use cxx::UniquePtr;
use derivative::Derivative;
use nalgebra::{Isometry3, Vector3};
use static_assertions::assert_impl_all;

use crate::geom::{TransformExt, Vector3DExt};

#[derive(Derivative)]
#[derivative(Debug)]
#[repr(transparent)]
pub struct ActorSnapshot {
    #[derivative(Debug = "ignore")]
    inner: UniquePtr<FfiActorSnapshot>,
}

impl ActorSnapshot {
    pub fn id(&self) -> u32 {
        self.inner.GetId()
    }

    pub fn transform(&self) -> Isometry3<f32> {
        self.inner.GetTransform().to_na()
    }

    pub fn velocity(&self) -> Vector3<f32> {
        self.inner.GetVelocity().to_na()
    }

    pub fn acceleration(&self) -> Vector3<f32> {
        self.inner.GetAcceleration().to_na()
    }

    pub fn angular_velocity(&self) -> Vector3<f32> {
        self.inner.GetAngularVelocity().to_na()
    }

    pub(crate) fn from_cxx(ptr: UniquePtr<FfiActorSnapshot>) -> Option<Self> {
        if ptr.is_null() {
            None
        } else {
            Some(Self { inner: ptr })
        }
    }
}

assert_impl_all!(ActorSnapshot: Send);
