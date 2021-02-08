load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:private"])

cc_library(
    name = "application",
    srcs = [
        "application.cc",
    ],
    hdrs = [
        "application.h",
        "entry_point.h",
    ],
)

cc_library(
    name = "tdlr_public",
    hdrs = [
        "tdlr.h",
    ],
    strip_include_prefix = "//src",
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":application",
    ],
)
