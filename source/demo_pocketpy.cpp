#include <pybind11/pybind11.h>

namespace py = pybind11;

int main() {
    // Start the interpreter
    py::scoped_interpreter guard{};

    // Hello world!
    py::exec("print('Hello world!')");

    // Create a list
    py::exec("a = [1, 2, 3]");

    // Eval the sum of the list
    auto result = py::eval("sum(a)");
    std::cout << "Sum of the list: " << result.cast<int>() << std::endl;  // 6

    // Bindings
    auto m = py::module_::__main__();
    m.def("add", [](int a, int b) {
        return a + b;
    });

    // Call the function
    std::cout << "Sum of 2 variables: " << m.attr("add")(1, 2).cast<int>() << std::endl;  // 10

    return 0;
}