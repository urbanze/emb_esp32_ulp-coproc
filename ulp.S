#include "soc/soc_ulp.h"
#include "soc/rtc_io_reg.h"
#include "soc/sens_reg.h"
#include "soc/rtc_cntl_reg.h"


.bss//Declaracao de variaveis aqui


.text

	.global main
	main://Inicio do codigo (Entry point)
		WRITE_RTC_REG(RTC_GPIO_OUT_W1TC_REG, RTC_GPIO_OUT_DATA_W1TC_S+12, 1, 1)//Desliga o atuador (GPIO2 = LOW)



	loop:

		READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S+11, 1)//Le o estado do GPIO0 e guarda no R0
		jumpr on, 1, lt//Se o botao for pressionado (0), ativa o atuador

		WRITE_RTC_REG(RTC_GPIO_OUT_W1TC_REG, RTC_GPIO_OUT_DATA_W1TC_S+12, 1, 1)//Caso o botao nao esteja pressionado, mantem o atuador desligado


	jump loop//retorna ao loop


	on://ativa o atuador e retorna ao loop
		WRITE_RTC_REG(RTC_GPIO_OUT_W1TS_REG, RTC_GPIO_OUT_DATA_W1TS_S+12, 1, 1)//Ativa o atuador (GPIO2 = HIGH)
	jump loop
