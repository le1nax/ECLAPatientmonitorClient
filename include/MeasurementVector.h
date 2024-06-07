#pragma once
#include <vector>
#include <string>
#include "../ParseECLA/Id.h"
#include "../ParseECLA/IdType.h"

class MeasurementVector {
public:
    MeasurementVector(const Id& id);

    void addMeasurement(float measurement);
    const std::vector<float>& getMeasurements() const;
    const std::vector<float>& getCylclicMeasurements() const;
    const Id& getId() const;
    int idPattern;
    std::string name;
    std::string unit;
    double factor;
    int canInterval;
    int sdInterval;
    int canThreshold;
    int sdThreshold;
    uint32_t min;
    uint32_t max;
    std::string description;

private:
    std::vector<float> measurements;
    std::vector<float> cyclicMeasurements;   //u0sed to plot, displays only a certain amount
    Id id;
};
