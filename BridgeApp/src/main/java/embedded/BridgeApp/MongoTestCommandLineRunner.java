package embedded.BridgeApp;

import embedded.BridgeApp.persistance.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

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

    }

}
