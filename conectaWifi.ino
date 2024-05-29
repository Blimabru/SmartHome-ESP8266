#include <ESP8266WiFiMulti.h> //https://arduino.esp8266.com/stable/package_esp8266com_index.json

ESP8266WiFiMulti wifiMulti;  // Instancia um objeto ESP8266WiFiMulti chamado wifiMulti

void conectaWifi() {

  const uint32_t connectTimeoutMs = 10000;  // Tempo limite para conectar ao Wi-Fi.
  bool conectado = false;

  WiFi.mode(WIFI_STA);     // Configura o WiFi para modo estação
  WiFi.persistent(false);  // Não salvar a configuração WiFi em flash - opcional

  // Conecta ao Wi-Fi
  while (!conectado) {

    Serial.println("Conectando ao Wi-Fi...");

    credenciaisWifi();

    if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
      Serial.println("Ok.");
      Serial.print("Conectado a: ");
      Serial.println(WiFi.SSID());
      Serial.print("IP local: ");
      Serial.println(WiFi.localIP());

      conectado = true;

      break;

    } else {

      verificaStatusWiFi();

      delay(1000);
    }
  }
  delay(1000);
}

void verificaStatusWiFi() {

    wl_status_t estadoWifi = WiFi.status();
    String estado;

    switch (estadoWifi) {

        case WL_IDLE_STATUS:

            estado = "Wi-Fi está ocioso.";

            Serial.println("Erro: " + estado);

            break;

        case WL_NO_SSID_AVAIL:

            estado = "SSID não disponível.";

            Serial.println("Erro: " + estado);

            break;

        case WL_SCAN_COMPLETED:

            estado = "Varredura de redes Wi-Fi concluída.";

            Serial.println("Erro: " + estado);

            break;

        case WL_CONNECTED:

            estado = "Conectado ao Wi-Fi";

            Serial.println("Erro: " + estado);

            break;

        case WL_CONNECT_FAILED:

            estado = "Falha na conexão.";

            Serial.println("Erro: " + estado);

            break;

        case WL_CONNECTION_LOST:

            estado = "Conexão perdida.";

            Serial.println("Erro: " + estado);

            break;

        case WL_DISCONNECTED:

            estado = "Desconectado do Wi-Fi.";

            Serial.println("Erro: " + estado);

            break;;

        default:

            estado = "Erro Desconhecido.";

            Serial.println("Erro: " + estado);

            break;
    }
}