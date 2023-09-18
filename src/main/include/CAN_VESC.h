// #include <frc/CAN.h>
#include <iostream>

#include <frc/Errors.h>
#include <hal/CANAPITypes.h>
#include <hal/CAN.h>

#include <hal/CANAPI.h>
#include <hal/Errors.h>
#include <hal/FRCUsageReporting.h>

#include <frc/CAN.h>

// baud 500k
// 250KBPS, MCP_8MHZ

// got this from bldc firmware
typedef enum {
  CAN_PACKET_SET_DUTY = 0,
  CAN_PACKET_SET_CURRENT = 1,
  CAN_PACKET_SET_CURRENT_BRAKE = 2,
  CAN_PACKET_SET_RPM = 3,
  CAN_PACKET_SET_POS = 4,
  CAN_PACKET_FILL_RX_BUFFER = 5,
  CAN_PACKET_FILL_RX_BUFFER_LONG = 6,
  CAN_PACKET_PROCESS_RX_BUFFER = 7,
  CAN_PACKET_PROCESS_SHORT_BUFFER = 8,
  CAN_PACKET_STATUS = 9,
  CAN_PACKET_SET_CURRENT_REL = 10,
  CAN_PACKET_SET_CURRENT_BRAKE_REL = 11,
  CAN_PACKET_SET_CURRENT_HANDBRAKE = 12,
  CAN_PACKET_SET_CURRENT_HANDBRAKE_REL = 13,
  CAN_PACKET_STATUS_2 = 14,
  CAN_PACKET_STATUS_3 = 15,
  CAN_PACKET_STATUS_4 = 16,
  CAN_PACKET_PING = 17,
  CAN_PACKET_PONG = 18,
  CAN_PACKET_DETECT_APPLY_ALL_FOC = 19,
  CAN_PACKET_DETECT_APPLY_ALL_FOC_RES = 20,
  CAN_PACKET_CONF_CURRENT_LIMITS = 21,
  CAN_PACKET_CONF_STORE_CURRENT_LIMITS = 22,
  CAN_PACKET_CONF_CURRENT_LIMITS_IN = 23,
  CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN = 24,
  CAN_PACKET_CONF_FOC_ERPMS = 25,
  CAN_PACKET_CONF_STORE_FOC_ERPMS = 26,
  CAN_PACKET_STATUS_5 = 27,
  CAN_PACKET_POLL_TS5700N8501_STATUS = 28,
  CAN_PACKET_CONF_BATTERY_CUT = 29,
  CAN_PACKET_CONF_STORE_BATTERY_CUT = 30,
  CAN_PACKET_SHUTDOWN = 31,
  CAN_PACKET_IO_BOARD_ADC_1_TO_4 = 32,
  CAN_PACKET_IO_BOARD_ADC_5_TO_8 = 33,
  CAN_PACKET_IO_BOARD_ADC_9_TO_12 = 34,
  CAN_PACKET_IO_BOARD_DIGITAL_IN = 35,
  CAN_PACKET_IO_BOARD_SET_OUTPUT_DIGITAL = 36,
  CAN_PACKET_IO_BOARD_SET_OUTPUT_PWM = 37,
  CAN_PACKET_BMS_V_TOT = 38,
  CAN_PACKET_BMS_I = 39,
  CAN_PACKET_BMS_AH_WH = 40,
  CAN_PACKET_BMS_V_CELL = 41,
  CAN_PACKET_BMS_BAL = 42,
  CAN_PACKET_BMS_TEMPS = 43,
  CAN_PACKET_BMS_HUM = 44,
  CAN_PACKET_BMS_SOC_SOH_TEMP_STAT = 45,
  CAN_PACKET_PSW_STAT = 46,
  CAN_PACKET_PSW_SWITCH = 47,
  CAN_PACKET_BMS_HW_DATA_1 = 48,
  CAN_PACKET_BMS_HW_DATA_2 = 49,
  CAN_PACKET_BMS_HW_DATA_3 = 50,
  CAN_PACKET_BMS_HW_DATA_4 = 51,
  CAN_PACKET_BMS_HW_DATA_5 = 52,
  CAN_PACKET_BMS_AH_WH_CHG_TOTAL = 53,
  CAN_PACKET_BMS_AH_WH_DIS_TOTAL = 54,
  CAN_PACKET_UPDATE_PID_POS_OFFSET = 55,
  CAN_PACKET_POLL_ROTOR_POS = 56,
  CAN_PACKET_NOTIFY_BOOT = 57,
  CAN_PACKET_STATUS_6 = 58,
  CAN_PACKET_GNSS_TIME = 59,
  CAN_PACKET_GNSS_LAT = 60,
  CAN_PACKET_GNSS_LON = 61,
  CAN_PACKET_GNSS_ALT_SPEED_HDOP = 62,
  CAN_PACKET_MAKE_ENUM_32_BITS = 0xFFFFFFFF,
} CAN_PACKET_ID;

// got this from an arduino using mcp2515
enum VESC_COMMAND_ID {
  kDutyCycle = 0x0000000A,
  kCurrent = 0x0000010A,
  kERPM = 0x0000030A
};

class CAN_VESC {
 public:
  CAN_VESC(int canID) : _canID(canID), _can(canID) {
  }

  void vesc_set_duty_b(float duty) {
    // assume duty of 1.0
    uint32_t set_value = duty * 100000;   // if 1 * 100000 = 100000
    uint8_t buffer[4];                    // message buffer
    buffer[0] = (set_value >> 24) & 0xFF; // 00000000
    buffer[1] = (set_value >> 16) & 0xFF; // 00000001
    buffer[2] = (set_value >> 8) & 0xFF;  //  10000110
    buffer[3] = set_value & 0xFF;         //         10100000

    // print the binary form
    // for (int i = 0; i < 4; i++) {
    //   std::cout << "Pos(" << i << "): ";
    //   for (int bit = 7; bit >= 0; --bit) {
    //     std::cout << ((buffer[i] >> bit) & 1);
    //   }
    //   std::cout << std::endl;
    // }

    // _can.WritePacket(buffer, 4, CAN_PACKET_ID::CAN_PACKET_SET_DUTY);
    int32_t status = 0;
    std::cout << "HAL Status: " << status << std::endl;
  }

  // quick and dirty
  int get_position() {
    // _can.WritePacket(nullptr, 0, CAN_PACKET_ID::CAN_PACKET_POLL_ROTOR_POS); // request
    // frc::CANData buffer;
    uint8_t buffer[8];
    int32_t length;
    int32_t status_w = 0;
    int32_t status_r = 0;
    uint64_t timestamp;
    
    // HAL_WriteCANPacket(_handle, nullptr, 4, CAN_PACKET_POLL_ROTOR_POS, &status_w);
    // _can.WritePacket(nullptr, )
    // auto can = _handl

    // std::cout << "Status Write: " << status_w << std::endl;
    // HAL_ReadCANPacketLatest(_handle, CAN_PACKET_POLL_ROTOR_POS, buffer, &length, &timestamp, &status_r);
    // std::cout << "Status Read: " << status_r << std::endl;


    return buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3];
  }

private:
  frc::CAN _can;
  const int _canID;

  float _inputVoltage, _dutyCycleNow, _avgInputCurrent, _avgMotorCurrent, _tempFET, _tempMotor;
  long _erpm;
};