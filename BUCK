cxx_binary(
    name = "lotus",
    header_namespace = "lotus",
    srcs = glob(["src/*.cpp"]),
    include_directories = ["include", "//ThirdParty/glm/include", "//ThirdParty/stb_image/include"],
    deps = ["//ThirdParty:SDL3_lib", "//ThirdParty:SDL3_dll", "//ThirdParty:OpenGL", "//ThirdParty:Glad"],
    compiler_flags = ["/Z7", "/GL"],
    linker_flags = ["/DEBUG", "/LTCG"],
)