package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.data.SoundData;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface SoundRepository extends MongoRepository<SoundData, String> {
}
