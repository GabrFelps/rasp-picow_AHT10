<p align="center">
  <img src="https://img.icons8.com/fluency/96/temperature.png" alt="Sensor AHT10 Logo" width="120"/>
</p>

<h1 align="center">Monitoramento de Temperatura e Umidade com Sensor AHT10 no RP2040</h1>

<p align="center">
  <b>Projeto em C para Raspberry Pi Pico W (RP2040): leitura de temperatura e umidade com sensor AHT10 e exibição em LCD 320x240 com alertas visuais.</b>
</p>

---

## 🎯 Objetivo

- Configurar o sensor **AHT10** para monitorar temperatura e umidade do ambiente via I2C no RP2040.
- Exibir os dados em tempo real em uma tela **LCD 320x240**.
- Implementar alertas visuais no LCD quando:
  - Umidade ultrapassar **70%**.
  - Temperatura ficar abaixo de **20°C**.

---

## ⚙️ Funcionamento

- O sensor AHT10 realiza leituras precisas de temperatura (°C) e umidade (%RH).
- O RP2040 coleta esses dados via I2C e atualiza a tela LCD em tempo real.
- Quando os valores ultrapassam os limites definidos, o LCD exibe mensagens de aviso para o usuário.

---

## 🔌 Esquema de Ligações

| Componente | RP2040 (Pico W)     |
|------------|---------------------|
| AHT10 VCC  | 3.3V                |
| AHT10 GND  | GND                 |
| AHT10 SDA  | GP0 (I2C SDA)       |
| AHT10 SCL  | GP1 (I2C SCL)       |
| LCD VCC    | 3.3V ou 5V (conforme LCD) |
| LCD GND    | GND                 |
| LCD SDA    | GP4 (I2C SDA ou SPI, conforme modelo) |
| LCD SCL    | GP5 (I2C SCL ou SPI, conforme modelo) |
| LCD CS, DC, RST | Conforme conexão específica do LCD |

*Consulte o código e documentação do projeto para detalhes exatos da conexão do LCD.*

---

## 💻 Estrutura do Projeto

- `main.c`: Inicializa sensores, coleta dados e atualiza o LCD.
- `aht10.c/h`: Driver para comunicação e leitura do sensor AHT10 via I2C.
- `lcd.c/h`: Controle do display LCD 320x240.
- `external/ssd1306`: Biblioteca do display.

---

## 🖥️ Como Compilar e Executar

1. Clone o repositório:
git clone https://github.com/GabrFelps/rasp-picow_AHT10.git

2. Configure o ambiente do SDK do Raspberry Pi Pico.

3. Compile o projeto:
```
cd rasp-picow_AHT10
mkdir build && cd build
cmake ..
make
```
4. Copie o arquivo `.uf2` gerado para o Raspberry Pi Pico W.

5. Conecte o hardware conforme o esquema e ligue o dispositivo.

6. Observe a leitura de temperatura e umidade atualizadas no LCD.

7. Caso a umidade ultrapasse 70% ou a temperatura fique abaixo de 20°C, o LCD exibirá um alerta visual.

---
