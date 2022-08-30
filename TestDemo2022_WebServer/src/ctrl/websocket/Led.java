package ctrl.websocket;

import java.io.IOException;

import javax.websocket.OnClose;
import javax.websocket.OnOpen;
import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;

@ServerEndpoint("/led04/ws_read")
public class Led
{
	private Led_Reader reader;

	@OnOpen
	public void onOpen(Session session) throws IOException
	{
		this.reader = new Led_Reader(session);
		reader.start();
	}

	@OnClose
	public void onClose(Session session) throws IOException
	{
		reader.interrupt_safe();
	}
}

class Led_Reader extends Thread
{
	private final Session session;
	private boolean isSafeInterrupt = false;

	public Led_Reader(Session session)
	{
		this.session = session;
	}

	public void interrupt_safe()
	{
		this.isSafeInterrupt = true;
		this.interrupt();
	}

	public void run()
	{
		try
		{
			while (true)
			{
				session.getAsyncRemote().sendText(ctrl.restful.Led.instance.read());
				Thread.sleep(1 * 1000);
			}
		} catch (InterruptedException | IOException e)
		{
			boolean isOk = true;
			isOk &= isSafeInterrupt;
			isOk &= e instanceof InterruptedException;
			if (!isOk)
			{
				e.printStackTrace();
			}
		}
	};
}