// Conecte o pino TX do ESP8266 ao pino RX1 (19) do Arduino Mega.
// Conecte o pino RX do ESP8266 ao pino TX1 (18) do Arduino Mega.
// Conecte os pinos GND de ambos os dispositivos.

void enviaMsgErro(String operacao, int dado) {
}

void enviaEstadoDispositivoArduino(String dispositivo, String estado) {

  ComunicacaoUART.flush();
  ComunicacaoUART.println("Dispositivo: " + dispositivo + " - Estado: " + estado);
  delay(150);
}


void recebeDadosArduino() {
  if (ComunicacaoUART.available() > 0) {                            // Verifica se há dados disponíveis para leitura
    String dadosRecebidos = ComunicacaoUART.readStringUntil('\n');  // Lê a mensagem recebida
    
    int idxDispositivo = dadosRecebidos.indexOf("Sensor: "); // Localiza a posição da substring "Sensor: " na mensagem recebida
    int idxEstado = dadosRecebidos.indexOf(" - Valor: ");  // Localiza a posição da substring " - Valor: " na mensagem recebida

    // Verifica se ambas as substrings foram encontradas
    if (idxDispositivo != -1 && idxEstado != -1) {
      // Extrai o nome do dispositivo a partir da posição após "Sensor: "
      String dispositivo = dadosRecebidos.substring(idxDispositivo + 8, idxEstado);

      // Extrai o estado a partir da posição após " - Valor: "
      String estado = dadosRecebidos.substring(idxEstado + 10);

      dispositivo.trim(); // Apagar espaços em branco
      estado.trim(); // Apagar espaços em branco

      // Chama a função para processar e exibir o nome do dispositivo e seu estado
      enviaRequisicaoPOST(dispositivo, estado);
      delay(150);
    }
  }
}
