#include <ESP8266HTTPClient.h>  //https://arduino.esp8266.com/stable/package_esp8266com_index.json

extern String url;

void enviaRequisicaoPOST(String sensor, String valor) {

  if (WiFi.status() == WL_CONNECTED) {  // Verifica se está conectado ao WiFi
    HTTPClient http;                    // Cria uma instância de HTTPClient
    WiFiClient client;                  // Cria uma instância de WiFiClient

    http.begin(client, url);  // Especifica o URL do servidor usando WiFiClient

    // Adiciona cabeçalhos
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Dados para enviar via POST
    String parametros = "sensor=" + sensor + "&valor=" + valor;

    // Envia requisição POST
    int httpResponseCode = http.POST(parametros);

    // Verifica o código de resposta
    if (httpResponseCode > 0) {

      String response = http.getString();  // Obter a resposta do servidor

      //Serial.println("Enviando dados para o servidor:");
      Serial.print("Sensor: ");
      //Serial.println(httpResponseCode);   // Imprimir código de resposta
      Serial.println(response);  // Imprimir resposta do servidor
      delay(150);
      
    } else {

      Serial.print("Erro ao enviar dados para o servidor Web: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Finaliza a requisição
  } else {
    Serial.println("Erro na conexão WiFi");  // Imprime mensagem de erro de conexão
  }
}

void verificarEstadoDispositivo(String dispositivo) {
  if (WiFi.status() == WL_CONNECTED) {  // Verifica se está conectado ao WiFi
    HTTPClient http;                    // Cria uma instância de HTTPClient
    WiFiClient client;                  // Cria uma instância de WiFiClient

    http.begin(client, url);                             // Especifica o URL do servidor usando WiFiClient
    http.addHeader("Content-Type", "application/json");  // Adiciona cabeçalho

    // Define o payload JSON a ser enviado
    String jsonPayload = "{\"dispositivo\":\"" + dispositivo + "\"}";
    // Envia a requisição POST
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {            // Verifica o código de resposta
      String response = http.getString();  // Obtém a resposta do servidor

      //Serial.print("Dispositivo: ");
      //Serial.println(httpResponseCode); // Imprime o código de resposta
      //Serial.println(response);  // Imprime a resposta do servidor

      // Remove os caracteres de início e fim: { }
      response.remove(0, 2);                     // Remove os dois primeiros caracteres ' { " '
      response.remove(response.length() - 2);  // Remove os doi últimos caracteres ' " } " '

      // Encontra o índice do separador ':'
      int separatorIndex = response.indexOf(':');

      // Extrai o nome do dispositivo e o estado, removendo também as aspas extras
      String dispositivo = response.substring(0, separatorIndex);  // Remove aspas no início e no fim do dispositivo
      dispositivo.remove(dispositivo.length() - 1);
      String estado = response.substring(separatorIndex + 2);  // Remove aspas no início e no fim do estado

      enviaEstadoDispositivoArduino(dispositivo, estado);
      delay(150);

    } else {
      Serial.print("Erro ao baixar dados do servidor Web: ");  // Imprime mensagem de erro
      Serial.println(httpResponseCode);                        // Imprime o código de resposta
      delay(150);
    }

    http.end();  // Finaliza a requisição
  } else {
    Serial.println("Erro na conexão WiFi");  // Imprime mensagem de erro de conexão
  }
}