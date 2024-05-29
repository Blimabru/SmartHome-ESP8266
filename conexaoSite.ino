#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

extern String url;

void enviarRequisicaoPOST(String dados, const char* operacao) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Erro na conexão WiFi");
    return;
  }

  HTTPClient http;
  WiFiClient client;

  http.begin(client, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(dados);

  if ((httpResponseCode > 0) /*&& (operacao != "e")*/) {
    String response = http.getString();
    enviarDadosArduino(response.c_str());

  } else {
    Serial.print("Erro na requisição HTTP: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void verificarEstadoDispositivos(String dispositivo) {
  String dados = "dispositivo=" + dispositivo;
  enviarRequisicaoPOST(dados, "v");
}

void enviarDadosSensor(String sensor, String valor) {
  String dados = "sensor=" + sensor + "&valor=" + valor;
  enviarRequisicaoPOST(dados, "e");
}