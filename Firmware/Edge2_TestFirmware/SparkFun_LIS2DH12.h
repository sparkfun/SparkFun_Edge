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
#ifndef SparkFun_LIS2DH12_H
#define SparkFun_LIS2DH12_H

#include <Arduino.h>
#include <Wire.h>

#include "lis2dh12_reg.h" //This is the ST library

#define ACCEL_DEFAULT_ADR 0x19

class SPARKFUN_LIS2DH12
{
  public:
    bool begin(uint8_t address = ACCEL_DEFAULT_ADR, TwoWire &wirePort = Wire); //Begin comm with accel at given I2C address, and given wire port
    bool isConnected(); //Returns true if an accel sensor is detected at library's I2C address
    bool available(); //Returns true if new accel data is available
    bool temperatureAvailable(); //Returns true if new temp data is available

    float getX(); //Return latest accel data. If data has already be read, initiate new read.
    float getY();
    float getZ();
    float getTemperature(); //Returns latest temp data in C. If data is old, initiate new read.

    void getAccelData(); //Load sensor data into global vars. Call after new data is avaiable.
    void getTempData();

    lis2dh12_ctx_t dev_ctx;

    static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
    static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

  private:
    uint8_t _i2cAddress;
    TwoWire *_i2cPort;

    bool xIsFresh = false;
    bool yIsFresh = false;
    bool zIsFresh = false;
    bool tempIsFresh = false;

    float accelX;
    float accelY;
    float accelZ;
    float temperatureC;

};

#endif /* SparkFun_LIS2DH12_H */
