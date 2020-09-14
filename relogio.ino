#include <NTPClient.h>
#include <WiFi.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "NOME_DA_REDE";                  // Nome da rede Wi-Fi
const char* password = "SENHA_DA_REDE";     // Senha da rede Wi-Fi

#define OLED_LARGURA 128 // Número de Pixels do display OLED (Largura)
#define OLED_ALTURA 64 // Número de Pixels do display OLED (Altura)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(OLED_LARGURA, OLED_ALTURA, &Wire, OLED_RESET);

WiFiUDP udp;
NTPClient ntp(udp, "a.st1.ntp.br", -3 * 3600, 60000);
String hora;

void setup()  {
  WiFi.begin(ssid, password);
  delay(2000);
  ntp.begin();              
  ntp.forceUpdate();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  hora = ntp.getFormattedTime();

  display.setTextSize(2);         // Tamanho da fonte
  display.setTextColor(WHITE);    // Cor da fonte
  display.setCursor(10,8);        // Local de início do texto
  display.println(hora);          // Variável a ser imprimida
  display.display();
  delay(1000);
  display.clearDisplay();         // Limpa p display
}
