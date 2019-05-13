package embedded.BridgeApp.application.websocket;

import com.google.gson.Gson;
import embedded.BridgeApp.application.Element;
import embedded.BridgeApp.application.data.*;

import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.GregorianCalendar;
import java.util.List;

public class LoraTranslator {

    public static List<Element> translateDataFromDevice(String data, String eui, long timestamp) {
        byte[] dataArray = hexStringToByteArray(data);
        Instant instant = Instant.ofEpochSecond(timestamp);
        LocalDateTime currentTime = LocalDateTime.ofInstant(instant, ZoneId.of("Europe/Copenhagen"));
        return loadData(dataArray, eui, currentTime);
    }

    public static String translateOperationCodeToData(OperationCode code, String deviceID) {
        String data = String.format("%02x", code.getCode());
        LoraDownlinkMessage downlinkMessage = new LoraDownlinkMessage(deviceID, data);
        Gson gson = new Gson();
        return gson.toJson(downlinkMessage);
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

    private static List<Element> loadData(byte[] dataArray, String deviceId, LocalDateTime currentTime) {
        return List.of(
                new CarbonDioxideData(currentTime, ((dataArray[1] & 0xff) << 8) | (dataArray[0] & 0xff), deviceId),
                new TemperatureData(currentTime, dataArray[2], deviceId),
                new HumidityData(currentTime, dataArray[3], deviceId),
                new LightData(currentTime, dataArray[4], deviceId),
                new MovementData(currentTime, dataArray[5], deviceId));
    }
}
