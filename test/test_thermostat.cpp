#include <QtTest>

#include <iostream>

#include <thermostat.hpp>

class test_thermostat : public QObject
{
    Q_OBJECT
public:
    test_thermostat(){}
    ~test_thermostat(){}

private slots:
    void test_set_temperature();
    void test_output_below_set_temperature();
    void test_output_above_set_temperature();
    void test_output_hysteresis();

private:
    Thermostat cont;

};

void test_thermostat::test_set_temperature()
{
    const auto T=27.5;
    cont.setTargetTemperature(T);
    QVERIFY(cont.getTargetTemperature() == T);
}

void test_thermostat::test_output_below_set_temperature()
{
    const auto Tset = 25.0;
    cont.setTargetTemperature(Tset);

    const auto Tin = Tset-0.7;
    const auto controller_output = cont.getOutput(Tin);
    QVERIFY(controller_output == Thermostat::ON);

}

void test_thermostat::test_output_above_set_temperature()
{
    const auto Tset = 25.0;
    cont.setTargetTemperature(Tset);

    const auto Tin = Tset + 1.0;
    const auto controller_output = cont.getOutput(Tin);
    QVERIFY(controller_output == Thermostat::OFF);
}

#include <boost/range/combine.hpp>

void test_thermostat::test_output_hysteresis()
{
    const auto Tset = 25.0;
    const auto hysteresis = 0.5; // temperature has to drop by hysteresis before we switch on again, then has to rise until Tset

    cont.setTargetTemperature(Tset);
    cont.setHysteresis(hysteresis);

    const auto Tin = {25.5, 24.9, 24.0, 24.9, 25.01};
    constexpr auto ON = Thermostat::ON;
    constexpr auto OFF = Thermostat::OFF;
    const auto ExpectOut = {OFF, OFF, ON, ON, OFF};

    for (const auto tup : boost::combine(Tin, ExpectOut))
    {
        double T;
        Thermostat::output_t E;
        boost::tie(T, E) = tup;

        std::cout << "Tin: " << T << std::endl;
        QVERIFY(E == cont.getOutput(T));
    }
}

QTEST_APPLESS_MAIN(test_thermostat)

#include "test_thermostat.moc"
