package embedded.BridgeApp.application.data;

import embedded.BridgeApp.application.Element;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import java.time.LocalDateTime;

@Document
public abstract class Data implements Element {

    @Id
    private String deviceId;
    private LocalDateTime timeStamp;
    private double data;

    protected Data(LocalDateTime timeStamp, double data, String deviceId) {
        this.timeStamp = timeStamp;
        this.data = data;
        this.deviceId = deviceId;
    }
}
