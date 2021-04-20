cc_library(
	name = "python",
	hdrs = glob(["include/**/*.h"]),
	visibility = ["//visibility:public"],
	includes = [
		"include",
	],
	deps = [
		":python_import",
	]
)

cc_import(
	name = "python_import",
	interface_library = "libs/python36.lib",
	shared_library = "libs/python3.dll",
	visibility = ["//visibility:public"],
)
