package embedded.BridgeApp.persistance;

import org.springframework.data.mongodb.repository.MongoRepository;

public interface TemperatureRepository extends MongoRepository<TemperatureData, String> {
}
