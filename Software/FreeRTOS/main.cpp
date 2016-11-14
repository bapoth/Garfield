#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "system.h"
#include "FreeRTOS.h"
#include "task.h"

class abc {
	public:
	void habedere(void) { alt_putstr("Habedere C++"); }
};

void sayHello( void *p)
{
	while(1)
	{
		alt_putstr("Hello, world!\n");
		vTaskDelay(1000);
	}
}
void sayInBitween (void *p)
{
	while(1)
	{
		alt_putstr("In between\n");
		vTaskDelay(300);
	}
}
int main()
{
	abc* a = new abc{};
	a->habedere();

 alt_putstr("Hello from Nios II!\n");
 xTaskCreate(sayHello, "sayHello", 512, NULL, 2, NULL);
 xTaskCreate(sayInBitween, "sayInBitween",512,NULL,2,NULL);
 vTaskStartScheduler();
 return 0;
}
