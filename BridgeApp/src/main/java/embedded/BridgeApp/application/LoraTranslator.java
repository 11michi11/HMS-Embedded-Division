package embedded.BridgeApp.application;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import embedded.BridgeApp.application.data.*;

import java.lang.reflect.Modifier;
import java.time.LocalDateTime;
import java.util.LinkedList;
import java.util.List;

public class LoraTranslator {

    public static List<Element> translateDataFromDevice(String data, String eui) {
        byte[] dataArray = hexStringToByteArray(data);
        return loadData(dataArray,eui);
    }

    public static String translateOperationCodeToData(OperationCode code, String deviceID){
        String data = String.format("%02x",code.getCode());
        LoraUplinkMessage uplinkMessage = new LoraUplinkMessage(deviceID,data);
        Gson gson = new GsonBuilder().excludeFieldsWithModifiers(Modifier.TRANSIENT).create();
        return gson.toJson(uplinkMessage);
    }

    private static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i+1), 16));
        }
        return data;
    }

    private static List<Element> loadData(byte[] dataArray, String deviceId) {
        List<Element> dataList = new LinkedList<>();
        LocalDateTime currentTime = LocalDateTime.now();
        dataList.add(new CarbonDioxideData(currentTime,dataArray[0]+(dataArray[1]<<8),deviceId));
        dataList.add(new TemperatureData(currentTime,dataArray[2],deviceId));
        dataList.add(new HumidityData(currentTime,dataArray[3],deviceId));
        dataList.add(new SoundData(currentTime,dataArray[4],deviceId));
        dataList.add(new MovementData(currentTime,dataArray[5],deviceId));
        return dataList;
    }
}
