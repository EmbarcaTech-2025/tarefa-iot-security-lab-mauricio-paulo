// Bibliotecas necessárias
#include <string.h>                 // Para funções de string como strlen()
#include "pico/stdlib.h"            // Biblioteca padrão do Pico (GPIO, tempo, etc.)
#include "pico/cyw43_arch.h"        // Driver WiFi para Pico W
#include "include/wifi_conn.h"      // Funções personalizadas de conexão WiFi
#include "include/mqtt_comm.h"      // Funções personalizadas para MQTT
#include "include/xor_cipher.h"     // Funções de cifra XOR

#define LED_RED 13
#define LED_BLUE 12
#define LED_GREEN 11

int main() {
    // Inicializa todas as interfaces de I/O padrão (USB serial, etc.)
    stdio_init_all();
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_RED,GPIO_OUT);
    gpio_set_dir(LED_GREEN,GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE,GPIO_OUT);
    // Conecta à rede WiFi
    // Parâmetros: Nome da rede (SSID) e senha
    if(connect_to_wifi("Mauricio's Galaxy S21 FE 5G", "vuyz1773")){
        // Se a conexão for 168.15.6bem-sucedida, acende o LED verde
        gpio_put(LED_GREEN, 1);
        sleep_ms(1000);
        gpio_put(LED_GREEN, 0);
    } else {
        // Se a conexão falhar, acende o LED vermelho
        gpio_put(LED_RED, 1);
        sleep_ms(1000);
        gpio_put(LED_RED, 0);
    }
    
    // Configura o cliente MQTT
    // Parâmetros: ID do cliente, IP do broker, usuário, senha
    mqtt_setup("bitdog1", "192.168.80.145", "mauricio", "1234");
   


    // Mensagem original a ser enviada
    const char *mensagem = "26.5";
    // Buffer para mensagem criptografada (16 bytes)
    uint8_t criptografada[16];
    // Criptografa a mensagem usando XOR com chave 42
    xor_encrypt((uint8_t *)mensagem, criptografada, strlen(mensagem), 42);
    int i=1;
    // Loop principal do programa
    while (true) {
        // Publica a mensagem original (não criptografada)
        //mqtt_comm_publish("escola/sala1/temperatura", mensagem, strlen(mensagem));
  
        
        // Alternativa: Publica a mensagem criptografada (atualmente comentada)
        //mqtt_comm_publish("escola/sala1/temperatura", criptografada, strlen(mensagem));
        subscribe_to_topic("escola/sala1/temperatura", 1);

        
        // Aguarda 5 segundos antes da próxima publicação
        gpio_put(LED_BLUE, i);
        i^=1;
        sleep_ms(5000);
    }
    
    return 0;
}

/* 
 * Comandos de terminal para testar o MQTT:
 * 
 * Inicia o broker MQTT com logs detalhados:
 * mosquitto -c mosquitto.conf -v
 * 
 * Assina o tópico de temperatura (recebe mensagens):
 * mosquitto_sub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "mauricio" -P "1234"
 * 
 * Publica mensagem de teste no tópico de temperatura:
 * mosquitto_pub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123" -m "26.6"
 */