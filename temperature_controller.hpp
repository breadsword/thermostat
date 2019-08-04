#ifndef TEMPERATURE_CONTROLLER_HPP_INCLUDED
#define TEMPERATURE_CONTROLLER_HPP_INCLUDED

class TemperatureController{
public:
    void setTargetTemperature(const double _target)
    {
        target_temperature = _target;
    }

    double getTargetTemperature() const
    {
        return target_temperature;
    }


    void setHysteresis(const double _hysteresis)
    {
        hysteresis = _hysteresis;
    }

    enum output_t {OFF, ON};
    output_t getOutput(const double Tsens);

private:
    double target_temperature = 25.0;
    double hysteresis = 0.0;
    bool outputIsOn = false;
};

#endif //TEMPERATURE_CONTROLLER_HPP_INCLUDED
