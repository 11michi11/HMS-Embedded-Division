package embedded.BridgeApp;

import embedded.BridgeApp.application.LoraService;
import embedded.BridgeApp.application.data.*;
import embedded.BridgeApp.persistance.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.time.LocalDateTime;

@SpringBootApplication
public class BridgeAppApplication implements CommandLineRunner {

    @Autowired
    LoraService lora;


    public static void main(String[] args) {
        SpringApplication.run(BridgeAppApplication.class, args);
    }


    @Override
    public void run(String... args) throws Exception {
        lora.start();

    }
}
