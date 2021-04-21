#pragma once

#include <Python.h>

#include <string>

namespace tdrl {

	PyObject* LoadPythonClass(const std::string& code, const std::string& class_name);

} // namespace TDRL