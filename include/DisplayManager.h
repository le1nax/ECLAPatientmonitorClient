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


/// @brief callback function of a glfw error thrown
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


class DisplayManager {
    public:

        /// @brief constructor of the DisplayManager, in which the measurement vectors are filled on runtime
        DisplayManager();

        DisplayManager(const DisplayManager&) = delete;
        DisplayManager& operator=(const DisplayManager&) = delete;

        DisplayManager(DisplayManager&&) = delete;
        DisplayManager& operator=(DisplayManager&&) = delete;

        /// @brief initializes the ImGui Window
        void initWindow();
        
        /// @brief Custom IO function, that plots the measurement vector 
        /// @param label The corresponding label of the Plot
        /// @param values The measurement vector that is plotted
        void PlotVector(const char* label, const std::vector<float>& values);

        /// @brief The slot which handles the incoming DataPoint
        /// @param dataPointReceived Encoded DataPoint that is handled
        void onPressureChanged(const DataPointEncoded& dataPointReceived);

        virtual ~DisplayManager();

    private:

        ///@brief Imgui Window is initialized, Data is plotted
        void DisplayThread();
        /// @brief Creates a CSV file with the Measurements in each column
        /// @param filename The Filename of the created csv file
        /// @param measurements The vector of the measurements
        void writeCSV(const std::string& filename, const std::vector<std::vector<float>*>& measurements);

        /// @brief Measurements are stored in std::vectors which are stored in a std::vector measurementsVec. It is filled on runtime on runtime
        std::vector<std::vector<float>*> measurementsVec = {};

        /// @brief The measurements of Honeywell pressure
        std::vector<float> m_BPData_mBar = {};
        /// @brief The measurements of Honeywell temperature
        std::vector<float> m_TempData_Celsius = {};
        /// @brief the measurements of SFM3300 data
        std::vector<float> m_FlowData_mBar = {};
        /// @brief thread, that displays the ImGui Window
        std::unique_ptr<std::thread> displayWindowThread {nullptr};
        //debug Value
        uint64_t countMsgReceived = 0;
        
        std::ofstream file;
        size_t measurementCount;
};

