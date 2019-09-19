/*
  This is a library written for the SparkFun LIS2DH12
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/15083

  Written by Nathan Seidle @ SparkFun Electronics, November 25th, 2018

  The LIS2DH12 is a very low power I2C triple axis accelerometer

  https://github.com/sparkfun/SparkFun_LIS2DH12_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.9

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SparkFun_LIS2DH12.h"
#include "Arduino.h"


//Begin comm with accel at given I2C address, and given wire port
//Init accel with default settings
bool SPARKFUN_LIS2DH12::begin(uint8_t i2cAddress, TwoWire &wirePort)
{
  _i2cPort = &wirePort;
  _i2cAddress = i2cAddress; //Capture user's setting

  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;

  if (isConnected() == false) return false;

  //Enable Block Data Update
  lis2dh12_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

  //Enable temperature sensor
  lis2dh12_temperature_meas_set(&dev_ctx, LIS2DH12_TEMP_ENABLE);

  //Set Output Data Rate to 25Hz
  lis2dh12_data_rate_set(&dev_ctx, LIS2DH12_ODR_25Hz);

  //Set full scale to 2g
  lis2dh12_full_scale_set(&dev_ctx, LIS2DH12_2g);

  //Enable temperature sensor
  lis2dh12_temperature_meas_set(&dev_ctx, LIS2DH12_TEMP_ENABLE);

  //Set device in continuous mode with 12 bit resol.
  lis2dh12_operating_mode_set(&dev_ctx, LIS2DH12_HR_12bit);

  return true;
}

//Check to see if IC ack its I2C address. Then check for valid LIS2DH ID.
bool SPARKFUN_LIS2DH12::isConnected()
{
  Wire1.beginTransmission((uint8_t)_i2cAddress);
  if (Wire1.endTransmission() == 0)
  {
    //Something ack'd at this address. Check ID.
    static uint8_t whoamI;
    lis2dh12_device_id_get(&dev_ctx, &whoamI);
    if (whoamI == LIS2DH12_ID)
    {
      return (true);
    }
  }
  return (false);
}

//Returns true if new data is available
bool SPARKFUN_LIS2DH12::available()
{
  lis2dh12_reg_t reg;
  lis2dh12_xl_data_ready_get(&dev_ctx, &reg.byte);
  if (reg.byte)
    return true;
  return false;
}

//Returns true if new temperature data is available
bool SPARKFUN_LIS2DH12::temperatureAvailable()
{
  lis2dh12_reg_t reg;
  lis2dh12_temp_data_ready_get(&dev_ctx, &reg.byte);
  if (reg.byte)
    return true;
  return false;

}

//Returns X accel of the global accel data
float SPARKFUN_LIS2DH12::getX()
{
  if (xIsFresh == false)
  {
    getAccelData();
  }
  xIsFresh = false;
  return (accelX);
}

//Returns Y accel of the global accel data
float SPARKFUN_LIS2DH12::getY()
{
  if (yIsFresh == false)
  {
    getAccelData();
  }
  yIsFresh = false;
  return (accelY);
}

//Returns Z accel of the global accel data
float SPARKFUN_LIS2DH12::getZ()
{
  if (zIsFresh == false)
  {
    getAccelData();
  }
  zIsFresh = false;
  return (accelZ);
}

//Returns sensor temperature in C
float SPARKFUN_LIS2DH12::getTemperature()
{
  if (tempIsFresh == false)
  {
    getTempData();
  }
  tempIsFresh = false;
  return (temperatureC);
}

//Load global vars with latest accel data
//Does not guarantee data is fresh (ie you can read the same accel values multiple times)
void SPARKFUN_LIS2DH12::getAccelData()
{
  // Read accelerometer data
  axis3bit16_t data_raw_acceleration;
  memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
  lis2dh12_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);

  accelX = lis2dh12_from_fs2_hr_to_mg(data_raw_acceleration.i16bit[0]);
  accelY = lis2dh12_from_fs2_hr_to_mg(data_raw_acceleration.i16bit[1]);
  accelZ = lis2dh12_from_fs2_hr_to_mg(data_raw_acceleration.i16bit[2]);

  xIsFresh = true;
  yIsFresh = true;
  zIsFresh = true;
}

//Load global vars with latest temp data
//Does not guarantee data is fresh (ie you can read the same temp value multiple times)
void SPARKFUN_LIS2DH12::getTempData()
{
  //Read temperature data
  axis1bit16_t data_raw_temperature;
  memset(data_raw_temperature.u8bit, 0x00, sizeof(int16_t));
  lis2dh12_temperature_raw_get(&dev_ctx, data_raw_temperature.u8bit);
  temperatureC = lis2dh12_from_lsb_hr_to_celsius(data_raw_temperature.i16bit);

  tempIsFresh = true;
}

/*
   @brief  Write generic device register (platform dependent)

   @param  handle    customizable argument. In this examples is used in
                     order to select the correct sensor bus handler.
   @param  reg       register to write
   @param  bufp      pointer to data to write in register reg
   @param  len       number of consecutive register to write

*/
int32_t SPARKFUN_LIS2DH12::platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  if (len > 30)
  {
    return 1; //Error
  }

  Wire1.beginTransmission(ACCEL_DEFAULT_ADR);
  Wire1.write(reg);
  for (uint16_t x = 0 ; x < len ; x++)
  {
    Wire1.write(bufp[x]);
  }

  byte endT = Wire1.endTransmission();
  return (endT); //Will return 0 upon success
}

/*
   @brief  Read generic device register (platform dependent)

   @param  handle    customizable argument. In this examples is used in
                     order to select the correct sensor bus handler.
   @param  reg       register to read
   @param  bufp      pointer to buffer that store the data read
   @param  len       number of consecutive register to read

*/
int32_t SPARKFUN_LIS2DH12::platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  if (len > 1)
  {
    //For multi byte reads we must set the first bit to 1
    reg |= 0x80;
  }

  Wire1.beginTransmission(ACCEL_DEFAULT_ADR);
  Wire1.write(reg);
  Wire1.endTransmission(false); //Don't release bus. Will return 0 upon success.

  //  Wire1.requestFrom(_i2cAddress, len);
  Wire1.requestFrom(ACCEL_DEFAULT_ADR, len);
  for (uint16_t x = 0; x < len; x++)
  {
    bufp[x] = Wire1.read();
  }

  return (0); //Success
}
