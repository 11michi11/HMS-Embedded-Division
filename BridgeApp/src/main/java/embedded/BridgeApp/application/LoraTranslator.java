package embedded.BridgeApp.application;

import java.nio.ByteBuffer;
import java.util.LinkedList;
import java.util.List;

public class LoraTranslator {
    public static List<Element> translateDataFromDevice(String data) {
        List<Element> dataList = new LinkedList<>();
        byte[] dataArray = hexStringToByteArray(data);

        return null;
    }

    public static byte[] translateOperationCodeToData(OperationCode code){
        return null;
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

    private static List<Element> loadData(byte[] dataArray) {

    }

    private static double loadSensorData(byte[] sensorData) {
        return ByteBuffer.wrap(sensorData).getDouble();
    }


}
