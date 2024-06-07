#include "../include/MeasurementVector.h"
#include "../include/definitions.h"

MeasurementVector::MeasurementVector(const Id& id) : id(id) {
    IdType tmpIdType = *id.getType();
    idPattern = tmpIdType.getIdPattern();
    name = tmpIdType.getNamePattern();
    unit = tmpIdType.getUnit();
    factor = tmpIdType.getFactor();
    canInterval = tmpIdType.getCanInterval();
    sdInterval = tmpIdType.getSdInterval();
    canThreshold = tmpIdType.getCanThreshold();
    sdThreshold = tmpIdType.getSdThreshold();
    min = tmpIdType.getMin();
    idPattern = tmpIdType.getMax();
    description = tmpIdType.getDescription();
}

void MeasurementVector::addMeasurement(float measurement) {
    measurements.push_back(measurement);
    if(cyclicMeasurements.size() < maxNumberOfPressValues){
        cyclicMeasurements.push_back(measurement*factor);
    }
     //else: Reset Cyclic Plot Vector
    cyclicMeasurements.clear();
    cyclicMeasurements.push_back(measurement*factor);
}

const std::vector<float>& MeasurementVector::getMeasurements() const {
    return measurements;
}

const std::vector<float>& MeasurementVector::getCylclicMeasurements() const {
    return cyclicMeasurements;
}

const Id& MeasurementVector::getId() const {
    return id;
}