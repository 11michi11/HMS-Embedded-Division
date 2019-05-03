package embedded.BridgeApp;

import embedded.BridgeApp.application.LoraService;
import embedded.BridgeApp.persistance.MongoRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class BridgeAppApplication implements CommandLineRunner {

    @Autowired
    LoraService lora;
    @Autowired
    MongoRepository mongoRepository;


    public static void main(String[] args) {
        SpringApplication.run(BridgeAppApplication.class, args);
    }


    @Override
    public void run(String... args) throws Exception {
        lora.start();
    }
}
