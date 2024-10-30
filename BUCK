cxx_binary(
    name = "lotus",
    header_namespace = "lotus",
    srcs = glob(["src/*.cpp"]),
    include_directories = ["include"],
    deps = ["//ThirdParty:SDL3_lib", "//ThirdParty:SDL3_dll", "//ThirdParty:GLEW_lib"],
    compiler_flags = ["/Z7"],
    linker_flags = ["/DEBUG"],
)