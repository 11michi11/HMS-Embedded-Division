package embedded.BridgeApp.application.data;

import embedded.BridgeApp.application.Visitor;
import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import java.time.LocalDateTime;

public class TemperatureData extends Data{


    protected TemperatureData(LocalDateTime timeStamp, double data, String deviceId) {
        super(timeStamp, data, deviceId);
    }

    @Override
    public void acceptVisitor(Visitor visitor) {
        throw new NotImplementedException();
    }
}
