use cmake;
use std::env;
use std::path::{Path, PathBuf};

fn main() {
    let mylib_dir = Path::new(".").join("external").join("mylib");
    let mylib_name = match env::var("DEBUG").unwrap_or(String::from("false")).as_str() {
        "true" => "mylib-d",
        _ => "mylib",
    };

    // (cmake-)build mylib
    let out_path = cmake::Config::new(mylib_dir.as_path())
        // .define("BUILD_SHARED_LIBS", "ON")
        .build();

    println!(
        "cargo:rustc-link-search=native={}",
        out_path.join("lib").display()
    );
    println!("cargo:rustc-link-lib={}={}", "static", mylib_name);

    // create bindings for mylib
    let bindings = bindgen::Builder::default()
        .use_core()
        .ctypes_prefix("cty")
        .rustified_enum("mylib_error_t")
        .header(mylib_dir.join("include").join("mylib.h").to_str().unwrap())
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
