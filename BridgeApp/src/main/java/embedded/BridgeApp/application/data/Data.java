package embedded.BridgeApp.application.data;

import embedded.BridgeApp.application.Element;

import java.time.LocalDateTime;

public abstract class Data implements Element {

    private LocalDateTime timeStamp;
    private double data;
    private String deviceId;

    protected Data(LocalDateTime timeStamp, double data, String deviceId) {
        this.timeStamp = timeStamp;
        this.data = data;
        this.deviceId = deviceId;
    }
}
