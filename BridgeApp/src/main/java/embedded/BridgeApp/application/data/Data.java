package embedded.BridgeApp.application.data;

import embedded.BridgeApp.application.Element;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

import java.time.LocalDateTime;
import java.util.Objects;

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

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Data data1 = (Data) o;

        if (Double.compare(data1.data, data) != 0) return false;
        if (!Objects.equals(deviceId, data1.deviceId)) return false;
        return Objects.equals(timeStamp, data1.timeStamp);
    }

    @Override
    public int hashCode() {
        int result;
        long temp;
        result = deviceId != null ? deviceId.hashCode() : 0;
        result = 31 * result + (timeStamp != null ? timeStamp.hashCode() : 0);
        temp = Double.doubleToLongBits(data);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        return result;
    }

    @Override
    public String toString() {
        return "Data{" +
                "deviceId='" + deviceId + '\'' +
                ", timeStamp=" + timeStamp +
                ", data=" + data +
                '}';
    }
}
