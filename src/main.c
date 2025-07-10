#include <stdio.h>
#include "pico/stdlib.h"
#include "display/display.h"
#include "aht10/aht10.h"

// Constantes para os limites de alerta
#define HUMIDITY_THRESHOLD 70.0f
#define TEMPERATURE_THRESHOLD 20.0f

// Função para verificar se há condições de alerta
bool check_alert_conditions(float temp, float hum) {
    return (hum > HUMIDITY_THRESHOLD || temp < TEMPERATURE_THRESHOLD);
}

// Função para exibir alerta no display
void display_alert(float temp, float hum) {
    clear_display();
    
    // Título do alerta
    display_text_no_clear("ALERTA!", 30, 0, 2);

    char hum_str[10], temp_str[10];
    sprintf(hum_str, "%.1f %%", hum);
    sprintf(temp_str, "%.1f C", temp);

    // Verificar qual condição foi violada
    if (hum > HUMIDITY_THRESHOLD && temp < TEMPERATURE_THRESHOLD) {
        // Ambas as condições violadas
        display_text_no_clear("Umidade ALTA", 5, 20, 1);
        display_text_no_clear("Temp BAIXA", 5, 32, 1);

    } else if (hum > HUMIDITY_THRESHOLD) {
        // Apenas umidade alta
        display_text_no_clear("Umidade ALTA!", 15, 20, 1);
    } else if (temp < TEMPERATURE_THRESHOLD) {
        // Apenas temperatura baixa
        display_text_no_clear("Temp BAIXA!", 15, 20, 1);
    }

    printf(hum_str);
    printf(" | ");
    printf(temp_str);
    printf("\n");
    display_text_no_clear("H: ", 5, 44, 1);
    display_text_no_clear(hum_str, 20, 44, 1);
    display_text_no_clear("T: ", 70, 44, 1);
    display_text_no_clear(temp_str, 85, 44, 1);
    
    show_display();
}

// Função para exibir informações normais no display
void display_normal_info(float temp, float hum) {
    clear_display();
    
    // Título
    display_text_no_clear("Monitor", 25, 0, 2);
    
    // Umidade
    display_text_no_clear("Umidade:", 5, 20, 1);
    char hum_str[10];
    sprintf(hum_str, "%.1f%%", hum);
    display_text_no_clear(hum_str, 70, 20, 1);
    
    // Temperatura
    display_text_no_clear("Temp:", 5, 32, 1);
    char temp_str[10];
    sprintf(temp_str, "%.1fC", temp);
    display_text_no_clear(temp_str, 70, 32, 1);
    
    // Status
    display_text_no_clear("Status: OK", 5, 44, 1);
    
    show_display();
}

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    printf("Sistema de Monitoramento AHT10 + Display OLED\n");

    // Inicializar display
    display_init();
    sleep_ms(500);
    
    // Exibir mensagem de inicialização
    display_text("Iniciando...", 0, 25, 2);
    show_display();
    sleep_ms(2000);

    // Inicializar sensor AHT10
    aht10_i2c_init();
    aht10_init();
    sleep_ms(200);
    
    float temp, hum;
    bool alert_active = false;

    while (true) {
        aht10_trigger_measurement();
        sleep_ms(200);

        // Tenta ler sensor
        if (aht10_read(&temp, &hum)) {
            printf("TEMP: %.2f°C | HUM: %.2f%%\n", temp, hum);
            
            // Verificar condições de alerta
            if (check_alert_conditions(temp, hum)) {
                if (!alert_active) {
                    printf("ALERTA: Condições críticas detectadas!\n");
                    alert_active = true;
                }
                display_alert(temp, hum);
            } else {
                if (alert_active) {
                    printf("Condições normalizadas.\n");
                    alert_active = false;
                }
                display_normal_info(temp, hum);
            }
        } else {
            printf("Falha ao ler sensor AHT10...\n");
            display_text("Erro Sensor", 25, 25, 2);
            show_display();
        }

        sleep_ms(1000); // Atualizar a cada 2 segundos
    }
}
