void enviarDadosArduino(const char* dados) {
  ComunicacaoUART.flush();
  ComunicacaoUART.println(dados);
  ComunicacaoUART.print("\n");
}

void recebeDadosArduino() {
  static char dadosRecebidos[200];
  static unsigned int index = 0;
  static bool mensagemCompleta = false;

  while (ComunicacaoUART.available() > 0) {
    char c = ComunicacaoUART.read();

    if (c == '{') {  // Início de mensagem
      index = 0;
      mensagemCompleta = false;
    }

    if (!mensagemCompleta) {
      dadosRecebidos[index++] = c;

      if (c == '}') {                  // Fim de mensagem
        dadosRecebidos[index] = '\0';  // Termina a string
        mensagemCompleta = true;
        processaDadosRecebidos(dadosRecebidos);
        break;
      }
    }
  }
}

void processaDadosRecebidos(char* dados) {
  //Serial.println(dados);

  String dadosStr(dados);
  int idxSensor = dadosStr.indexOf("sensor");
  int idxValor = dadosStr.indexOf("valor");

  if (idxSensor != -1 && idxValor != -1) {
    String sensor = dadosStr.substring(idxSensor + 9, dadosStr.indexOf("\"", idxSensor + 9));
    String valor = dadosStr.substring(idxValor + 8, dadosStr.indexOf("\"", idxValor + 8));

    enviarDadosSensor(sensor, valor);
  }
}