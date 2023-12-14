#pragma once
#include <iostream>

#include "definitions.h"

//PCANModule includes
#include "../PCANModule/DataPoint.h"

#include <thread>

#include <vector>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class DisplayManager {
    public:

        DisplayManager();

        DisplayManager(const DisplayManager&) = delete;
        DisplayManager& operator=(const DisplayManager&) = delete;

        DisplayManager(DisplayManager&&) = delete;
        DisplayManager& operator=(DisplayManager&&) = delete;

        void initWindow();

        void onPressureChanged(const DataPointEncoded& dataPointReceived);

        virtual ~DisplayManager();

    private:

        void DisplayThread();
        void writeCSV(const std::string& filename, const std::vector<std::vector<float>*>& measurements);
        std::vector<std::vector<float>*> measurementsVec = {};
        std::vector<float> m_BPData_mBar = {};
        std::vector<float> m_TempData_Celsius = {};
        std::vector<float> m_FlowData_mBar = {};
        std::unique_ptr<std::thread> displayWindowThread {nullptr};

        uint64_t countMsgReceived = 0;
};

