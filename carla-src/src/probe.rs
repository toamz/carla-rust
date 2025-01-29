use std::path::{Path, PathBuf};

use anyhow::{bail, ensure, Result};

#[derive(Debug, Clone)]
pub struct Probe {
    pub prefix: PathBuf,
    pub include_dirs: IncludeDirs,
    pub lib_dirs: LibDirs,
}

#[derive(Debug, Clone)]
pub struct IncludeDirs {
    pub carla_source: PathBuf,
    pub carla_third_party: PathBuf,
    pub recast: PathBuf,
    pub rpclib: PathBuf,
    pub boost: Vec<PathBuf>,
    pub libpng: PathBuf,
}

#[derive(Debug, Clone)]
pub struct LibDirs {
    pub recast: Vec<PathBuf>,
    pub rpclib: PathBuf,
    pub boost: Vec<PathBuf>,
    pub libpng: PathBuf,
    pub libcarla_client: PathBuf,
}

impl IncludeDirs {
    pub fn into_vec(self) -> Vec<PathBuf> {
        let Self {
            recast,
            rpclib,
            mut boost,
            libpng,
            carla_source,
            carla_third_party,
        } = self;
        let mut result = vec![
            recast,
            rpclib,
            libpng,
            carla_source,
            carla_third_party,
        ];
        result.append(&mut boost);
        
        result
    }
}

impl LibDirs {
    pub fn into_vec(self) -> Vec<PathBuf> {
        let Self {
            mut recast,
            rpclib,
            mut boost,
            libpng,
            libcarla_client,
        } = self;
        let mut result = vec![
            rpclib,
            libpng,
            libcarla_client,
        ];
        result.append(&mut boost);
        result.append(&mut recast);
        
        result
    }
}

pub fn probe<P>(carla_src_dir: P) -> Result<Probe>
where
    P: AsRef<Path>,
{
    let find_match = |pattern: &str| -> Result<_> {
        let mut iter = glob::glob(pattern)?;

        let path = match iter.next() {
            Some(Ok(path)) => path,
            Some(Err(err)) => return Err(err.into()),
            None => bail!("Unable to match '{pattern}'"),
        };
        ensure!(
            iter.next().is_none(),
            "'{pattern}' matches more than one file"
        );
        Ok(path)
    };

    let carla_src_dir = carla_src_dir.as_ref();
    let carla_source_dir = carla_src_dir.join("LibCarla").join("source");
    let carla_third_party_dir = carla_source_dir.join("third-party");
    let build_dir = carla_src_dir.join("Build");

    let recast_dir = find_match(build_dir.join("_deps/recastnavigation-src/Recast").to_str().unwrap())?;
    let rpclib_dir = find_match(
        build_dir
            .join("_deps/rpclib-src/")
            .to_str()
            .unwrap(),
    )?;
    let boost_dirs: Vec<PathBuf> = glob::glob(build_dir.join("_deps/boost-src/libs/*/include").to_str().unwrap())?.flatten().collect();

    let libpng_dir = build_dir.join("_deps/libpng-src");
    ensure!(
        libpng_dir.exists(),
        "Unable to find '{}'",
        libpng_dir.display()
    );

    let libcarla_client_lib_dir = build_dir
        .join("LibCarla");
    ensure!(
        libpng_dir.exists(),
        "Unable to find '{}'",
        libcarla_client_lib_dir.display()
    );

    let include_dirs = IncludeDirs {
        carla_source: carla_source_dir,
        carla_third_party: carla_third_party_dir,
        recast: recast_dir.join("Include"),
        rpclib: rpclib_dir.join("include"),
        boost: boost_dirs,
        libpng: libpng_dir.clone(),
    };
    let lib_dirs = LibDirs {
        recast: vec![
            build_dir.join("_deps/recastnavigation-build/Recast"),
            build_dir.join("_deps/recastnavigation-build/DetourCrowd"),
            build_dir.join("_deps/recastnavigation-build/Detour"),
        ],
        rpclib: build_dir.join("_deps/rpclib-build"),
        boost: vec![
            build_dir.join("_deps/boost-build/libs/filesystem"),
        ],
        libpng: build_dir.join("_deps/libpng-build"),
        libcarla_client: libcarla_client_lib_dir,
    };

    Ok(Probe {
        prefix: carla_src_dir.to_path_buf(),
        include_dirs,
        lib_dirs,
    })
}
