package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.data.LightData;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface LightRepository extends MongoRepository<LightData, String> {
}
