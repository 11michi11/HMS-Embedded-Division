package embedded.BridgeApp.application.data;

import embedded.BridgeApp.application.Visitor;
import org.springframework.data.mongodb.core.mapping.Document;

import java.time.LocalDateTime;

@Document(collection = "sound")
public class SoundData extends Data {

    public SoundData(LocalDateTime timeStamp, double data, String deviceId) {
        super(timeStamp, data, deviceId);
    }

    @Override
    public void acceptVisitor(Visitor visitor) {
        visitor.saveSound(this);
    }
}
