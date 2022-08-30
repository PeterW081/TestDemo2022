package function.gpio;

public interface GPIO_Define
{
	public enum Pin
	{
		PIN04(4);
		public int v;
		Pin(int value)
		{
			this.v = value;
		}
	}

	public static enum PinMode
	{
		PI_OUTPUT(1);
		public int v;
		PinMode(int value)
		{
			this.v = value;
		}
	}
}
