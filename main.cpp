extern "C"
{
#include <driver/gpio.h>
#include <driver/rtc_io.h>
#include <ulp/ulp.c>
#include <ulp_main.h>
}

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");//Inicio do binario
extern const uint8_t ulp_main_bin_end[] asm("_binary_ulp_main_bin_end");//Fim do binario


void initULP()
{
	//Configura o GPIO0 como entrada no RTC Domain (ULP reside no RTC Domain)
	rtc_gpio_init(GPIO_NUM_0);
	rtc_gpio_set_direction(GPIO_NUM_0, RTC_GPIO_MODE_INPUT_ONLY);


	//Configura o GPIO2 como saida no RTC Domain (ULP reside no RTC Domain)
	rtc_gpio_init(GPIO_NUM_2);
	rtc_gpio_set_direction(GPIO_NUM_2, RTC_GPIO_MODE_OUTPUT_ONLY);



	ulp_load_binary(0, ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));//Carrega o binario na RTC_SLOW_MEM
	ulp_run((&ulp_main - RTC_SLOW_MEM) / sizeof(uint32_t));//Inicializa o ULP
}


extern "C" void app_main()
{
	initULP();//Funcao que inicializa o ULP

	//Configura o GPIO13 como saida
	gpio_pad_select_gpio(13);
	gpio_set_direction(GPIO_NUM_13, GPIO_MODE_OUTPUT);


	while (1)//PWM 4 MHz
	{
		REG_WRITE(GPIO_OUT_W1TS_REG, BIT13);//GPIO13 = HIGH
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		REG_WRITE(GPIO_OUT_W1TC_REG, BIT13);//GPIO13 = LOW
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
		asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
	}

}
