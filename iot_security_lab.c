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
#define BUTTON_A 5

void gpio_callback(uint gpio, uint32_t events) {
    // Callback para interrupção do botão A
    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_RISE)) {
        // Ação a ser executada quando o botão A for pressionado
        // Aqui você pode adicionar código para publicar uma mensagem MQTT ou outra ação
        const char *mensagem = "Botão A pressionado!";
        mqtt_comm_publish("botaoA/pressionado", mensagem, strlen(mensagem));
    }
}

void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
    if(strcmp(topic, "botaoA/pressionado") == 0){
        gpio_put(LED_RED, 1); // Acende o LED vermelho se o tópico for "botaoA/pressionado"
        sleep_ms(1000); // Mantém o LED aceso por 1 segundo
        gpio_put(LED_RED, 0); // Desliga o LED vermelho
    }
    printf("Mensagem recebida no tópico: %s (tamanho total: %lu)\n", topic, (unsigned long)tot_len);
}

void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
    printf("Conteúdo recebido: ");
    for (u16_t i = 0; i < len; i++) {
        putchar(data[i]);
    }
    printf("\n");
}



int main() {
    // Inicializa todas as interfaces de I/O padrão (USB serial, etc.)
    stdio_init_all();
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_RED,GPIO_OUT);
    gpio_set_dir(LED_GREEN,GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE,GPIO_OUT);
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A); // Configura o botão com pull-up interno
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    // Conecta à rede WiFi
    // Parâmetros: Nome da rede (SSID) e senha
    if(connect_to_wifi("xxx", "xxx")){
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
    mqtt_setup("bitdog1", "192.168.15.13", "mauricio", "1234", mqtt_incoming_publish_cb, mqtt_incoming_data_cb);
    

    // Mensagem original a ser enviada
    const char *mensagem = "26.5";
    // Buffer para mensagem criptografada (16 bytes)
    uint8_t criptografada[16];
    // Criptografa a mensagem usando XOR com chave 42
    xor_encrypt((uint8_t *)mensagem, criptografada, strlen(mensagem), 42);
    int i=1;


    subscribe_to_topic("botaoA/pressionado", 1);

    // Loop principal do programa
    while (true) {
        // Publica a mensagem original (não criptografada)
        //mqtt_comm_publish("escola/sala1/temperatura", mensagem, strlen(mensagem));
  
        
        // Alternativa: Publica a mensagem criptografada (atualmente comentada)
        //mqtt_comm_publish("escola/sala1/temperatura", criptografada, strlen(mensagem));
        

        

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
 * mosquitto_pub -h 192.168.15.13 -p 1883 -t "botaoA/pressionado" -u "aluno" -P "senha123" -m "26.6"
 */