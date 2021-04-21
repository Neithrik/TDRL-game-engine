#include "Sandbox.h"

#include <iostream>

namespace tdrl {

	PyObject* LoadPythonClass(const std::string& code, const std::string& class_name) {
		std::cout << "Loading Python class" << std::endl;

		Py_Initialize();

		const char *MyModuleName = "agent";
		const char *MyModuleCode = const_cast<char*>(code.c_str());

		PyObject *module = Py_CompileString(MyModuleCode, "", Py_file_input);

		PyObject *python_module = PyImport_ExecCodeModule(MyModuleName, module);
		
		if (python_module == nullptr) {
			std::cout << "Python module is nullptr" << std::endl;
			PyErr_Print();
		}
		else {
			std::cout << "Python module is not nullptr" << std::endl;
		}

		if (!PyModule_Check(python_module)) {
			std::cout << "Invalid Python code" << std::endl;
		}
		else {
			std::cout << "Valid Python code" << std::endl;
		}

		PyObject* dict = PyModule_GetDict(python_module);

		if (dict == nullptr) {
			std::cout << "Python dict is nullptr" << std::endl;
			PyErr_Print();
		}
		else {
			std::cout << "Python dict is not nullptr" << std::endl;
			PyObject* dictRepresentation = PyObject_Repr(dict);
			std::cout << PyUnicode_AsUTF8(dictRepresentation) << std::endl;
		}

		PyObject* class_object = PyDict_GetItemString(dict, const_cast<char*>(class_name.c_str()));

		PyObject* instance = PyObject_CallObject(class_object, nullptr);

		return instance;
	}

} // namespace TDRL