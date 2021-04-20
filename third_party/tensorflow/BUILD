cc_library(
	name = "tensorflow",
	hdrs = glob(["include/**/*.h"]),
	visibility = ["//visibility:public"],
	includes = [
		"include",
	],
	deps = [
		":tensorflow_import",
	]
)

cc_import(
	name = "tensorflow_import",
	interface_library = "lib/tensorflow.lib",
	shared_library = "lib/tensorflow.dll",
	visibility = ["//visibility:public"],
)
