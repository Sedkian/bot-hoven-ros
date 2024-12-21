#ifndef HARDWARE__PCA9685__PCA9685_H
#define HARDWARE__PCA9685__PCA9685_H

#include <string>
#include <memory>

#include "hardware/common/Constants.h"
#include "hardware/i2c/I2CPeripheral.h"

namespace pca9685_hardware_interface {

class PCA9685 {
public:
    PCA9685(std::shared_ptr<hardware::I2CPeripheral> i2c_device, int address);
    ~PCA9685();

    void init();
    void disconnect();

    void set_pwm_freq(const double freq_hz);

    void set_pwm(const int channel, const uint16_t on, const uint16_t off);

    void set_all_pwm(const uint16_t on, const uint16_t off);

    void set_pwm_ms(const int channel, const double ms);

private:
    std::shared_ptr<I2CPeripheral> i2c_dev;

    std::string device = "/dev/i2c-1";
    int address = 0x40;
    

};

}  // namespace pca9685_hardware_interface

#endif //HARDWARE__PCA9685__PCA9685_H
