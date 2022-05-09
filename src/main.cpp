﻿#include <iostream>
#include <thread>
#include "render/engine.h"
#include "tooth/engine.h"

#include <communication/AutoBus.hpp>

using namespace std;

int main() {
    thread logic_thread([&]() {
        int scale = 100;
        auto service = ToothSpace::make_service("static", scale);
        service->refresh_edge();
        service->calculate_table("test.csv");
    });
    logic_thread.detach();

    auto renderer = RenderSpace::make_renderer(800, 600);
    return renderer->exec();
}
