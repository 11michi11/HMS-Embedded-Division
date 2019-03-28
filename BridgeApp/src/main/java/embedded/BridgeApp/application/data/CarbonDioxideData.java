package embedded.BridgeApp.application.data;

import embedded.BridgeApp.application.Visitor;
import org.springframework.data.mongodb.core.mapping.Document;

import java.time.LocalDateTime;

@Document(collection = "carbon")
public class CarbonDioxideData extends Data {

    public CarbonDioxideData(LocalDateTime timeStamp, double data, String deviceId) {
        super(timeStamp, data, deviceId);
    }

    @Override
    public void acceptVisitor(Visitor visitor) {
        visitor.saveCarbonDioxide(this);
    }
}
