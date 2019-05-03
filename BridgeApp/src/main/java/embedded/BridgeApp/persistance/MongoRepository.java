package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.Element;
import embedded.BridgeApp.application.Visitor;
import embedded.BridgeApp.application.data.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class MongoRepository implements Visitor {

    private TemperatureRepository temperatureRepository;
    private CarbonDioxideRepository carbonDioxideRepository;
    private HumidityRepository humidityRepository;
    private MovementRepository movementrepository;
    private SoundRepository soundRepository;
    private LightRepository lightRepository;


    @Autowired
    public MongoRepository(TemperatureRepository temperatureRepository, CarbonDioxideRepository carbonDioxideRepository, HumidityRepository humidityRepository, MovementRepository movementrepository, SoundRepository soundRepository, LightRepository lightRepository) {
        this.temperatureRepository = temperatureRepository;
        this.carbonDioxideRepository = carbonDioxideRepository;
        this.humidityRepository = humidityRepository;
        this.movementrepository = movementrepository;
        this.soundRepository = soundRepository;
        this.lightRepository = lightRepository;
    }

    public void save(List<Element> elements) {
        System.out.println("Saving");
        elements.forEach(element -> element.acceptVisitor(this));
    }

    @Override
    public void saveCarbonDioxide(CarbonDioxideData data) {
        carbonDioxideRepository.save(data);
        System.out.println("Saving carbon");
    }

    @Override
    public void saveTemperature(TemperatureData data) {
        temperatureRepository.save(data);
        System.out.println("Saving temperature");
    }

    @Override
    public void saveHumidity(HumidityData data) {
        humidityRepository.save(data);
        System.out.println("Saving humidity");
    }

    @Override
    public void saveMovement(MovementData data) {
        movementrepository.save(data);
        System.out.println("Saving movement");
    }

    @Override
    public void saveSound(SoundData data) {
        soundRepository.save(data);
        System.out.println("Saving sound");
    }

    @Override
    public void saveLight(LightData data) {
        lightRepository.save(data);
        System.out.println("Saving carbon");
    }
}
