load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository", "git_repository")

new_git_repository(
    name = "glew",
    remote = "https://github.com/Lunarsong/glew.git",
    commit = "a38094b249974f219f9c23f54b5b60a620777a13",
    build_file = "glew.BUILD",
)

new_local_repository(
    name = "glfw",
    path = "third_party/glfw",
    build_file = "third_party/glfw/glfw.BUILD",
)

new_local_repository(
    name = "spdlog",
    path = "third_party/spdlog",
    build_file = "third_party/spdlog.BUILD",
)

new_local_repository(
    name = "opengl",
	path = "C:/Windows/System32",
    build_file = "third_party/opengl.BUILD",
)
