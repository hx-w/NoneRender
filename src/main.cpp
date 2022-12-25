﻿#include <iostream>
#include <thread>
#include "render/engine.h"

#include <pybind11/embed.h>
namespace py = pybind11;

using namespace std;

int main() {
    py::scoped_interpreter guard{}; // start the interpreter and keep it alive

    py::print("Hello, World!"); // use the Python API

    cout << "main thread ID: " << this_thread::get_id() << endl;
    auto renderer = RenderSpace::make_renderer(1200, 800);

    // thread ml_thread(train_and_test, 100, renderer->get_service());
    // ml_thread.detach();

    return renderer->exec();
}