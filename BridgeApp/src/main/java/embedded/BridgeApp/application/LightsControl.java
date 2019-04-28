package embedded.BridgeApp.application;

public interface LightsControl {
    public void turnOnMovementDetection(String deviceID);
    public void turnOffMovementDetection(String deviceID);
}
