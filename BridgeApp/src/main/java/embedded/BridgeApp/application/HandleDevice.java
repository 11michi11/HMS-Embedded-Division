package embedded.BridgeApp.application;

import embedded.BridgeApp.persistance.MongoRepository;
import org.springframework.beans.factory.annotation.Autowired;

public class HandleDevice implements Runnable{
    private int deviceId;
    @Autowired
    private MongoRepository mongoRepository;

    public HandleDevice(int deviceId) {
        this.deviceId = deviceId;
    }

    public byte[] receiveTransmision() {
        return null;
    }

    public void sendCommand(byte[] data) {

    }

    @Override
    public void run() {

    }
}
