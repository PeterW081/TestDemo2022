package function.gpio;

import ctrl.main.Main;

public abstract class GPIO_Core implements GPIO_Define
{
	private static class Jni
	{
		private static String libPath = Main.pathLibJniGpio;
		static
		{
			System.load(libPath);
			env_init();
		}
		private static native void   env_init();
		private static native void   pin_init(int pin_number, int pin_mode);
		private static native int    pin_read(int pin_number);
		private static native void   pin_write(int pin_number, int value);		
	}
	protected static void pin_init(Pin pin_number, PinMode pin_mode)
	{
		Jni.pin_init(pin_number.v, pin_mode.v);
	}
	protected static int pin_read(Pin pin_number)
	{
		return Jni.pin_read(pin_number.v);
	}
	protected static void pin_write(Pin pin_number, int value)
	{
		Jni.pin_write(pin_number.v, value);
	}
}



