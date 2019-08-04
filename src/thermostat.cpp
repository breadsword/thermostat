#include <thermostat.hpp>

TemperatureController::output_t TemperatureController::getOutput(const double Tsens)
{
    if (outputIsOn)
    {
        if (Tsens > target_temperature)
        {
            outputIsOn = false;
            return OFF;
        }
        else
        {
            outputIsOn = true;
            return ON;
        }
    }
    else
    {
        if (Tsens < target_temperature-hysteresis)
        {
            outputIsOn = true;
            return ON;
        }
        else
        {
            outputIsOn = false;
            return OFF;
        }
    }
}
