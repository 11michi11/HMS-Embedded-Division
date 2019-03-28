package embedded.BridgeApp.application;

import embedded.BridgeApp.application.data.*;

public interface Visitor {

    public void saveCarbonDioxide(CarbonDioxideData data);
    public void saveTemperature(TemperatureData data);
    public void saveHumidity(HumidityData data);
    public void saveMovement(MovementData data);
    public void saveSound(SoundData data);
    public void saveLight(LightData data);

}
