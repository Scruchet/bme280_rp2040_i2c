#include "main.h"

int main()
{
    float temp;
    float press;
    float hum;
    init();
    sleep_ms(1000);
    set_pressure_oversampling(1);
    set_temperature_oversampling(1);
    set_mode(SLEEP_MODE);
    while (true)
    {
        set_mode(FORCED_MODE);// Single capture 
        sleep_ms(10);

        temp = get_temp_celsius();
        press = get_pressure_in_Pa();
        hum = get_humidity_percentage();
        printf("Temperature : %.2f °C\n", temp);
        printf("Pressure : %.2f Pa\n", press);
        printf("Humidity : %.2f %%\n", hum);
        sleep_ms(1000);
    }

    return 0;
}