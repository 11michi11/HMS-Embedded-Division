package embedded.BridgeApp.application;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import embedded.BridgeApp.application.data.*;

import java.lang.reflect.Modifier;
import java.time.LocalDateTime;
import java.util.List;

public class LoraTranslator {

    public static List<Element> translateDataFromDevice(String data, String eui) {
        byte[] dataArray = hexStringToByteArray(data);
        return loadData(dataArray, eui);
    }

    public static String translateOperationCodeToData(OperationCode code, String deviceID) {
        String data = String.format("%02x", code.getCode());
        LoraUplinkMessage uplinkMessage = new LoraUplinkMessage(deviceID, data);
        Gson gson = new GsonBuilder().excludeFieldsWithModifiers(Modifier.TRANSIENT).excludeFieldsWithoutExposeAnnotation().create();
        return gson.toJson(uplinkMessage);
    }

    private static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i + 1), 16));
        }
        return data;
    }

    private static List<Element> loadData(byte[] dataArray, String deviceId) {
        LocalDateTime currentTime = LocalDateTime.now();
        return List.of(
                new CarbonDioxideData(currentTime, dataArray[0] + (dataArray[1] << 8), deviceId),
                new TemperatureData(currentTime, dataArray[2], deviceId),
                new HumidityData(currentTime, dataArray[3], deviceId),
                new MovementData(currentTime, dataArray[4], deviceId));
    }
}
