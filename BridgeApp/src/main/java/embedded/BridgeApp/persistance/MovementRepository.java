package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.data.MovementData;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface MovementRepository extends MongoRepository<MovementData, String> {
}
