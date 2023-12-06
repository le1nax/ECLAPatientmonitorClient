#include "../include/DisplayManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <mat.h>

DisplayManager::DisplayManager()
{
    //add every measurement stream to vector
    measurementsVec.push_back(&m_BPData_mBar);
    measurementsVec.push_back(&m_TempData_Celsius);
    
}

void DisplayManager::initWindow()
{
    if(displayWindowThread && displayWindowThread->joinable())
    {
        displayWindowThread->join(); 
    }
    displayWindowThread = std::make_unique<std::thread>(&DisplayManager::DisplayThread, this);
}

void DisplayManager::onPressureChanged(const DataPointEncoded& dataPointReceived)
{
    float readData = dataPointReceived.value;
    switch (static_cast<EnumCanID>(dataPointReceived.canID))
    {
    case EnumCanID::PRESS:
        m_BPData_mBar.push_back(readData*canPressConversionFactor);
        break;
    case EnumCanID::TEMP:
        m_TempData_Celsius.push_back(readData*canTempConversionFactor);
        break;
    
    default:
        std::cout << "Invalid canID: " << dataPointReceived.canID << std::endl;
        break;
    }
}


void DisplayManager::writeCSV(const std::string& filename, const std::vector<std::vector<float>*>& data) {

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // get min size
    size_t minSize = std::numeric_limits<size_t>::max();
    for (const auto& vec : data) {
        minSize = std::min(minSize, vec->size());
    }

    for (size_t i = 0; i < minSize; ++i) {
        for (const auto& vec : data) {
            std::cout << "rowValue: " << vec->at(i) << std::endl;
            file << vec->at(i) << ","; //write content of vec into csv
        }
        file << "\n"; // next row
    }

    // Close the file
    file.close();

    std::cout << "CSV file created: " << filename << std::endl;
}

void convertToMat(const std::string& csvFilename, const std::string& matFilename) {

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

    // std::cout << "MAT file created: " << matFilename << std::endl;
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
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Plot BP");

        PlotVector("BP [mBar]", m_BPData_mBar);
        PlotVector("Temperature [°C]", m_TempData_Celsius);

        if (ImGui::Button("Export Data to .csv and .mat")) {
            writeCSV("measurements.csv", measurementsVec);
            convertToMat("measurements.csv", "measurements.mat");
        }

        ImGui::End();//end window

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
    ImGui::DestroyContext();
    glfwTerminate();
}


DisplayManager::~DisplayManager()
{
    if(displayWindowThread && displayWindowThread->joinable()) {
        displayWindowThread->join();
    }
}