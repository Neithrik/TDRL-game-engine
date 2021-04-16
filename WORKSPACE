load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "bazel_skylib",
    urls = [
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.0.3/bazel-skylib-1.0.3.tar.gz",
    ],
    sha256 = "1c531376ac7e5a180e0237938a2536de0c54d93f5c278634818e0efc952dd56c",
)
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
bazel_skylib_workspace()

new_git_repository(
    name = "glew",
    remote = "https://github.com/Lunarsong/glew.git",
    commit = "a38094b249974f219f9c23f54b5b60a620777a13",
    build_file = "glew.BUILD",
)

new_git_repository(
    name = "org_tensorflow",
    remote = "https://github.com/tensorflow/tensorflow",
	build_file_content = " ",
	branch = "master",
)
load("@org_tensorflow//tensorflow:workspace3.bzl", "tf_workspace3")
tf_workspace3()
load("@org_tensorflow//tensorflow:workspace2.bzl", "tf_workspace2")
tf_workspace2()
load("@org_tensorflow//tensorflow:workspace1.bzl", "tf_workspace1")
tf_workspace1()
load("@org_tensorflow//tensorflow:workspace0.bzl", "tf_workspace0")
tf_workspace0()

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
