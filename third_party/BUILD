filegroup(
	name = "opengl32_lib",
	srcs = [":opengl32.dll"],
	# output_group = "interface_library",
)

cc_import(
	name = "opengl",
	interface_library = "opengl32.lib",
	shared_library = "opengl32.dll",
	visibility = ["//visibility:public"],
)
