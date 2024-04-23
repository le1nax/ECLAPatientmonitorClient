#pragma once
#include <Windows.h>
#include "../include/definitions.h"
#include <cstdint>
#include <memory>
#include <fstream>
#include <vector>


/// @brief DataStruct holding the information that is sent via udp
/// @todo include beacon timestamp
struct DataPointEncoded
{
	/// @brief the canID that is read by the PCAN USB Adapter
	uint32_t canID;
	/// @brief the timestamp that is defined in the CAN Sensormodule (Beacontimestamp)
	uint32_t timestamp;
	/// @brief the timestamp that is defined from the pcanModule (time after start of operating system)
	uint64_t pcanTimestamp; //milliseconds after pcanConnect;
	/// @brief the payload from the CAN sensormodule
	int32_t value;	
};

/// @brief the size of the encoded Data Struct (effectivly the buffersize of the udp messages)
static constexpr size_t size_encoded = sizeof(DataPointEncoded);

/// @brief The Class, that handles the measurement information at a specific timestamp
class DataPoint
{
public:
	/// @brief Constructor
	/// @param canID canID read by PCAN USB Adapter
	/// @param data payload
	/// @param milliseconds milliseconds after start of operating system
	/// @param dataLength length of Can Message
	DataPoint(uint32_t canID, char* data, uint64_t milliseconds, uint8_t dataLength);

	/// @brief default copy constructor
	/// @param other Other DataPoint
	DataPoint(const DataPoint& other) = default;
	/// @brief canID read by PCAN USB Adapter
	uint32_t m_canID;
	/// @brief payload
	char* m_value;
	/// @brief beacon bits from CAN sensormodule
	char* m_beacon;
	/// @brief beacon timestamp from CAN sensormodule
	char* m_timestamp;
	/// @brief count of message (Debug value)
	char* m_counter;
	/// @brief length of Can Message
	uint8_t m_data_lenght;
	/// @brief milliseconds after start of operating system
	uint64_t m_pcanTimestamp;
	DataPointType m_datatype = DataPointType::DEBUG;
	/// @brief encoded Data struct (effectivly the buffer that is sent via UDP)
	DataPointEncoded encodedData{};
	

private:
	// uint32_t m_canID;                                  
	// char* m_data;

	// uint8_t dataLength;
	// double timestamp;
	///@brief parses values from given data char* buffer
	void parseValuesFromDataString(char* data, uint64_t milliseconds, uint8_t dataLength);

    

};