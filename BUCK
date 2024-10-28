cxx_binary(
    name = "lotus",
    srcs = glob(["src/*.cpp"]),
    deps = ["//ThirdParty:SDL3_lib", "//ThirdParty:SDL3_dll"],
    compiler_flags = ["/Z7"],
    linker_flags = ["/DEBUG"],
)