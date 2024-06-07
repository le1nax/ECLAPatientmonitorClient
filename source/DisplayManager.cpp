#include "../include/DisplayManager.h"
#include "../include/DisplayApplication.h"
#include <fstream>
#include <sstream>
#include <iomanip>

#define LOCALIP "127.0.0.1"
#define LOCALPORT 12345

// #include <mat.h>

DisplayManager::DisplayManager() : lruCache(numberOfCanIdsInCache)
{
    idMan = std::make_unique<IdManager>("../ParseECLA/SmartECLA_IDs.h");
    canHashMap = idMan->getIdDict();
    //add every measurement stream to vector
    // measurementsVec.push_back(&m_BPData_mBar);
    // measurementsVec.push_back(&m_TempData_Celsius);
    // measurementsVec.push_back(&m_FlowData_mBar);
    
}

void DisplayManager::initWindow()
{
    if(displayWindowThread && displayWindowThread->joinable())
    {
        displayWindowThread->join(); 
    }
    displayWindowThread = std::make_unique<std::thread>(&DisplayManager::DisplayThread, this);
}

void DisplayManager::setLRUCacheCapacity(uint8_t capacity)
{
    lruCache.setCapacity(capacity);
}

/// @todo Config Datei auslesen und Dateninterpretation anpassen 
void DisplayManager::handleDataPoints(const DataPointEncoded& dataPointReceived)
{
    auto receivedCanId = dataPointReceived.canID;
    Id* idStructPtr = lruCache.get(receivedCanId);
    if (idStructPtr) {
        // Found in cache, search for index
        auto it = measurementsCanIDs2VecIndex.find(receivedCanId);
        if (it != measurementsCanIDs2VecIndex.end()) {
            // Add measurement data to the corresponding MeasurementVector
            m_measurementsVec[it->second].addMeasurement(dataPointReceived.value);
        } else {
            throw std::runtime_error("Index not found in measurementsCanIDs2VecIndex for canId: " + std::to_string(dataPointReceived.canID));
        }
    } else {
        // search in canHashMap
        auto it = canHashMap.find(receivedCanId);
        if (it != canHashMap.end()) {
            // Found in canHashMap
    
            MeasurementVector newMeasurementVector(*it->second);
            newMeasurementVector.addMeasurement(dataPointReceived.value);

            //add to LRUCache
            lruCache.put(receivedCanId, *it->second);
            
            //add to m_measurementsVec
            ///@todo Abfrage imGUI
            m_measurementsVec.push_back(newMeasurementVector);
            size_t newIndex = m_measurementsVec.size() - 1;

            //add index to measurementsCanIDs2VecIndex
            measurementsCanIDs2VecIndex[receivedCanId] = newIndex;
        } else {
            //if canId not found in canHashMap
            throw std::runtime_error("canId not found in canHashMap: " + std::to_string(receivedCanId));
        }
    }
    // float readData = dataPointReceived.value;
    // switch (static_cast<EnumCanID>(dataPointReceived.canID))
    // {
    // case EnumCanID::PRESS:
    //     m_BPData_mBar.push_back(readData*canPressConversionFactor);
    //     if(m_CyclicBPData_mBar.size() < maxNumberOfPressValues){
    //         m_CyclicBPData_mBar.push_back(readData*canPressConversionFactor);
    //         break;
    //     }
    //     //else: Reset Cyclic Plot Vector
    //     m_CyclicBPData_mBar.clear();
    //     m_CyclicBPData_mBar.push_back(readData*canPressConversionFactor);
    //     break;
    // case EnumCanID::TEMP:
    //     m_TempData_Celsius.push_back(readData*canTempConversionFactor);
    //     if(m_CyclicBPData_mBar.size() < maxNumberOfPressValues){
    //         m_CyclicTempData_Celsius.push_back(readData*canTempConversionFactor);
    //         break;
    //     }
    //     //else: Reset Cyclic Plot Vector
    //     m_CyclicBPData_mBar.clear();
    //     m_CyclicTempData_Celsius.push_back(readData*canTempConversionFactor);
    //     break;
    // ///@todo
    // case EnumCanID::SFM3300:
    //     m_FlowData_mBar.push_back(readData*canPressConversionFactor);
    //     m_CyclicFlowData_mBar.push_back(readData*canPressConversionFactor);

    // ///@todo default case definieren
    // default:
    //     std::cout <<  "Invalid canID: " << dataPointReceived.canID << std::endl;
    //     break;
    // }
}


void DisplayManager::writeCSV(const std::string& filename, const std::vector<MeasurementVector>& data) {

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // get min size
    size_t minSize = std::numeric_limits<size_t>::max();
    for (const auto& vec : data) {
        minSize = std::min(minSize, vec.getMeasurements().size());
    }

    for (size_t i = 0; i < minSize; ++i) {
        for (const auto& vec : data) {
            if(configModeDebug){ 
                std::cout <<  "rowValue: " << vec.getMeasurements().at(i) << std::endl;
            }
            file << vec.getMeasurements().at(i) << ","; //write content of vec into csv
        }
        file << "\n"; // next row
    }

    // Close the file
    file.close();
    std::cout <<  "CSV file created: " << filename << std::endl;
}

void DisplayManager::setAppInstance(DisplayApplication* instanceA) {
        appInstance = instanceA;
    }

void DisplayManager::convertToMat(const std::string& csvFilename, const std::string& matFilename) {

    // std::ifstream csvFile(csvFilename);
    // std::string line;
    // std::vector<std::vector<double>> data;

    // while (std::getline(csvFile, line)) {
    //     std::vector<double> row;
    //     std::istringstream iss(line);
    //     std::string value;
    //     while (std::getline(iss, value, ',')) {
    //         row.push_back(std::stod(value));
    //     }
    //     data.push_back(row);
    // }

    // MATFile* matFile = matOpen(matFilename.c_str(), "w");
    // if (matFile == nullptr) {
    //     std::cerr << "Error creating MAT file: " << matFilename << std::endl;
    //     return;
    // }

    // const char* varName = "data";
    // mxArray* mxData = mxCreateDoubleMatrix(data.size(), data[0].size(), mxREAL);

    // double* pData = mxGetPr(mxData);
    // size_t index = 0;
    // for (const auto& row : data) {
    //     for (const auto& value : row) {
    //         pData[index++] = value;
    //     }
    // }

    // matPutVariable(matFile, varName, mxData);
    // matClose(matFile);

    // if(configModeDebug){ 
        //std::cout <<  "MAT file created: " << matFilename << std::endl;
}


void DisplayManager::DisplayThread()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return;

    // Decide GL+GLSL versions

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    GLFWwindow* window = glfwCreateWindow(1280, 720, "BP View Debug Version", nullptr, nullptr);
    if (window == nullptr)
        return;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    while (!glfwWindowShouldClose(window)) {
        glfwMainLoop();

        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwTerminate();
}

void DisplayManager::PlotVector(const char* label, std::vector<float> values, int64_t yLowerLimit, int64_t yUpperLimit) {
    // values.resize(maxNumberOfPressValues, 0.0f);
    if (ImPlot::BeginPlot(label, NULL, NULL, ImVec2(800, 300))) {
        ImPlotAxisFlags plotFlags = ImPlotAxisFlags_NoGridLines;
        ImPlot::SetupAxesLimits(0, maxNumberOfPressValues, yLowerLimit, yUpperLimit);
        ImPlot::SetupAxis(ImAxis_X1, "Sample Point", plotFlags);
        ImPlot::SetupAxis(ImAxis_Y1, label);
        ImPlot::PlotLine(label, values.data(), static_cast<int>(values.size()), 1.0, 0.0, ImPlotFlags_NoLegend);
        // auto size = values.size();
        ImPlot::EndPlot();
    }
    else{
        std::cout << "Could not Plot vector: " + std::string(label) << std::endl;
    }
}

void DisplayManager::glfwMainLoop()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("PatientMonitorClient", NULL, ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::BeginTabBar("Client")) {

        if (ImGui::BeginTabItem("Monitor")) {
            // Content of Tab 1
            for(const auto& it : m_measurementsVec){
                ///@todo abgleich mit xml inputs
                PlotVector(it.name.c_str(), it.getCylclicMeasurements(), it.min, it.max);
            }
            // PlotVector("BP [mBar]", m_CyclicBPData_mBar, lowestCanPressValue, highestCanPressValue);

            // PlotVector("Temperature [°C]", m_CyclicTempData_Celsius, lowestCanTemperatureValue, highestCanTemperatureValue);

            if (ImGui::Button("Export Data to .csv and .mat")) {
                writeCSV("measurements.csv", m_measurementsVec);
                convertToMat("measurements.csv", "measurements.mat");
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Config")) {
            // Content of Tab 2
            static char inputBufferIp[128] = "";
            static char inputBufferPort[128] = "";

            ImGui::Text("Server IP");
            ImGui::InputTextWithHint("##serverIp", "Enter server ip", inputBufferIp, IM_ARRAYSIZE(inputBufferIp));

            ImGui::Text("Server Port");
            ImGui::InputTextWithHint("##serverPort", "Enter server port", inputBufferPort, IM_ARRAYSIZE(inputBufferPort));

            std::string inputIp = inputBufferIp; 
            unsigned short inputPort = static_cast<unsigned short>(std::strtoul(inputBufferPort, nullptr, 10));

            if (ImGui::Button("connect")) {
                receiveThread = std::make_unique<std::thread>(&DisplayApplication::connect, appInstance, inputIp, inputPort);
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar(); // End the tab bar
    }

    ImGui::End();//end window
}

DisplayManager::~DisplayManager()
{
    if(displayWindowThread && displayWindowThread->joinable()) {
        displayWindowThread->join();
    }
}