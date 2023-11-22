#include "DataPoint.h"
#include "../include/definitions.h"

DataPoint::DataPoint(uint32_t m_canID, byte* data, uint8_t dataLength, double timestamp)
{
	// byte* temp_data = new byte[dataLength];
	// for (int i = 0; i < dataLength; i++)
	// {
	// 	temp_data[i] = data[i];
	// }
	// data = std::unique_ptr<byte[]>(temp_data);
	// m_canID = m_canID;
	// dataLength = dataLength;
	// timestamp = timestamp;
}

DataPoint::DataPoint(uint32_t canID, char* data, uint8_t dataLength)
{
	m_canID = canID;
	parseValuesFromDataString(data, dataLength);
}

void DataPoint::parseValuesFromDataString(char* data, uint8_t dataLength)
{
	m_data_lenght = dataLength;
	m_value = ReadBytesFromBuffer(data, 0, valuebuffersize).release();
	m_beacon = ReadBytesFromBuffer(data, valuebuffersize, beaconbuffersize).release();
	m_timestamp = ReadBytesFromBuffer(data, valuebuffersize+beaconbuffersize, timestampbuffersize).release();
	m_counter = ReadBytesFromBuffer(data, valuebuffersize+beaconbuffersize+timestampbuffersize, counterbuffersize).release();

	encodedData.canID = m_canID;
	encodedData.timestamp = static_cast<uint32_t>(ReadByteSignedValuesFromBuffer(m_timestamp, 0, timestampbuffersize));
	encodedData.value = static_cast<uint32_t>(ReadByteSignedValuesFromBuffer(m_value, 0 , valuebuffersize));
	// std::cout << "encoded canID: " << encodedData.canID << std::endl;
	// std::cout << "encoded timestamp: " << encodedData.timestamp << std::endl;
	// std::cout << "encoded value: " << encodedData.value << std::endl;
}