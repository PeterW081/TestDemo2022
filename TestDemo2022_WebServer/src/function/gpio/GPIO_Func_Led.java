package function.gpio;

public class GPIO_Func_Led extends GPIO_Core
{
	public static int led_on = 1;
	public static int led_off = 0;	
	public static void enable(Pin pin_number)
	{
		pin_init(pin_number, PinMode.PI_OUTPUT);
	}
	public static int status(Pin pin_number)
	{
		return pin_read(pin_number);
	}
	public static void set_on(Pin pin_number)
	{
		pin_write(pin_number, led_on);
	}
	public static void set_off(Pin pin_number)
	{
		pin_write(pin_number, led_off);
	}
}
