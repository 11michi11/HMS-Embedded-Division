package embedded.BridgeApp;

import embedded.BridgeApp.application.Element;
import embedded.BridgeApp.application.data.MovementData;
import embedded.BridgeApp.persistance.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.time.LocalDateTime;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

@Component
public class MongoTestCommandLineRunner implements CommandLineRunner {

    @Autowired
    private TemperatureRepository temperatureRepository;
    @Autowired
    private CarbonDioxideRepository carbonDioxideRepository;
    @Autowired
    private SoundRepository soundRepository;
    @Autowired
    private HumidityRepository humidityRepository;
    @Autowired
    private MovementRepository movementRepository;
    @Autowired
    private LightRepository lightRepository;
    @Autowired
    private MongoRepository mongoRepository;


    static Random rn = new Random();

    @Override
    public void run(String... args) throws Exception {

//        LocalDateTime now = LocalDateTime.now().withNano(0);
//        String id = "testDevice";
//        TemperatureData dataT = new TemperatureData(now, 15.0, id);
//        CarbonDioxideData dataC = new CarbonDioxideData(now, 200.0, id);
//        HumidityData dataH = new HumidityData(now, 15.0, id);
//        SoundData dataS = new SoundData(now, 15.0, id);
//        LightData dataL = new LightData(now, 15.0, id);
//        MovementData dataM = new MovementData(now, 15.0, id);

//		movementRepository.save(dataM);
//		lightRepository.save(dataL);
//		soundRepository.save(dataS);
//		humidityRepository.save(dataH);
//		temperatureRepository.save(dataT);
//		carbonDioxideRepository.save(dataC);

//        movementRepository.delete(dataM);
//        lightRepository.delete(dataL);
//        soundRepository.delete(dataS);
//        humidityRepository.delete(dataH);
//        carbonDioxideRepository.delete(dataC);
//        temperatureRepository.delete(dataT);

//       generateDummyMovementData(50).stream().map(element -> (MovementData) element).forEach(element -> {
//           System.out.println(element);
//           movementRepository.save(element);
//       });

    }


    List<Element> generateDummyMovementData(int amount) {
        var elements = new LinkedList<Element>();

        LocalDateTime time = LocalDateTime.now();
        var value = 150.0;
        var id = "TestDevice";

        for (int i = 0; i < amount; i++) {
            elements.add(new MovementData(time, value, id));
            value = generateNewValue(value);
            time = time.plusMinutes(5);
        }
        return elements;
    }

    static double generateNewValue(double value) {
        int x = rn.nextInt(5);
        if (rn.nextBoolean() && (value - x) > 0)
            return value - x;
        return value + x;
    }


}
