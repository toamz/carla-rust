use carla_sys::carla::geom::Vector3D;
use carla_sys::carla_rust::{client::FfiActorSnapshot, geom::FfiTransform};
use cxx::UniquePtr;
use derivative::Derivative;
use static_assertions::assert_impl_all;

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

    pub fn transform(&self) -> FfiTransform {
        self.inner.GetTransform()
    }

    pub fn velocity(&self) -> Vector3D {
        self.inner.GetVelocity()
    }

    pub fn acceleration(&self) -> Vector3D {
        self.inner.GetAcceleration()
    }

    pub fn angular_velocity(&self) -> Vector3D {
        self.inner.GetAngularVelocity()
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
